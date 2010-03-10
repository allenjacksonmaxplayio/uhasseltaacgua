#ifndef SERVERTHREAD_H_
#define SERVERTHREAD_H_

#include "ServerCore.h"

namespace HovUni {

/**
 * This class represents the server thread for the server.
 *
 * @author Olivier Berghmans
 */
class ServerThread {
private:
	/** The server core */
	ServerCore* mServerCore;

	/** Whether to stop the thread */
	bool mStop;

public:
	/**
	 * Constructor
	 */
	ServerThread();

	/**
	 * Destructor
	 */
	~ServerThread();

	/**
	 * Indicate the thread to stop
	 */
	void stop();

	/**
	 * Call operator used for threading
	 */
	void operator()();
};

}

#endif
