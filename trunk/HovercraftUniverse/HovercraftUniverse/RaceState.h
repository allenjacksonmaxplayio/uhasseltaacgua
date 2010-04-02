#ifndef _RACESTATE_H
#define _RACESTATE_H

#include "HUClient.h"

namespace HovUni {
	/**
	 * RaceState will be the main controlling component during the game.
	 * It will manage the game state, handle game events and take care of all the
	 * game logic.
	 */
	class RaceState {
		public:
			/** All the possible stated during the race */
			static const enum States {
				INITIALIZING = 0, /** Pre-race state, show intro */
				RACE_START, /** The race will start, show countdown */
				RACING, /** The race has started */
				FINISHING, /** Someone has finished, wait for everyone to finish */
				ROUNDUP /** Everyone has finished, show some stats and return to lobby */
			};

		private:
			/** the current state of the race */
			States mCurrentState;

		public:
			/**
			 * Constructor
			 */
			RaceState();

			/**
			 * Destructor
			 */
			virtual ~RaceState();
		
	};
}

#endif //_RACESTATE_H