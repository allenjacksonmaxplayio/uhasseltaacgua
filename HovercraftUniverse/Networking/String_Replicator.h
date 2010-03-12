#ifndef STRING_REPLICATOR_H
#define STRING_REPLICATOR_H

#include <OgreString.h>
#include <zoidcom/zoidcom.h>

namespace HovUni {
	/**
	 * A class that implements a zoidcom replicator object to be able to
	 * replicate Ogre::String objects with ease.
	 *
	 * @autor Pieter-Jan Pintens
	 */
	class String_Replicator : public ZCom_ReplicatorBasic {
		private:

			static const int BUFFERSIZE = 512;

			/** The real data to be synchronised */
			Ogre::String * mData;

			/** A replica to discover changes */
			Ogre::String mCompare;

			/** An internal buffer */
			char mBuffer[BUFFERSIZE];

		public:
			/// constructor, taking a ZCom_ReplicatorSetup pointer
			String_Replicator(Ogre::Vector3 *data, ZCom_ReplicatorSetup *_setup);

			/// constructor, builds the replicatorsetup automatically
			String_Replicator(Ogre::Vector3 *data, zU8 _flags, zU8 _rules, zU8 _intercept_id = 0, zS16 _mindelay = -1, zS16 _maxdelay = -1);

			virtual ~String_Replicator();

			bool checkState();

			void packData(ZCom_BitStream *_stream);

			void unpackData(ZCom_BitStream *_stream, bool _store, zU32 _estimated_time_sent);

			void* peekData();

			void clearPeekData();

			void Process(eZCom_NodeRole _localrole, zU32 _simulation_time_passed);
	};
}

#endif