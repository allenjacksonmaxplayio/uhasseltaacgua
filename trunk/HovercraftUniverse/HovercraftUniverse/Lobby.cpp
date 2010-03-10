#include "Lobby.h"

namespace HovUni {

Lobby::Lobby(void):
	NetworkEntity(),mTrackFilename(""), mMaximumPlayers(8)
{
}

Lobby::~Lobby(void)
{
}

bool Lobby::onConnectAttempt ( ){
	//TODO lock mutex
	return mMaximumPlayers >= mCurrentPlayers;
}

void Lobby::onConnect( ZCom_ConnID id ) {
	//TODO lock mutex

	//request extra info
	if ( !mHasAdmin ){
		mAdmin = id;

		//TODO ZOIDCOM MAKE IT OWNER OF THE Lobby
	}
	
	//add player to map
	mPlayers.insert(std::pair<ZCom_ConnID,Player*>(id,new Player(id)));
	mCurrentPlayers++;
}

void Lobby::onDisconnect ( ZCom_ConnID id ) {
	//TODO lock mutex

	//remove from map
	std::map<ZCom_ConnID,Player*>::iterator i =  mPlayers.find ( id );
	delete i->second;
	mPlayers.erase(i);
	mCurrentPlayers--;

	//if admin set new admin
	if ( mAdmin == id ){
		
		//check if players remain
		if ( mPlayers.empty() ){
			//set admin to false if no player remain
			mHasAdmin = false;
		}
		else {
			//set new admin
			mAdmin = mPlayers.begin()->first;

			//TODO ZOIDCOM MAKE IT OWNER OF THE Lobby
		}
	}
}

void Lobby::onMapChange( const Ogre::String& filename ){
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