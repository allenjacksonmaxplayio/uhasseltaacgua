#ifndef OGREQUATERNION_REPLICATOR_H
#define OGREQUATERNION_REPLICATOR_H

#include <OgreQuaternion.h>
#include <zoidcom/zoidcom.h>

namespace HovUni {
	/**
	 * A class that implements a zoidcom replicator object to be able to
	 * replicate Ogre::Vector3 objects with ease.
	 *
	 * @autor Nick De Frangh
	 */
	class OgreQuaternion_Replicator : public ZCom_ReplicatorBasic {
		private:
			/** The real data to be synchronised */
			Ogre::Quaternion* mData;

			/** A replica to discover changes */
			Ogre::Quaternion mCompare;

			/** The number of mantissa bits you want to synchronise */
			zU8 mMantissaBits;

		public:
			/// constructor, taking a ZCom_ReplicatorSetup pointer
			OgreQuaternion_Replicator(Ogre::Quaternion *data, ZCom_ReplicatorSetup *_setup, zU8 mantissa = 10);

			/// constructor, builds the replicatorsetup automatically
			OgreQuaternion_Replicator(Ogre::Quaternion *data, zU8 mantissa, zU8 _flags, zU8 _rules, zU8 _intercept_id = 0, zS16 _mindelay = -1, zS16 _maxdelay = -1);

			virtual ~OgreQuaternion_Replicator();

			bool checkState();

			void packData(ZCom_BitStream *_stream);

			void unpackData(ZCom_BitStream *_stream, bool _store, zU32 _estimated_time_sent);

			void* peekData();

			void clearPeekData();

			void Process(eZCom_NodeRole _localrole, zU32 _simulation_time_passed);
	};
}

#endif //OGREQUATERNION_REPLICATOR_H