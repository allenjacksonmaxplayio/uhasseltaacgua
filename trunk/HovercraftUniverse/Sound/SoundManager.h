#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <map>
#include <OgreVector3.h>
#include <OgreString.h>
#include <fmod.hpp>
#include <fmod_event.hpp>
#include <fmod_errors.h>

namespace HovUni {
	class SoundManager {
		private:
			/** 
			 * A HashMap which contains a reference between ID's and Sounds.
			 * This will abstract the Sounds from a user by just using
			 * a simple identifier.
			 */
			std::map<int, FMOD::Sound> mSounds;

			FMOD::EventSystem * mEventSystem;
			FMOD::MusicSystem * mMusicSystem;
			
		public:
			/**
			 * Base constructor for the SoundManager.
			 *
			 * @param mediaPath The path to where all the sound media files are located.
			 */
			SoundManager(const Ogre::String& mediaPath);
			
			/**
			 * Virtual desctructor for the SoundManager.
			 */
			virtual ~SoundManager();
			
			/**
			 * Start playing a sound in the 3D space at a given location
			 * with a given velocity
			 *
			 * @param soundId The ID of the sound you want to start
			 * @param position The position where you want to sound to be originating from
			 * @param velocity The velocity of the sound source (default is a static source)
			 * @return A new channel ID to reference the newly created sound channel
			 */
			int start3DSound(int soundId, const Ogre::Vector3& position, const Ogre::Vector3& velocity);
		
			/**
			 * Stop a certain sound source from playing
			 *
			 * @param channelId The source you want to stop playing (this is an ID obtained
			 *		by calling {@link #<start3DSound> start3DSound} to start the sound first)
			 */
			void stop3DSound(int channelId);
		
			/**
			 * Add a new ambient sound to the stack (this is the background music)
			 *
			 * @param ambientId The ID of the abient sound to push onto the stack
			 */
			void pushAmbient(int ambientId);
		
			/**
			 * Remove and ambient sound from the stack
			 *
			 * @param ambientId The ID of the abient sound to pop from the stack
			 */
			void popAmbient(int ambientId);
		
			/**
			 * Update the position of the listener, this should be called everytime a new frame 
			 * has been calculated.
			 *
			 * @param position The new position of the listener.
			 *		Can be 0 to not update the position
			 * @param velocity The velocity of the listener <strong>in distance units per second (m/s)</strong>.
			 *		Default is 0 --> dont update the velocity
			 * @param forward The forwards orientation of the listener, must be of unit length and perpendicular to the up vector.
			 *		Default is 0 --> dont update the forwards orientation
			 * @param up The upwards orientation of the listener, must be of unit length and perpendicular to the forward vector.
			 *		Default is 0 --> dont update hte upwards orientation
			 */
			void updateListenerPosition(const Ogre::Vector3& position, const Ogre::Vector3& velocity, const Ogre::Vector3& forward, const Ogre::Vector3& up);
	};
}

#endif //SOUNDMANAGER_H