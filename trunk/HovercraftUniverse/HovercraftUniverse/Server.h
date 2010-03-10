#ifndef SERVER_H_
#define SERVER_H_

#include "ServerThread.h"
#include <boost/thread/thread.hpp>

namespace HovUni {

/**
 * This class represents the server.
 *
 * @author Olivier Berghmans
 */
class Server {
private:
	/** The boost thread container */
	boost::thread* mThread;

	/** The server thread */
	ServerThread* mServerThread;

public:
	/**
	 * Constructor
	 */
	Server();

	/**
	 * Destructor
	 */
	~Server();

	/**
	 * Start the server
	 */
	void start();

	/**
	 * Stop the server
	 */
	void stop();

	/**
	 * Check if server is running
	 */
	bool isRunning();

	/**
	 * Wait for this thread
	 */
	void join();
};

}

#endif
