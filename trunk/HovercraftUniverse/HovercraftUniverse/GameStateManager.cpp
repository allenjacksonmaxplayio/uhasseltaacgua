#include "GameStateManager.h"

#include "BasicGameState.h"

namespace HovUni {
	GameStateManager::GameStateManager(InputManager * inputMgr, GameState initialState, BasicGameState* gameState) 
			: mInputManager(inputMgr), mCurrentState(initialState), mCurrentGameState(gameState) {
		//Make sure all game states are initialised to null
		mGameStates[MAIN_MENU] = 0;
		mGameStates[LOBBY] = 0;
		mGameStates[IN_GAME] = 0;

		//Register ourselves to the input manager
		mInputManager->addKeyListener(this, "GameStateManager");
		mInputManager->addMouseListener(this, "GameStateManager");

		//Store the initial state
		addGameState(initialState, gameState);
		//Activate it
		gameState->activate();
	}

	void GameStateManager::addGameState(GameState state, BasicGameState* gameState) {
		//TODO: check for duplicates
		mGameStates[state] = gameState;

		// Register ourselfs to the gamestate
		gameState->setManager(this);
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
			//TODO: Maybe notify?
		}
	}

	bool GameStateManager::frameStarted(const Ogre::FrameEvent & evt) {
		//Update the input manager
		mInputManager->capture();

		if (mCurrentGameState) {
			return mCurrentGameState->frameStarted(evt);
		}
		return true; //Default return
	}

	bool GameStateManager::mouseMoved(const OIS::MouseEvent & e) {
		if (mCurrentGameState) {
			return mCurrentGameState->mouseMoved(e);
		}
		return true; //Default return
	}

	bool GameStateManager::mousePressed(const OIS::MouseEvent & e, OIS::MouseButtonID id) {
		if (mCurrentGameState) {
			return mCurrentGameState->mousePressed(e, id);
		}
		return true; //Default return
	}

	bool GameStateManager::mouseReleased(const OIS::MouseEvent & e, OIS::MouseButtonID id) {
		if (mCurrentGameState) {
			return mCurrentGameState->mouseReleased(e, id);
		}
		return true; //Default return
	}

	bool GameStateManager::keyPressed(const OIS::KeyEvent & e) {
		if (mCurrentGameState) {
			return mCurrentGameState->keyPressed(e);
		}
		return true; //Default return
	}

	bool GameStateManager::keyReleased(const OIS::KeyEvent & e) {
		if (mCurrentGameState) {
			return mCurrentGameState->keyReleased(e);
		}
		return true; //Default return
	}
}