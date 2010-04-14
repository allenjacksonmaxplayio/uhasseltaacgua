#ifndef PROGRESSMONITOR_H_
#define PROGRESSMONITOR_H_

#include <vector>
#include <utility>
#include <map>
#include "ProgressMonitorListener.h"
#include <string>

namespace HovUni {

/**
 * The progress monitor can be used to - here it comes! - monitor progress in a task that takes a while. It allows for the system to give feedback to the
 * user about how long it will take to perform the task(s). TODO Perhaps do something with the entity titles, now they're quite .. useless.
 *
 * @author Kristof Overdulve
 */
class ProgressMonitor
{
private:
	
	/** The entities to load */
	static std::map<std::string, int> mEntitiesToLoad;

	/** The entities loaded */
	static std::map<std::string, int> mEntitiesLoaded;

	/** The total number of entities to load */
	static int mTotalEntitiesToLoad;

	/** The total number of entities loaded */
	static int mTotalEntitiesLoaded;

	/** The listeners to notify upon an update */
	static std::vector<IProgressMonitorListener *> mListeners; 

	// Disallow object to be created
	ProgressMonitor(void) {}
	~ProgressMonitor(void) {}

public:

	/**
	 * Includes the given task into the monitor.
	 *
	 * @param title the title of the new task to load
	 * @param noLoads the number of elements that must be loaded
	 */
	static void addTask(std::string title, int noLoads);

	/**
	 * Updates the given task in order to indicate that a new element has been loaded.
	 *
	 * @param title the title of the task that is updated
	 */
	static void updateTask(std::string title);

	/**
	 * Returns the ratio of number of elements loaded, compared to the total number of entities to load (e.g. return of 0.51 means 51%).
	 *
	 * @return the progress
	 */
	static double getProgress();

	/**
	 * Adds the given object to the listeners.
	 *
	 * @param listener is the new listener
	 */
	static void addListener(IProgressMonitorListener * listener) {
		mListeners.push_back(listener);
	}


};

}

#endif