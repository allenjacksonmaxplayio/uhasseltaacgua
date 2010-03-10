#include "Server.h"
#include <boost/ref.hpp>

namespace HovUni {

Server::Server() : mThread(0), mServerThread(0) {

}


Server::~Server() {
}

void Server::start() {
	if (!mThread && !mServerThread) {
		mServerThread = new ServerThread();
		mThread = new boost::thread(boost::ref(*mServerThread));
	}
}

void Server::stop() {
	if (mThread && mServerThread) {
		mServerThread->stop();
		mThread->join();
		delete mThread;
		mThread = 0;
		delete mServerThread;
		mServerThread = 0;
	}
}

bool Server::isRunning() {
	return (mThread != 0);
}

void Server::join() {
	if (mThread) {
		mThread->join();
	}
}

}