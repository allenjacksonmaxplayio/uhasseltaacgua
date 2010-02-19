#ifndef BASICOVERLAY_H
#define BASICOVERLAY_H

/**
 * The BasicOverlay class will be a pure virtual class abstracting the notion of
 * a @link{Hikari::FlashControl} object and providing additional functionality.
 *
 * @author Nick De Frangh
 */

#include <Hikari.h>
#include <OIS.h>
 
using std::string;

namespace HovUni {
	class BasicOverlay : public OIS::KeyListener {
		private:
			/** The given name for this overlay */
			Ogre::String mName;

			/** The flash control used for this overlay */
			Hikari::FlashControl* mFlashControl;

		public:
			/**
			 * Basic constructor for a Flash overlay.
			 *
			 * @param name A name you want to assign to this overlay
			 * @param fileName The name of the Flash file you want to use (relative to the path of the @link{GUIManager})
			 * @param width The width of this overlay
			 * @param height The height of this overlay
			 * @param position The position where you want to place the overlay
			 * @param zOrder The z-order of the overlay. Specify '0' (default) to automatically
			 *					use the next-highest z-order.
			 */
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

			/**
			 * Request the @link{FlashControl} object associated with this overlay.
			 * This function will be used by the @link{GUIManager} and shouldnt be
			 * directly used unless you know what you are doing.
			 *
			 * @return The @link{FlashControl} for this overlay.
			 */
			Hikari::FlashControl* getFlashControl();
	};
}

#endif //BASICOVERLAY_H