#ifndef GUIMANAGER_H
#define GUIMANAGER_H

/**
 * The GUIManager class will manage everything that is related to
 * the graphical user interface that users will see during the game.
 *
 * @author Nick De Frangh
 */

#include <Hikari.h>
#include <OIS.h> //OIS input systeem
#include <Ogre.h>
 
using Hikari::HikariManager;
using std::string;

namespace HovUni {
	class GUIManager : public OIS::KeyListener, OIS::MouseListener {
		private:
			/** The main manager for all the flash objects */
			HikariManager mHikariManager;
			
		public:
			/**
			 * Basic constructor for the GUI manager.
			 *
			 * @param mediaPath The path to where the flash files for the GUI are
			 *		located. This can be absolute or relative
			 */
			GUIManager(const Ogre::String& mediaPath);

			/**
			 * Destructor
			 */
			virtual ~GUIManager();
		
			/**
			 * Remove one overlay from the current GUI, this will remove the object completely from memory.
			 *
			 * @param name The name of this overlay (the same name you used when you created it)
			 */
			void removeOverlay(const Ogre::String& name);
			
			/**
			 * Remove all current overlays. Could be used to switch from interface completely.
			 */
			void removeAllOverlays();
		
			/**
			 * Update function has to be called everytime the update loop of the
			 * program is executed to perform visual changes.
			 */
			void update();
		
			/**
			 * Inject mouse movement events into the GUI.
			 *
			 * @param evt The MouseEvent that occured
			 * @return ?
			 */
			bool mouseMoved(const OIS::MouseEvent &evt);
		
			/**
			 * Inject mouse press events into the GUI.
			 *
			 * @param evt The MouseEvent that occured
			 * @param id The id of the mouse button that was pressed
			 * @return ?
			 */
			bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
		
			/**
			 * Inject mouse release events into the GUI.
			 *
			 * @param evt The MouseEvent that occured
			 * @param id The id of the mouse button that was released
			 * @return ?
			 */
			bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
			
			/**
			 * Inject key press events into the GUI.
			 *
			 * @param evt The KeyEvent that occured
			 * @return ?
			 */
			bool keyPressed(const OIS::KeyEvent &evt);
		
			/**
			 * Inject key release events into the GUI.
			 *
			 * @param evt The KeyEvent that occured
			 * @return ?
			 */
			bool keyReleased(const OIS::KeyEvent &evt);

		private:
			/**
			 * Call this function to activate a new flash file as overlay.
			 *
			 * @param name The name you want to give this overlay
			 * @param fileName The filename of the flash file you want to use
			 * @param viewport The ogre viewport, needed to be able to render the 
			 * @param width The width of the overlay (in pixels)
			 * @param height The height of the overlay (in pixels)
			 * @param position The position where you want to place the overlay, relative to the viewport
			 * @param zOrder The z-order of the overlay. Specify '0' to automatically use the next-highest z-order (default).
			 */
			void activateOverlay(const Ogre::String& name, const Ogre::String& fileName, Ogre::Viewport* viewport, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder = 0);
	};
}

#endif //GUIMANAGER_H