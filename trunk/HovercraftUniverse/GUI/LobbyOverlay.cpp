#include "LobbyOverlay.h"

namespace HovUni {
	LobbyOverlay::LobbyOverlay(const Hikari::FlashDelegate& chatInput, const Hikari::FlashDelegate& botsValue, const Hikari::FlashDelegate& playerMax, const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder) 
			: BasicOverlay(name, fileName, width, height, position, zOrder) {
		this->bind("chatInput", chatInput);
		this->bind("botsValue", botsValue);
		this->bind("playerMax", playerMax);
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

	void LobbyOverlay::setAdmin(bool admin) {
		this->callFunction("setAdmin", Hikari::Args(admin));
	}

	void LobbyOverlay::markAdmin(int id) {
		this->callFunction("markAdmin", Hikari::Args(id));
	}

	void LobbyOverlay::setFillBots(bool fill) {
		this->callFunction("setFillBots", Hikari::Args(fill));
	}

	void LobbyOverlay::setPlayerMax(int value) {
		this->callFunction("setPlayerMax", Hikari::Args(value));
	}

	void LobbyOverlay::customActionAfterActivate() {
		this->focus();
	}
}