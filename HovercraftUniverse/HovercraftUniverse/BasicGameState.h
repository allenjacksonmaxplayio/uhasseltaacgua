#ifndef BASICGAMESTATE_H
#define BASICGAMESTATE_H

#include "GameStateManager.h"

namespace HovUni {
	/**
	 * A class to represent a game state. Specific states should be derived
	 * from this basic class
	 */
	class BasicGameState {
		protected:
			/** A reference to the GameStateManager */
			GameStateManager* mManager;

		public:
			/**
			 * Function called when the state gets activated
			 */
			virtual void activate() = 0;

			/**
			 * Function called when the state gets disabled
			 */
			virtual void disable() = 0;

			/**
			 * Function called every frame, do drawing functions and stuff in here
			 */
			virtual void onFrame(const Ogre::FrameEvent& evt) = 0;

			/**
			 * Initialise the manager for this game state
			 */
			void setManager(GameStateManager* manager);

		protected:
			/**
			 * Switch to a new gamestate
			 */
			void switchGameState(GameStateManager::GameState state);
	};
}

#endif //BASICGAMESTATE_H