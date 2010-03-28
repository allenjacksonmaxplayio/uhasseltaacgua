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

	void LobbyOverlay::addUser(int id, const std::string& username, const std::string& character, const std::string& car) {
		this->callFunction("addUser", Hikari::Args(id)(username)(character)(car));
	}

	void LobbyOverlay::editUser(int id, const std::string& username, const std::string& character, const std::string& car) {
		this->callFunction("editUser", Hikari::Args(id)(username)(character)(car));
	}

	void LobbyOverlay::deleteUser(int id) {
		this->callFunction("deleteUser", Hikari::Args(id));
	}

	void LobbyOverlay::customActionAfterActivate() {
		this->focus();
	}
}