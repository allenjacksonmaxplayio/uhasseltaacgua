#ifndef BASICOVERLAY_H
#define BASICOVERLAY_H

/**
 * The BasicOverlay class will be a pure virtual class abstracting the notion of
 * a Hikari::FlashControl object and providing additional functionality.
 *
 * @author Nick De Frangh
 */

#include <Hikari.h>
#include <OIS.h>
 
using std::string;

namespace HovUni {
	class BasicOverlay : public OIS::KeyListener {
		private:
			Ogre::String mName;
			Hikari::FlashControl* mFlashControl;

		public:
			BasicOverlay(const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder = 0);

			/**
			 * Trigger custom events when certain keys are pressed.
			 * You need to overload this function in order to add custom events,
			 * default function does nothing. You do not need to use this function
			 * for basic key inputs to the flash objects, this gets done
			 * automatically.
			 *
			 * @param evt The KeyEvent that occured
			 * @return ?
			 */
			virtual bool keyPressed(const OIS::KeyEvent &evt);
		
			/**
			 * Trigger custom events when certain keys are released.
			 * You need to overload this function in order to add custom events,
			 * default function does nothing. You do not need to use this function
			 * for basic key inputs to the flash objects, this gets done
			 * automatically.
			 *
			 * @param evt The KeyEvent that occured
			 * @return ?
			 */
			virtual bool keyReleased(const OIS::KeyEvent &evt);

			/**
			 * Function to automaticly register this overlay for key
			 * events coming from the GUIManager.
			 */
			void registerForKeys();

			/**
			 * Function to automaticly unregister this overlay for key
			 * events coming from the GUIManager.
			 */
			void unregisterForKeys();

			Hikari::FlashControl* getFlashControl();
	};
}

#endif //BASICOVERLAY_H