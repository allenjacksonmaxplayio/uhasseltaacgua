#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <map>

#include <Ogre.h>

namespace HovUni {
	class BasicGameState; //Forward declaration

	/**
	 * This class manages the different gamestates.
	 * For example: MainMenu, SinglePlayer, Multiplayern, ...
	 *
	 * @author Nick De Frangh
	 */
	class GameStateManager {
		public:
			/** Enumeration for all possible gamestates */
			static enum GameState {
				MAIN_MENU = 0, LOBBY, IN_GAME
			};

		private:
			/** A map containing all the regitered game states */
			std::map<GameState, BasicGameState*> mGameStates;

			/** The current state of the game */
			GameState mCurrentState;

		public:
			/** 
			 * Basic constructor
			 */
			GameStateManager(GameState initialState = MAIN_MENU);

			/**
			 * Add a new gamestate to the manager
			 *
			 * @param state The identifier for this type of state
			 * @param gameState The implementation for this game state
			 */
			void addGameState(GameState state, BasicGameState* gameState);

			/**
			 * This function should be called every frame to make
			 * changes possible. This will update the current active
			 * GameState.
			 *
			 * @param evt The FrameEvent given by Ogre.
			 */
			void onFrame(const Ogre::FrameEvent& evt);

			/**
			 * Switch to a new state, can only be accessed by friend
			 * classes (the game states).
			 *
			 * @param state The new stat to switch to
			 */
			void switchState(GameState state);
	};
}

#endif //GAMESTATEMANAGER_H