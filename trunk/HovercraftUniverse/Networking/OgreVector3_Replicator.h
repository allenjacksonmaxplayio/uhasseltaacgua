#ifndef OGREVECTOR3_REPLICATOR_H
#define OGREVECTOR3_REPLICATOR_H

#include <OgreVector3.h>
#include <zoidcom/zoidcom.h>

namespace HovUni {
	class OgreVector3_Replicator : public ZCom_ReplicatorBasic {
		private:
			/** The real data to be synchronised */
			Ogre::Vector3* mData;

			/** A replica to discover changes */
			Ogre::Vector3 mCompare;

			/** The number of mantissa bits you want to synchronise */
			zU8 mMantissaBits;

		public:
			/// constructor, taking a ZCom_ReplicatorSetup pointer
			OgreVector3_Replicator(Ogre::Vector3 *data, ZCom_ReplicatorSetup *_setup, zU8 mantissa = 10);

			/// constructor, builds the replicatorsetup automatically
			OgreVector3_Replicator(Ogre::Vector3 *data, zU8 mantissa, zU8 _flags, zU8 _rules, zU8 _intercept_id = 0, zS16 _mindelay = -1, zS16 _maxdelay = -1);

			virtual ~OgreVector3_Replicator();

			bool checkState();

			void packData(ZCom_BitStream *_stream);

			void unpackData(ZCom_BitStream *_stream, bool _store, zU32 _estimated_time_sent);

			void* peekData();

			void clearPeekData();

			void Process(eZCom_NodeRole _localrole, zU32 _simulation_time_passed);
	};
}

#endif //OGREVECTOR3_REPLICATOR_H