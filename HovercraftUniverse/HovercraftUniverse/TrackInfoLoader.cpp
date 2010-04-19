#include "CustomOgreMaxScene.h"
#include "TrackInfoLoader.h"
#include "Track.h"

namespace HovUni {

TrackInfoLoader::TrackInfoLoader() : mTrack(0) {
}

TrackInfoLoader::~TrackInfoLoader(void) {
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
		UserDataFactory::getSingleton().parseUserData(userData, desc);
	}
}

}
