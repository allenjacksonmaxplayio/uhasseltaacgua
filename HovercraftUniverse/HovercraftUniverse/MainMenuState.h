#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "BasicGameState.h"

#include "MainMenu.h"
#include "ServerMenuListener.h"

namespace HovUni {
	/**
	 * A Game state representing the main menu
	 *
	 * @author Nick De Frangh
	 */
	class MainMenuState : public BasicGameState, public ServerMenuListener {
		private:
			/** The Overlay for the Main menu */
			MainMenu* mMenu;

			/** Boolean to check if we want to stop or not */
			bool mContinue;
	
		public:
			/**
			 * Constructor for the Main menu state
			 */
			MainMenuState();

			/**
			 * this function gets calles when we want to connect to a certain IP
			 *
			 * @param address The adress to connect to <IP:port> or <IP>
			 */
			virtual bool onConnect(const Ogre::String& address);

			/**
			 * Called when we need to create a multiplayer game
			 */
			virtual void onCreate();

			/**
			 * Function that will be called when we want to quit the game
			 *
			 * @param caller A Reference to the caller, should be ignored
			 * @param arg Some arguments, will be empty
			 */
			Hikari::FlashValue onQuit(Hikari::FlashControl* caller, const Hikari::Arguments& args);

			/**
			 * Function called when the state gets activated
			 */
			virtual void activate();

			/**
			 * Function called when the state gets disabled
			 */
			virtual void disable();

			/**
			 * Function called every frame, do drawing functions and stuff in here
			 */
			virtual bool frameStarted(const Ogre::FrameEvent & evt);

			/**
			 * @see MouseListener::mouseMoved().
			 * Can be implemented as needed.
			 */
			virtual bool mouseMoved(const OIS::MouseEvent & e);

			/**
			 * @see MouseListener::mousePressed().
			 * Can be implemented as needed.
			 */
			virtual bool mousePressed(const OIS::MouseEvent & e, OIS::MouseButtonID id);
			
			/**
			 * @see MouseListener::mouseReleased().
			 * Can be implemented as needed.
			 */
			virtual bool mouseReleased(const OIS::MouseEvent & e, OIS::MouseButtonID id);

			/**
			 * @see KeyListener::keyPressed().
			 * Can be implemented as needed.
			 */
			virtual bool keyPressed(const OIS::KeyEvent & e);

			/**
			 * @see KeyListener::keyReleased().
			 * Can be implemented as needed.
			 */
			virtual bool keyReleased(const OIS::KeyEvent & e);
	};
}

#endif //MAINMENUSTATE_H