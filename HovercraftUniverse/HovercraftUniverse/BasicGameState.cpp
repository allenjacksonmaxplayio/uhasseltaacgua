#include "BasicGameState.h"

namespace HovUni {
	void BasicGameState::setManager(GameStateManager* manager) {
		mManager = manager;
	}

	void BasicGameState::switchGameState(GameStateManager::GameState state) {
		mManager->switchState(state);
	}
}