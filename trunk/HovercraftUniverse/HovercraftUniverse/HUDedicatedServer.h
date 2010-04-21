#ifndef HUDEDICATEDSERVER_H_
#define HUDEDICATEDSERVER_H_

#include "DedicatedServer.h"

namespace HovUni {
	/**
	*	The HoverCraftUniverse Dedicated Server Application Class.
	*	@author Dirk Delahaye, 30/03/2010
	*/
	class HUDedicatedServer : DedicatedServer {
	public:
		HUDedicatedServer(const std::string& configINI);

		/**
		*	See DedicatedServer::init()
		*/
		void init();

		/**
		*	See DedicatedServer::run()
		*/
		void run(bool standalone = false);
	};
}
#endif //HUDEDICATEDSERVER_H_