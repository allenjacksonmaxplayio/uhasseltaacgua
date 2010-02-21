#ifndef BASICOVERLAY_H
#define BASICOVERLAY_H

/**
 * The BasicOverlay class will be a pure virtual class abstracting the notion of
 * a Hikari::FlashControl object and providing additional functionality.
 *
 * @author Nick De Frangh
 */

//Include IOS but prevent double link errors!
#define OIS_DYNAMIC_LIB
#include <OIS.h>

#include <Hikari.h>
 
using std::string;

namespace HovUni {
	class BasicOverlay : public OIS::KeyListener {
		friend class GUIManager;

		private:
			/** The given name for this overlay */
			Ogre::String mName;

			/** The name of the Flash file you want to use */
			Ogre::String mFileName;

			/** The width you want the overlay to use */
			int mWidth;

			/** The height you want the overlay to use */
			int mHeight;

			/** The position where you want the overlay to get rendered */
			Hikari::Position mPosition;

			/** The z-order of the overlay */
			Ogre::ushort mZOrder;

			/** The flash control used for this overlay */
			Hikari::FlashControl* mFlashControl;

		public:
			/**
			 * Basic constructor for a Flash overlay.
			 *
			 * @param name A name you want to assign to this overlay
			 * @param fileName The name of the Flash file you want to use (relative to the path of the GUIManager)
			 * @param width The width of this overlay
			 * @param height The height of this overlay
			 * @param position The position where you want to place the overlay
			 * @param zOrder The z-order of the overlay. Specify '0' (default) to automatically
			 *					use the next-highest z-order.
			 */
			BasicOverlay(const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder = 0);

			/**
			 * Destructor
			 */
			virtual ~BasicOverlay();

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
			 * Request the FlashControl object associated with this overlay.
			 * This function will be used by the GUIManager and shouldnt be
			 * directly used unless you know what you are doing.
			 *
			 * @return The FlashControl for this overlay.
			 */
			Hikari::FlashControl* getFlashControl();
		
		private:
			/**
			 * Call this function to automaticly activate this overlay
			 */
			void activate();

			/**
			 * Call this function to automaticly disable this averlay
			 */
			void disable();
	};
}

#endif //BASICOVERLAY_H