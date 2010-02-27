#include "SoundManager.h"

#include <OgreRoot.h>

namespace HovUni {
	SoundManager* SoundManager::msSingleton = 0;
	const Ogre::String SoundManager::msPrefix = "SoundManager :: ";

	SoundManager::SoundManager(const Ogre::String& mediaPath, const Ogre::String& mediaFile) {
		//Initialize some stuff
		ERRCHECK(mResult = FMOD::EventSystem_Create(&mEventSystem));
		ERRCHECK(mResult = mEventSystem->init(64, FMOD_INIT_NORMAL, 0, FMOD_EVENT_INIT_NORMAL));
		ERRCHECK(mResult = mEventSystem->setMediaPath(mediaPath.c_str()));

		//Load a sound object

		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << msPrefix << "Loading mediafile : " << mediaPath.c_str() << mediaFile.c_str();
		ERRCHECK(mResult = mEventSystem->load(mediaFile.c_str(), 0, 0));
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << msPrefix << "Mediafile loaded.";

		ERRCHECK(mResult = mEventSystem->getMusicSystem(&mMusicSystem));
	}

	SoundManager& SoundManager::getSingleton(void) {
		if (msSingleton == 0) {
			//TODO: throw exception
		}

		return *msSingleton;
	}

	SoundManager* SoundManager::getSingletonPtr(void) {
		if (msSingleton == 0) {
			//TODO: throw exception
		}

		return msSingleton;
	}

	void SoundManager::init(const Ogre::String& mediaPath, const Ogre::String& mediaFile) {
		msSingleton = new SoundManager(mediaPath, mediaFile);
	}

	SoundManager::~SoundManager() {
		//Clean up
		ERRCHECK(mResult = mEventSystem->release());
	}

	void SoundManager::ERRCHECK(FMOD_RESULT result) {
		if (result != FMOD_OK) {
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << msPrefix << "ERROR: " << result << " " << FMOD_ErrorString(result);
			exit(-1);
		}
	}

	int SoundManager::start3DSound(int soundId, const Ogre::Vector3& position, const Ogre::Vector3& velocity) {
		return 0;
	}

	void SoundManager::stop3DSound(int channelId) {
		
	}

	void SoundManager::startAmbient(unsigned int ambientId) {
		//Lets see if this ambient already exists
		if (mPrompts.find(ambientId) == mPrompts.end()) {
			//Item does not exist, create it
			FMOD::MusicPrompt* newMusic;

			ERRCHECK(mResult = mMusicSystem->prepareCue(ambientId, &newMusic));

			mPrompts[ambientId] = newMusic;
		}

		//Actually start the ambient
		ERRCHECK(mResult = mPrompts[ambientId]->begin());
	}

	void SoundManager::stopAmbient(unsigned int ambientId) {
		if (mPrompts.find(ambientId) == mPrompts.end()) {
			//Does not exist...
		} else {
			ERRCHECK(mResult = mPrompts[ambientId]->end());
		}
	}

	void SoundManager::updateListenerPosition(const Ogre::Vector3& position, const Ogre::Vector3& velocity, const Ogre::Vector3& forward, const Ogre::Vector3& up) {

	}

	void SoundManager::update() {
		ERRCHECK(mResult = mEventSystem->update());
	}

}