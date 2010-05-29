#include "InGameState.h"
#include "Application.h"
#include "CheckPoint.h"
#include "Finish.h"
#include "Hovercraft.h"
#include "HovercraftRepresentation.h"
#include "ProgressMonitor.h"
#include "Start.h"
#include <HovSound.h>

namespace HovUni {
	InGameState::InGameState(HUClient* client, RaceState* raceState, TiXmlElement* HUDConfig) 
			: mHUClient(client), mTimeLapsed(0), mContinue(true), mRaceState(raceState), mLoader(0), mCountdownFadeout(-1), mUpdateListener(false), mCleaningUp(false) {

		mHud = new HUD(HUDConfig, Hikari::FlashDelegate(this, &InGameState::onChat));
		mEntityManager = EntityManager::getClientSingletonPtr();
		mRepresentationManager = RepresentationManager::getSingletonPtr();
		mRaceState->addListener(this);
	}

	Hikari::FlashValue InGameState::onChat(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		Ogre::String chatText = args.at(0).getString();

		if (chatText != "") {
			mHUClient->getChat()->sendText(chatText);
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[InGameState]: " << "Sending chat message: " << args.at(0).getString();
		}

		return "success";
	}

	////////////////////////////////////////////
	//	 ProgressMonitorListener functions	  //
	////////////////////////////////////////////

	void InGameState::updateProgress(double progress) {
		if (mLoader) {
			//Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[InGameState]: OMFG? " << (float) (progress * 100.0f);
			mLoader->setLoaded((float) (progress * 100.0f), "Loading some more...");
		}
	}

	////////////////////////////////////////////
	//			RaceStateListener functions	  //
	////////////////////////////////////////////

	void InGameState::onStateChange(RaceState::States state) {
		switch (state) {
			case RaceState::INITIALIZING:
				//People are still creating the racestate, start showing the loading screen
				//We don't want the listener position to be updated
				mUpdateListener = false;

				break;
			case RaceState::LOADING: {
				//We are actually loading, make sure we are monitoring everything
				//TODO make it get real values
				//mLoader->setLoaded(50.0f, "Loading...");

				break;
			}
			case RaceState::INTRO: {
				HovercraftRepresentation* me = (HovercraftRepresentation*) mRepresentationManager->getTrackedEntityRepresentation();
				me->setVolume(0.6f);

				//Everyone is done loading, go ingame and show the intro!
				mGUIManager->disableOverlay(mLoader);

				//TODO: Show cool intro?
				break;
			}
			case RaceState::COUNTDOWN: {
				//Make sure the hud is activated
				mHud->activate();
				//Register for chat events
				mHUClient->setChatListener(mHud);

				//Show the countdown
				mGUIManager->activateOverlay(mCountdown);
				mCountdown->start(5000);

				//Start updating the sound listener
				mUpdateListener = true;

				break;
			}
			case RaceState::RACING: {
				mCountdownFadeout = 3;
				//Countdown has finished, race has started!
				mHud->startLapTimer();
				mHud->setCurrentPosition(mRaceState->getOwnPlayer()->getPosition());
				mHud->setNumberOfPlayers(mRaceState->getPlayers().size());

				break;
			}
			case RaceState::FINISHING: {
				//We have finished, go freestyle!
				mHud->stopLapTimer();

				break;
			}
			case RaceState::CLEANUP: {
				//Cleaning up and going back to the lobby

				//Stop updating the sound listener
				mUpdateListener = false;

				//Stop some things
				mCleaningUp = true;
				
				break;
			}
		}
	}

	void InGameState::onPositionChange(RacePlayer* player) {
		if (mHud->isActivated()) {
			std::cout << "Position: " << mRaceState->getOwnPlayer()->getPosition() << std::endl;
			mHud->setCurrentPosition(mRaceState->getOwnPlayer()->getPosition());
			mHud->setNumberOfPlayers(mRaceState->getPlayers().size());
		}
	}

	////////////////////////////////////////////
	//			BasicGameState functions	  //
	////////////////////////////////////////////

	void InGameState::activate() {
		//Make sure we activate all the key actions
		mInputManager->getKeyManager()->setActive();

		//Remove cursor
		mGUIManager->showCursor(false);

		//Make sure the hud is deactivated
		mHud->deactivate();

		if (mLoader == 0) {
			mLoader = new LoadingOverlay("Loader", "loader.swf", mGUIManager->getResolutionWidth(), mGUIManager->getResolutionHeight(), Hikari::Center);
			mGUIManager->activateOverlay(mLoader);
			mLoader->setLoaded(0.0f, "Initializing");
			ProgressMonitor::getSingletonPtr()->addListener(this);
		}

		// Create skies
		mSkyX = new SkyX::SkyX(Application::msSceneMgr, mRepresentationManager->getGameViews().at(0)->getCamera()->getCamera());
		mSkyX->create();

		// Add a basic cloud layer
		mSkyX->getCloudsManager()->add(SkyX::CloudLayer::Options());
		SkyX::AtmosphereManager::Options SkyXOptions = mSkyX->getAtmosphereManager()->getOptions();
		SkyXOptions.Time.x = 21.0;
		mSkyX->getAtmosphereManager()->setOptions(SkyXOptions);

		std::pair<int, int> size = GUIManager::getSingletonPtr()->scale(200, 100, 400, 200);
		mCountdown = new Countdown("Countdown", "countdown.swf", size.first, size.second, Hikari::Center);

		//Switch music
		mSoundManager->startAmbient(MUSICCUE_HOVSOUND_BACKGROUND_NORMAL);
	}

	void InGameState::disable() {
		// Clean up skies
		mSkyX->remove();

		//Deregister for chatevents
		mHUClient->removeChatListener(mHud);

		//Remove the hud
		if (mHud != 0) {
			mHud->deactivate();
		}

		//Restore cursor
		mGUIManager->showCursor(true);

		if (mLoader != 0) {
			ProgressMonitor::getSingletonPtr()->removeListener(this);
			mGUIManager->disableOverlay(mLoader);
		}
		delete mLoader;
		mLoader = 0;

		delete mCountdown;
		mCountdown = 0;

		mRaceState->removeListener(this);

		//Switch music
		mSoundManager->stopAmbient(MUSICCUE_HOVSOUND_BACKGROUND_NORMAL);
		mSoundManager->startAmbient(MUSICCUE_HOVSOUND_MENU);
	}

	bool InGameState::frameStarted(const Ogre::FrameEvent & evt) {
		bool result = true;

		mTimeLapsed += evt.timeSinceLastFrame;

		// Update entity manager
		mEntityManager->updateEntities(evt.timeSinceLastFrame);

		// Process the client
		if (mTimeLapsed > 0.016f) {
			// Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Client start input output process";
			mHUClient->process((int) (mTimeLapsed * 1000.0f));
			// Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Client ends input output process";
			mTimeLapsed = 0.0f;
		}

		if (!mCleaningUp) {
			//Check if we need to synchronise the countdown
			if ((mRaceState != 0) && (mRaceState->getState() == RaceState::COUNTDOWN)) {
				mCountdown->resync(mRaceState->getCountdown());
			}
		} else {
			//We want to switch state!
			mRaceState->removeListener(this);
			mManager->switchState(GameStateManager::LOBBY);
		}

		//Check if we need to remove the countdown overlay
		if (mCountdownFadeout != -1) {
			mCountdownFadeout -= evt.timeSinceLastFrame;

			if (mCountdownFadeout <= 0) {
				mGUIManager->disableOverlay(mCountdown);
				mCountdownFadeout = -1;
			}
		}

		// Get the sky options
		SkyX::AtmosphereManager::Options SkyXOptions = mSkyX->getAtmosphereManager()->getOptions();
		mSkyX->setTimeMultiplier(0.3f);
		// Make sure we never quit night time
		if ((SkyXOptions.Time.x > 4.0) && (SkyXOptions.Time.x < 5.0)) {
			SkyXOptions.Time.x = 21.0;
		}
		mSkyX->getAtmosphereManager()->setOptions(SkyXOptions);
		mSkyX->update(evt.timeSinceLastFrame);

		// Update representation manager
		mRepresentationManager->drawGameViews(evt.timeSinceLastFrame);

		//Update the HUD
		if (mHud->isActivated()) {
			updateHud();
		}

		//We are using a GUI, so update it
		mGUIManager->update();

		//We have sound, update it
		if (mUpdateListener) {
			//Get current entity
			Entity* currEntity = mEntityManager->getTrackedEntity();
			Ogre::SceneManager::CameraIterator it = mRepresentationManager->getSceneManager()->getCameraIterator();
			Ogre::Camera* cam = it.getNext();
			mSoundManager->updateListenerPosition(&currEntity->getPosition(), &currEntity->getVelocity(), &currEntity->getOrientation());
		}
		mSoundManager->update();

		return (mContinue && result);
	}

	bool InGameState::mouseMoved(const OIS::MouseEvent & e) {
		bool result = true;

		//We are using a GUI, so update it
		result = result && mGUIManager->mouseMoved(e);

		return result;
	}

	bool InGameState::mousePressed(const OIS::MouseEvent & e, OIS::MouseButtonID id) {
		bool result = true;

		//We are using a GUI, so update it
		result = result && mGUIManager->mousePressed(e, id);
		
		return result;
	}

	bool InGameState::mouseReleased(const OIS::MouseEvent & e, OIS::MouseButtonID id) {
		bool result = true;

		//We are using a GUI, so update it
		result = result && mGUIManager->mouseReleased(e, id);
		
		return result;
	}

	bool InGameState::keyPressed(const OIS::KeyEvent & e) {
		bool result = true;

		OIS::Keyboard * keyboard = InputManager::getSingletonPtr()->getKeyboard();

		switch (e.key) {
			case OIS::KC_ESCAPE:
			case OIS::KC_LMENU:
			case OIS::KC_RMENU:
			case OIS::KC_F4:
				// Check whether right combinations are pressed concurrently
				if (keyboard->isKeyDown(OIS::KC_ESCAPE) || 
					(keyboard->isKeyDown(OIS::KC_LMENU) && keyboard->isKeyDown(OIS::KC_RMENU) && keyboard->isKeyDown(OIS::KC_F4))) {
					// Stop rendering
					mContinue = false;
				}
				break;
			case OIS::KC_RETURN:
				//Focus the chat
				if (!mHud->isChatFocused()) {
					mHud->focusChat();
					//We don't want any crazy input keys
					mInputManager->getKeyManager()->setInactive();
				} else {
					//Defocus the chat
					mHud->defocusChat();
					//We don't want any crazy input keys
					mInputManager->getKeyManager()->setActive();
				}
				break;
			default:
				// Do nothing
				break;
		}

		//We are using a GUI, so update it
		result = result && mGUIManager->keyPressed(e);
		
		return result;
	}

	bool InGameState::keyReleased(const OIS::KeyEvent & e) {
		bool result = true;

		//We are using a GUI, so update it
		result = result && mGUIManager->keyReleased(e);
		
		return result;
	}

	void InGameState::updateHud() {
		//Update hud objects to new values
		//Current entity
		Entity* currEnt = EntityManager::getClientSingletonPtr()->getTrackedEntity();

		RacePlayer* myPlayer = mRaceState->getOwnPlayer();
		
		//std::cout << "WE NEED TO POINT TO: " << (int)myPlayer->getLastCheckpoint() << std::endl;

		Ogre::Vector3 goal = (currEnt->getPosition() + currEnt->getOrientation());
		if ((int)myPlayer->getLastCheckpoint() == -1) {
			//Point to the start
			std::vector<Entity*> starts = EntityManager::getServerSingletonPtr()->getEntities(Start::CATEGORY);
			if (starts.size() >= 1) {
				Start * start = dynamic_cast<Start *> (starts[0]);
				goal = start->getPosition();
			}
		} else {
			//Find the correct checkpoint
			std::vector<Entity*> checkpoints = EntityManager::getServerSingletonPtr()->getEntities(CheckPoint::CATEGORY);
			for (unsigned int i = 0; i < checkpoints.size(); ++i) {
				CheckPoint * checkpoint = dynamic_cast<CheckPoint *> (checkpoints[i]);
				if (checkpoint->getNumber() == (myPlayer->getLastCheckpoint() + 1)) {
					goal = checkpoint->getPosition();
					break;
				}

				//If we get here, we didn't find it, point to the finish!
				std::vector<Entity*> finishes = EntityManager::getServerSingletonPtr()->getEntities(Finish::CATEGORY);
				if (finishes.size() >= 1) {
					Finish * finish = dynamic_cast<Finish *> (finishes[0]);
					goal = finish->getPosition();
				}
			}
		}

		if (currEnt != 0) {
			Hovercraft* hov = (Hovercraft*) currEnt;

			mHud->updateDirection(currEnt->getOrientation(), goal - currEnt->getPosition(), currEnt->getUpVector());
			mHud->updateSpeed( fabs((hov->getSpeed() / hov->getMaximumSpeed()) * 100.0f) );
		}
	}
}
