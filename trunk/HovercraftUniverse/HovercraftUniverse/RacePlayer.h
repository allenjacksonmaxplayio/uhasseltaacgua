#ifndef _RACEPLAYER_H
#define _RACEPLAYER_H

#include "PlayerSettings.h"

namespace HovUni {
	class RacePlayer {
		private:
			/** The general player settings and data */
			PlayerSettings* mPlayerSettings;

			/** The current position of this player in the race */
			short mPlayerPosition;

		public:
			/**
			 * Constructor for a RacePlayer
			 *
			 * @param playerSettings The general settings for this player
			 */
			RacePlayer(PlayerSettings* playerSettings);

			void onCheckpoint();

			void onFinish();
			
			short getPosition();
	};
}

#endif //_RACEPLAYER_H