#include "InGameState.h"

namespace HovUni {
	InGameState::InGameState(ClientCore* client, TiXmlElement* HUDConfig) 
			: mClientCore(client), mTimeLapsed(0), mContinue(true) {

		mHud = new HUD(HUDConfig);
		mEntityManager = EntityManager::getClientSingletonPtr();
		mRepresentationManager = RepresentationManager::getSingletonPtr();
	}

	void InGameState::activate() {
		//Remove cursor
		mGUIManager->showCursor(false);
	}

	void InGameState::disable() {
		//Restore cursor
		mGUIManager->showCursor(true);
	}

	bool InGameState::frameStarted(const Ogre::FrameEvent & evt) {
		bool result = true;

		mTimeLapsed += evt.timeSinceLastFrame;

		// Update entity manager
		mEntityManager->updateEntities(evt.timeSinceLastFrame);

		// Process the client
		if (mTimeLapsed > 0.016f) {
			// Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Client start input output process";
			mClientCore->process();
			// Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Client ends input output process";
			mTimeLapsed = 0.0f;
			// TODO Remove
			mClientCore->start();
		}

		// Update representation manager
		mRepresentationManager->drawGameViews(evt.timeSinceLastFrame);

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
}