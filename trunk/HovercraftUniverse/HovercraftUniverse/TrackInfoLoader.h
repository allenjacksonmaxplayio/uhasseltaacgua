#ifndef TRACKINFOLOADER_H
#define TRACKINFOLOADER_H

#include "Loader.h"
#include "UserDataCallback.h"
#include "UserDataFactory.h"

namespace HovUni {

/**
 * Loader for global track info.
 * 
 * @author Kristof Overdulve
 */
class TrackInfoLoader : public Loader, public UserDataCallback {
private:

	/** The track */
	Track * mTrack;

public:
	/**
	 * Constructor.
	 */
	TrackInfoLoader();

	/**
	 * Destructor.
	 */ 
	virtual ~TrackInfoLoader();

	virtual void StartedLoad();

	virtual void FinishedLoad(bool success);

	/**
	 * @see UserDataCallback::onTrack().
	 */
	virtual void onTrack(Track * track);

	/**
	 * @see Loader::onSceneUserData().
	 */
	void onSceneUserData(const Ogre::String& userDataReference, const Ogre::String& userData);

	/**
	 * Returns the track after the loading or 0 if no loading has occurred yet.
	 *
	 * @return the track
	 */
	Track * getTrack() { return mTrack; }

};

}

#endif
