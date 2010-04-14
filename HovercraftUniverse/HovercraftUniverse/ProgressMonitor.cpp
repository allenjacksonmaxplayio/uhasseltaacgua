#include "ProgressMonitor.h"
#include <string>

namespace HovUni {

std::map<std::string, int> ProgressMonitor::mEntitiesToLoad = std::map<std::string, int>();
std::map<std::string, int> ProgressMonitor::mEntitiesLoaded = std::map<std::string, int>();
int ProgressMonitor::mTotalEntitiesToLoad = 0;
int ProgressMonitor::mTotalEntitiesLoaded = 0;
std::vector<IProgressMonitorListener *> ProgressMonitor::mListeners = std::vector<IProgressMonitorListener *>(); 

void ProgressMonitor::addTask(std::string title, int noLoads) {
	if (mEntitiesToLoad.size() == 0) {
		// First element --> initialize
		mTotalEntitiesToLoad = 0;
		mTotalEntitiesLoaded = 0;
	}

	mEntitiesToLoad[title] =  noLoads;
	mEntitiesLoaded[title] = 0;
	mTotalEntitiesToLoad += noLoads;
}

void ProgressMonitor::updateTask(std::string title) {
	mEntitiesLoaded[title] ++;
	mTotalEntitiesLoaded ++;

	// Notify listeners
	for (std::vector<IProgressMonitorListener *>::const_iterator it = mListeners.begin(); it != mListeners.end(); it++) {
		(*it)->updateProgress(getProgress());
	}
}

double ProgressMonitor::getProgress() {
	return (double) mTotalEntitiesLoaded / (double) mTotalEntitiesToLoad;
}

}