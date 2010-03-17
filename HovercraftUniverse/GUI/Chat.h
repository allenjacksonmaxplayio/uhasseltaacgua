#ifndef _CHAT_H
#define _CHAT_H

#include "BasicOverlay.h"

namespace HovUni {
	/**
	 * An overlay containing a chat representation.
	 *
	 * @author Nick De Frangh
	 */
	class Chat : public BasicOverlay {
		public:
			/**
			 * Chat constructor, see BasicOverlay for parameter description
			 */
			Chat(const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder = 0);

	};
}

#endif //_CHAT_H