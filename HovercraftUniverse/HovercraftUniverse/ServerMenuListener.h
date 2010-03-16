#ifndef _SERVERMENULISTENER_H
#define _SERVERMENULISTENER_H

#include <OgreString.h>

namespace HovUni {
	class ServerMenuListener {
		public:
			virtual bool onConnect(const Ogre::String& address) = 0;
			virtual void onCreate() = 0;
	};
}

#endif //_SERVERMENULISTENER_H