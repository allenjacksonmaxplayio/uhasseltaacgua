#ifndef _COUNTDOWN_H
#define _COUNTDOWN_H

#include "BasicOverlay.h"

namespace HovUni {
	/**
	 * An overlay containing a countdown representation.
	 *
	 * @author Nick De Frangh
	 */
	class Countdown : public BasicOverlay {
		private:
			/** Boolean to mark if we should be running or not */
			bool mStarted;

		public:
			/**
			 * Chat constructor, see BasicOverlay for parameter description
			 */
			Countdown(const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder = 0);

			/**
			 * Start the countdown timer.
			 */
			void start();

			/**
			 * Function that will be called when the overlay is activated
			 */
			virtual void customActionAfterActivate();
	};
}


#endif //_COUNTDOWN_H