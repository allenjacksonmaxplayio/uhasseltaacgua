#include "InGameState.h"

#include "Hovercraft.h"

namespace HovUni {
	InGameState::InGameState(HUClient* client, RaceState* raceState, TiXmlElement* HUDConfig) 
			: mHUClient(client), mTimeLapsed(0), mContinue(true), mRaceState(raceState), mLoader(0) {

		mHud = new HUD(HUDConfig, Hikari::FlashDelegate(this, &InGameState::onChat));
		mEntityManager = EntityManager::getClientSingletonPtr();
		mRepresentationManager = RepresentationManager::getSingletonPtr();
		mRaceState->addListener(this);
	}

	Hikari::FlashValue InGameState::onChat(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		Ogre::String chatText = args.at(0).getString();

		if (chatText != "") {
			mHUClient->getChatClient()->sendText(chatText);
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[LobbyState]: " << "Sending chat message: " << args.at(0).getString();
		}

		return "success";
	}

	////////////////////////////////////////////
	//			RaceStateListener functions	  //
	////////////////////////////////////////////

	void InGameState::onStateChange(RaceState::States state) {
		switch (state) {
			case RaceState::INITIALIZING:
				//People are still creating the racestate, start showing the loading screen
			case RaceState::LOADING: {
				//Make sure the hud is deactivated
				mHud->deactivate();

				if (mLoader == 0) {
					mLoader = new LoadingOverlay("Loader", "loader.swf", mGUIManager->getResolutionWidth(), mGUIManager->getResolutionHeight(), Hikari::Center);
					mGUIManager->activateOverlay(mLoader);
				}

				//We are actually loading, make sure we are monitoring everything
				//TODO make it get real values
				mLoader->setLoaded(50.0f, "Loading...");

				break;
			}
			case RaceState::COUNTDOWN: {
				//Everyone is done loading, go ingame and start the countdown!
				mGUIManager->disableOverlay(mLoader);
				//Make sure the hud is activated
				mHud->activate();

				break;
			}
			case RaceState::RACING: {
				//Countdown has finished, race has started!

				break;
			}
			case RaceState::FINISHING: {
				//We have finished, go freestyle!
				
				break;
			}
			case RaceState::CLEANUP: {
				//Cleaning up and going back to the lobby
				
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
		//Register for chat events
		mHUClient->setChatListener(mHud);

		//Make sure we activate all the key actions
		mInputManager->getKeyManager()->setActive();

		//Remove cursor
		mGUIManager->showCursor(false);
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
			mGUIManager->disableOverlay(mLoader);
		}
		delete mLoader;

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

		// Update representation manager
		mRepresentationManager->drawGameViews(evt.timeSinceLastFrame);

		//Update the HUD
		if (mHud->isActivated()) {
			updateHud();
		}

		//We are using a GUI, so update it
		mGUIManager->update();

		//We have sound, update it
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
