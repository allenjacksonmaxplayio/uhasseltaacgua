#include "InGameState.h"

#include "Hovercraft.h"
#include "HovercraftRepresentation.h"
#include "ProgressMonitor.h"
#include <HovSound.h>

namespace HovUni {
	InGameState::InGameState(HUClient* client, RaceState* raceState, TiXmlElement* HUDConfig) 
			: mHUClient(client), mTimeLapsed(0), mContinue(true), mRaceState(raceState), mLoader(0), mCountdownFadeout(-1), mUpdateListener(false) {

		mHud = new HUD(HUDConfig, Hikari::FlashDelegate(this, &InGameState::onChat));
		mEntityManager = EntityManager::getClientSingletonPtr();
		mRepresentationManager = RepresentationManager::getSingletonPtr();
		mRaceState->addListener(this);
	}

	Hikari::FlashValue InGameState::onChat(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		Ogre::String chatText = args.at(0).getString();

		if (chatText != "") {
			mHUClient->getChatClient()->sendText(chatText);
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
			mLoader->setLoaded((float) (progress * 100.0f), "KeejOow! hier moet ge zijn!!!");
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
				
				break;
			}
		}
	}

	void InGameState::onPositionChange(RacePlayer* player) {
		
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

		std::pair<int, int> size = GUIManager::getSingletonPtr()->scale(200, 100, 400, 200);
		mCountdown = new Countdown("Countdown", "countdown.swf", size.first, size.second, Hikari::Center);

		//Switch music
		mSoundManager->startAmbient(MUSICCUE_HOVSOUND_BACKGROUND_NORMAL);
	}

	void InGameState::disable() {
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
	}

	bool InGameState::frameStarted(const Ogre::FrameEvent & evt) {
		bool result = true;

		mTimeLapsed += evt.timeSinceLastFrame;

		// Update entity manager
		mEntityManager->updateEntities(evt.timeSinceLastFrame);

		// Process the client
		if (mTimeLapsed > 0.016f) {
			// Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Client start input output process";
			mHUClient->process();
			// Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Client ends input output process";
			mTimeLapsed = 0.0f;
		}

		//Check if we need to synchronise the countdown
		if (mRaceState->getState() == RaceState::COUNTDOWN) {
			mCountdown->resync(mRaceState->getCountdown());
		}

		//Check if we need to remove the countdown overlay
		if (mCountdownFadeout != -1) {
			mCountdownFadeout -= evt.timeSinceLastFrame;

			if (mCountdownFadeout <= 0) {
				mGUIManager->disableOverlay(mCountdown);
				mCountdownFadeout = -1;
			}
		}

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

		if (currEnt != 0) {
			Hovercraft* hov = (Hovercraft*) currEnt;

			mHud->updateDirection(currEnt->getOrientation(), (Ogre::Vector3(2, 0, 0) - currEnt->getPosition()), Ogre::Vector3(0.0f, 1.0f, 0.0f));
			mHud->updateSpeed( fabs((hov->getSpeed() / hov->getMaximumSpeed()) * 100.0f) );
		}
	}
}
