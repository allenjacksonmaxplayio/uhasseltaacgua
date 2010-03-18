#include "Lobby.h"
#include "EntityManager.h"
#include "NetworkIDManager.h"
#include "String_Replicator.h"
#include "GameEventParser.h"
#include "DummyHovercraft.h"
#include "Loader.h"

namespace HovUni {

std::string Lobby::getClassName() { 
	return "Lobby";
}

Lobby::Lobby(Loader * loader): NetworkEntity(4), mLoader(loader), mHasAdmin(false), mTrackFilename("SimpleTrack.scene"), mMaximumPlayers(2), mStarted(false), mCurrentPlayers(0) {
	if (loader) {
		loader->setLobby(this);
	}
}

Lobby::~Lobby(void) {
	if ( mLoader )
		delete mLoader;
}

void Lobby::start() {
	// TODO
	//if(mNode->getRole() == eZCom_RoleOwner) {
		StartTrackEvent event;
		sendEvent(event);
	//} else {
	//	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "send denied";
	//}
}

bool Lobby::isAdmin() const {
	return (mNode->getRole() == eZCom_RoleOwner);
}

bool Lobby::onConnectAttempt(ZCom_ConnID id) {
	//TODO lock mutex

	if(mCurrentPlayers < mMaximumPlayers) {
		return true;
	}
	return false;
}

void Lobby::onConnect(ZCom_ConnID id) {
	//TODO lock mutex

	// Request extra info
	if(!mHasAdmin){
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
	if(mAdmin == id) {
		
		// Check if players remain
		if(mPlayers.empty()) {
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
	// For now just create a dummy hovercraft for each player
	// TODO Move somewhere else
	if(!mStarted) {
		// TODO This is only called on the server. The client should wait for entities before being able to process them, so in fact the loader is only required
		// at the server side of the lobby. Therefore i would recommend to move this to a server specific class, so that lobby does not need a loader anymore, but
		// just the track name. For now, i will pass 0 as loader for the client Lobby
		//called when map should be loaded
		mLoader->load(mTrackFilename);

		/*NetworkIDManager* idmanager = NetworkIDManager::getServerSingletonPtr();
		for(std::map<ZCom_ConnID,Player*>::iterator it = mPlayers.begin(); it != mPlayers.end(); ++it) {
			DummyHovercraft * hovercraft = new DummyHovercraft();
			hovercraft->networkRegister(idmanager, "DummyHovercraft");
			hovercraft->getNetworkNode()->setOwner(it->first, true);
			EntityManager::getServerSingletonPtr()->registerEntity(hovercraft);
		}*/
		mStarted = true;
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Start event received and processed";
	}
}

void Lobby::onPlayerCharacterChange(ZCom_ConnID id, const Ogre::String& character ){
	mPlayers[id]->setCharacter(character);
}

void Lobby::onPlayerHovercraftChange(ZCom_ConnID id, const Ogre::String& hovercraft ){
	mPlayers[id]->setHovercraft(hovercraft);
}

void Lobby::parseEvents(ZCom_BitStream* stream, float timeSince) {
	GameEventParser p;
	GameEvent* event = p.parse(stream);
	eZCom_NodeRole role = mNode->getRole();
	switch(role) {
		case eZCom_RoleAuthority:
			processEventsServer(event);
			break;
		case eZCom_RoleOwner:
			processEventsOwner(event);
			break;
		case eZCom_RoleProxy:
			processEventsOther(event);
			break;
		default:
			break;
	}
	delete event;
}

void Lobby::processEventsServer(GameEvent* event) {
	// Save the new event in the moving status
	StartTrackEvent* start = dynamic_cast<StartTrackEvent*>(event);
	if(start) {
		onStart();
	}
}

void Lobby::processEventsOwner(GameEvent* event) {

}

void Lobby::processEventsOther(GameEvent* event) {

}

void Lobby::setupReplication() {

	//track filename
	mNode->addReplicator(new String_Replicator(&mTrackFilename,ZCOM_REPFLAG_MOSTRECENT,ZCOM_REPRULE_AUTH_2_ALL),true);

	//mAdmin
	mNode->addReplicationInt((zS32*)&mAdmin,	// pointer to the variable
	sizeof(ZCom_ConnID) * 8,					// amount of bits(full)
    false,										// unsigned
    ZCOM_REPFLAG_MOSTRECENT,					// always send the most recent value only
    ZCOM_REPRULE_AUTH_2_ALL						// server sends to all clients
	);

	//mCurrentPlayers
	mNode->addReplicationInt(&mCurrentPlayers,	// pointer to the variable
    8,											// amount of bits(up to 255 players)
    false,										// unsigned
    ZCOM_REPFLAG_MOSTRECENT,					// always send the most recent value only
    ZCOM_REPRULE_AUTH_2_ALL						// server sends to all clients
	);

	//mMaximumPlayers
	mNode->addReplicationInt(&mMaximumPlayers,	// pointer to the variable
    8,											// amount of bits(up to 255 players)
    false,										// unsigned
    ZCOM_REPFLAG_MOSTRECENT,					// always send the most recent value only
    ZCOM_REPRULE_AUTH_2_ALL						// server sends to all clients
	);
}

void Lobby::setAnnouncementData(ZCom_BitStream* stream) {

}

}