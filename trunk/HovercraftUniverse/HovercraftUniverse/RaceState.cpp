#include "RaceState.h"
#include "Lobby.h"
#include "Loader.h"

namespace HovUni {

RaceState::RaceState(Lobby* lobby, Loader* loader, Ogre::String track) :
	NetworkEntity(0), mCurrentState(INITIALIZING), mLobby(lobby), mLoader(loader), mTrackFilename(
			track) {

	// Add as network entity
	networkRegister(NetworkIDManager::getServerSingletonPtr(), getClassName(), true);

	// Load the track on the server
	mLoader->load(mTrackFilename);
}

RaceState::RaceState(Lobby* lobby, ZCom_BitStream* announcementdata, ZCom_ClassID id,
		ZCom_Control* control) :
	NetworkEntity(0), mCurrentState(INITIALIZING), mLobby(lobby), mLoader(0), mTrackFilename(
			announcementdata->getString()) {

	// Add as network entity
	networkRegister(id, control);
}

RaceState::~RaceState() {

}

std::string RaceState::getClassName() {
	return "RaceState";
}

void RaceState::setAnnouncementData(ZCom_BitStream* stream) {
	stream->addString(mTrackFilename.c_str());
}

void RaceState::parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id,
		ZCom_BitStream* stream, float timeSince) {

}

void RaceState::setupReplication() {
}

}
