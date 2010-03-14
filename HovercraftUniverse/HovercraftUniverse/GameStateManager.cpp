#include "GameStateManager.h"

#include "BasicGameState.h"

namespace HovUni {
	GameStateManager::GameStateManager(GameState initialState) : mCurrentState(initialState) {
		//Make sure all game states are initialised to null
		mGameStates[MAIN_MENU] = 0;
		mGameStates[LOBBY] = 0;
		mGameStates[IN_GAME] = 0;
	}

	void GameStateManager::addGameState(GameState state, BasicGameState* gameState) {
		//TODO: check for duplicates
		mGameStates[state] = gameState;

		// Register ourselfs to the gamestate
		gameState->setManager(this);
	}

	void GameStateManager::onFrame(const Ogre::FrameEvent& evt) {
		BasicGameState* currState = mGameStates[mCurrentState];

		if (currState != 0) {
			currState->onFrame(evt);
		} else {
			//Maybe notify?
		}
	}

	void GameStateManager::switchState(GameState state) {
		//Notify the previous one of deactivation
		BasicGameState* currState = mGameStates[mCurrentState];

		if (currState != 0) {
			currState->disable();
		} else {
			//Maybe notify?
		}

		//Set the new state as active
		mCurrentState = state;

		currState = mGameStates[mCurrentState];

		if (currState != 0) {
			currState->activate();
		} else {
			//Maybe notify?
		}
	}
}