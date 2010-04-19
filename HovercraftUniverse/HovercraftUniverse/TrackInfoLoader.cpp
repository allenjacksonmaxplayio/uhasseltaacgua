#include "CustomOgreMaxScene.h"
#include "TrackInfoLoader.h"
#include "Track.h"
#include <OgreLogManager.h>

namespace HovUni {

TrackInfoLoader::TrackInfoLoader() : mTrack(0) {
	mUserDataFactory.addUserDataCallback(this);
}

TrackInfoLoader::~TrackInfoLoader(void) {
	mUserDataFactory.removeUserDataCallback(this);
}

void TrackInfoLoader::StartedLoad() {
	setLoading(true);
}

void TrackInfoLoader::FinishedLoad(bool success) {
	setLoading(false);
}

void TrackInfoLoader::onTrack(Track * track) {
	mTrack = track;
}

void TrackInfoLoader::onSceneUserData(const Ogre::String& userDataReference, const Ogre::String& userData) {
	Ogre::LogManager::getSingletonPtr()->getDefaultLog()->stream() << "TRACKINFOLOADER USERDATA";
	if (!userData.empty()) {
		EntityDescription desc("Track", Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
		mUserDataFactory.parseUserData(userData, desc);
	}
}

}
