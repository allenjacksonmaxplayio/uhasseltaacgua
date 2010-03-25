#include "LobbyOverlay.h"

namespace HovUni {
	LobbyOverlay::LobbyOverlay(const Hikari::FlashDelegate& chatInput, const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder) 
			: BasicOverlay(name, fileName, width, height, position, zOrder) {
		this->bind("chatInput", chatInput);
		setBParameter(BasicOverlay::ALPHAHACK, true);
	}

	void LobbyOverlay::addText(const Ogre::String& username, const Ogre::String& message) {
		this->callFunction("addText", Hikari::Args(username)(message));
	}

	void LobbyOverlay::addAction(const Ogre::String& message) {
		this->callFunction("addAction", Hikari::Args(message));
	}

	void LobbyOverlay::customActionAfterActivate() {
		this->focus();
	}
}