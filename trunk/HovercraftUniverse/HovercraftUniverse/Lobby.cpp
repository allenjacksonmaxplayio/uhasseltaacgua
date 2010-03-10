#include "Lobby.h"

namespace HovUni {

std::string Lobby::getClassName() { 
	return "Lobby";
}

Lobby::Lobby(): NetworkEntity(),mTrackFilename(""), mMaximumPlayers(8) {

}

Lobby::~Lobby(void) {

}

bool Lobby::onConnectAttempt() {
	//TODO lock mutex
	return mMaximumPlayers >= mCurrentPlayers;
}

void Lobby::onConnect(ZCom_ConnID id) {
	//TODO lock mutex

	// Request extra info
	if (!mHasAdmin){
		mAdmin = id;
		getNetworkNode()->setOwner(mAdmin, true);
		mHasAdmin = true;
	}
	
	// Add player to map
	mPlayers.insert(std::pair<ZCom_ConnID,Player*>(id,new Player(id)));
	mCurrentPlayers++;
}

void Lobby::onDisconnect(ZCom_ConnID id) {
	//TODO lock mutex

	// Remove from map
	std::map<ZCom_ConnID,Player*>::iterator i =  mPlayers.find(id);
	delete i->second;
	mPlayers.erase(i);
	mCurrentPlayers--;

	// Check if new admin is needed
	if (mAdmin == id) {
		
		// Check if players remain
		if (mPlayers.empty()) {
			// Set admin to false if no player remain
			mHasAdmin = false;
		}
		else {
			// Set new admin
			mAdmin = mPlayers.begin()->first;
			getNetworkNode()->setOwner(mAdmin, true);
		}
	}
}

void Lobby::onTrackChange(const Ogre::String& filename) {
	mTrackFilename = filename;
}

void Lobby::onStart() {
	//called when map should be loaded
	//World::creat();	
}

void Lobby::onPlayerCharacterChange( ZCom_ConnID id, const Ogre::String& character  ){
	mPlayers[id]->setCharacter(character);
}

void Lobby::onPlayerHovercraftChange( ZCom_ConnID id, const Ogre::String& hovercraft  ){
	mPlayers[id]->setHovercraft(hovercraft);
}

void Lobby::parseEvents(ZCom_BitStream* stream, float timeSince) {

}

void Lobby::setupReplication() {

}

}