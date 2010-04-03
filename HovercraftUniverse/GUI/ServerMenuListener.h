#ifndef _SERVERMENULISTENER_H
#define _SERVERMENULISTENER_H

#include <OgreString.h>

namespace HovUni {
	/**
	 * An interface for a serverMenuListener. This should be implemented by
	 * classes who are interested in the server menu events.
	 *
	 * @author Nick De Frangh
	 */
	class ServerMenuListener {
		public:
			/**
			 * Function that will be called when a client wants to connect to a certain address.
			 *
			 * @param address The IP:Port string represention the server address.
			 */
			virtual bool onConnect(const Ogre::String& address) = 0;

			/**
			 * When a player wants to create a new game, this method will be called.
			 */
			virtual void onCreate() = 0;
	};
}

#endif //_SERVERMENULISTENER_H