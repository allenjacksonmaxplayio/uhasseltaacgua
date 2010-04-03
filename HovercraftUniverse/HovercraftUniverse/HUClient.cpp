#include "HUClient.h"
#include "HUApplication.h"
#include "ClientLoader.h"
#include "EntityRegister.h"
#include "Exception.h"

#include "HovercraftPlayerController.h"
#include "HovercraftAIController.h"
#include "HovercraftLoader.h"

#include "Application.h"
#include "Config.h"
#include "Lobby.h"
#include "PlayerSettings.h"
#include "RaceState.h"
#include "RacePlayer.h"

#include "AsteroidRepresentation.h"
#include "BoostRepresentation.h"
#include "CheckPointRepresentation.h"
#include "FinishRepresentation.h"
#include "HovercraftRepresentation.h"
#include "PortalRepresentation.h"
#include "StartRepresentation.h"
#include "TrackRepresentation.h"

#include "Start.h"
#include "Finish.h"
#include "Asteroid.h"
#include "Hovercraft.h"
#include "CheckPoint.h"
#include "StartPosition.h"
#include "SpeedBoost.h"
#include "Portal.h"
#include "PowerupSpawn.h"
#include "ResetSpawn.h"

#include <OgreLogManager.h>

namespace HovUni {

HUClient::HUClient(const char* name, unsigned int port) :
	NetworkClient(name, port, "HUClient"), mAddress(name), mSemaphore(0) {
	initialize();
}

HUClient::HUClient() :
	NetworkClient(2376, "HUClient"), mAddress(""), mSemaphore(0) {
	initialize();
}

void HUClient::initialize() {
	//Set chat variables to null
	mChatListener = 0;
	mChatClient = 0;

	// Create and store entity manager
	mEntityManager = EntityManager::getClientSingletonPtr();
	mIDManager = new NetworkIDManager(this);
	EntityRegister::registerAll(*mIDManager);
	ZCom_setUpstreamLimit(0, 0);

	//Create the lobby object
	mLobby = new Lobby(HUApplication::msPreparationLoader);
	mLobby->networkRegisterUnique(mIDManager, Lobby::getClassName());
}

HUClient::~HUClient() {
	delete mChatClient;
}

void HUClient::process() {
	NetworkClient::process();
	mLobby->process();

	if (mChatClient != 0) {
		mChatClient->process();
	}
}

void HUClient::ZCom_cbConnectResult(ZCom_ConnID id, eZCom_ConnectResult result,
		ZCom_BitStream& reply) {
	if (result == eZCom_ConnAccepted) {
		// Connection accepted, so request zoid level
		ZCom_requestDownstreamLimit(id, 60, 600);
		ZCom_requestZoidMode(id, 1);

		//Start the chat client
		if (mAddress == "") {
			mChatClient
					= new ChatClient(Application::getConfig()->getValue("Player", "PlayerName"));
		} else {
			mChatClient = new ChatClient(
					Application::getConfig()->getValue("Player", "PlayerName"), mAddress.c_str());
		}
		mChatClient->connect(0);

		//Check if we already have a listener
		if (mChatListener != 0) {
			mChatClient->registerListener(mChatListener);
		}

		//We are done, notify our listeners
		mSemaphore.post();
	} else {
		//Notify our listeners
		mSemaphore.post();

		// Connection failed
		THROW(NetworkException, "Connection failed");
		return;
	}
}

void HUClient::ZCom_cbConnectionClosed(ZCom_ConnID id, eZCom_CloseReason reason,
		ZCom_BitStream& reasondata) {
	// Connection closed
}

void HUClient::ZCom_cbDataReceived(ZCom_ConnID id, ZCom_BitStream& data) {
	// Data received
}

void HUClient::ZCom_cbZoidResult(ZCom_ConnID id, eZCom_ZoidResult result, zU8 new_level,
		ZCom_BitStream& reason) {
	if (result == eZCom_ZoidEnabled) {
		// Requested zoid level was confirmed
	} else {
		// Requested zoid level denied
	}
}

void HUClient::ZCom_cbNodeRequest_Dynamic(ZCom_ConnID id, ZCom_ClassID requested_class,
		ZCom_BitStream* announcedata, eZCom_NodeRole role, ZCom_NodeID net_id) {
	// Receive and create the entity
	Ogre::String name("");

	// Debug output
	Ogre::LogManager::getSingletonPtr()->getDefaultLog()->stream()
			<< "[HUClient]: Creating object of type " << mIDManager->getName(requested_class);

	//Lobby
	if (requested_class == mIDManager->getID(Lobby::getClassName())) {
		// Lobby received (upon connect)
		mLobby = new Lobby(0);
		mLobby->networkRegister(requested_class, this);
		HUApplication::msPreparationLoader->registerLoader(mLobby->getTrackFilename());
	} else if (requested_class == mIDManager->getID(PlayerSettings::getClassName())) {
		// Player
		PlayerSettings * ent = new PlayerSettings(mLobby, announcedata, requested_class, this);
		ent->processEvents(0.0f);

		// Network register is done in constructor of player settings
		Ogre::LogManager::getSingletonPtr()->getDefaultLog()->stream()
				<< "[HUClient]: adding player to lobby";
		mLobby->addPlayer(ent, ent->getID() == id);

		// Let's check if this is our own PlayerSettings object
		if (role == eZCom_RoleOwner) {
			// Put our data in it
			Config* conf = Application::getConfig();
			ent->setPlayerName(conf->getValue("Player", "PlayerName"));
			ent->setCharacter(conf->getValue("Player", "Character"));
			ent->setHovercraft(conf->getValue("Player", "Hovercraft"));
		}
	} else if (requested_class == mIDManager->getID(RaceState::getClassName())) {
		RaceState* ent = new RaceState(mLobby, HUApplication::msPreparationLoader, announcedata,
				requested_class, this);
		mLobby->setRaceState(ent);
	} else if (requested_class == mIDManager->getID(RacePlayer::getClassName())) {
		if (!mLobby->getRaceState()) {
			Ogre::LogManager::getSingletonPtr()->getDefaultLog()->stream()
					<< "[HUClient]: Error - no race state";
			THROW(NetworkException, "RaceState not received yet");
		}
		RacePlayer* ent = new RacePlayer(mLobby, announcedata, requested_class, this);
		mLobby->getRaceState()->addPlayer(ent, ent->getSettings()->getID()
				== mLobby->getOwnPlayer()->getID());
	}

	//Entities
	else if (requested_class == mIDManager->getID(Asteroid::getClassName())) {
		Asteroid * ent = new Asteroid(announcedata);
		ent->networkRegister(requested_class, this);
		mEntityManager->registerEntity(ent);
		name = ent->getName();
	} else if (requested_class == mIDManager->getID(CheckPoint::getClassName())) {
		CheckPoint * ent = new CheckPoint(announcedata);
		ent->networkRegister(requested_class, this);
		mEntityManager->registerEntity(ent);
		name = ent->getName();
	} else if (requested_class == mIDManager->getID(Start::getClassName())) {
		Start * ent = new Start(announcedata);
		ent->networkRegister(requested_class, this);
		mEntityManager->registerEntity(ent);
		name = ent->getName();
	} else if (requested_class == mIDManager->getID(StartPosition::getClassName())) {
		StartPosition * ent = new StartPosition(announcedata);
		ent->networkRegister(requested_class, this);
		mEntityManager->registerEntity(ent);
		name = ent->getName();
	} else if (requested_class == mIDManager->getID(Finish::getClassName())) {
		Finish * ent = new Finish(announcedata);
		ent->networkRegister(requested_class, this);
		mEntityManager->registerEntity(ent);
		name = ent->getName();
	} else if (requested_class == mIDManager->getID(ResetSpawn::getClassName())) {
		ResetSpawn * ent = new ResetSpawn(announcedata);
		ent->networkRegister(requested_class, this);
		mEntityManager->registerEntity(ent);
		name = ent->getName();
	} else if (requested_class == mIDManager->getID(PowerupSpawn::getClassName())) {
		PowerupSpawn * ent = new PowerupSpawn(announcedata);
		ent->networkRegister(requested_class, this);
		mEntityManager->registerEntity(ent);
		name = ent->getName();
	} else if (requested_class == mIDManager->getID(SpeedBoost::getClassName())) {
		SpeedBoost * ent = new SpeedBoost(announcedata);
		ent->networkRegister(requested_class, this);
		mEntityManager->registerEntity(ent);
		name = ent->getName();
	} else if (requested_class == mIDManager->getID(Portal::getClassName())) {
		Portal * ent = new Portal(announcedata);
		ent->networkRegister(requested_class, this);
		mEntityManager->registerEntity(ent);
		name = ent->getName();
	} else if (requested_class == mIDManager->getID(Hovercraft::getClassName())) {
		Hovercraft * ent = 0;

		if (role == eZCom_RoleOwner) {
			ent = new Hovercraft(announcedata);
			ent->setController(new HovercraftPlayerController());
		} else {
			ent = new Hovercraft(announcedata);
			HovercraftAIController* ai = new HovercraftAIController("scripts/AI/Pathfinding.lua");
			ent->setController(ai);
			ai->initialize();
		}

		ent->networkRegister(requested_class, this);
		mEntityManager->registerEntity(ent);

		if (role == eZCom_RoleOwner) {
			mEntityManager->trackEntity(ent->getName());
		}

		// Visualize the hovercraft
		HovercraftLoader hovLoader(HUApplication::msSceneMgr, ent->getName());
		hovLoader.load(ent->getDisplayName() + ".scene");
		//HovercraftRepresentation * test = new HovercraftRepresentation(ent,HUApplication::msSceneMgr,"hover1.mesh","General",true,true,500,"hover1.material",std::vector<Ogre::String>());
		//RepresentationManager::getSingletonPtr()->addEntityRepresentation(test);
	}

	if (!name.empty()) {
		// Now that we have created the entity, notify the client preparation loader of the arrival
		HUApplication::msPreparationLoader->update(name);
	}

}

void HUClient::start() {
	if (mLobby) {
		mLobby->start();
	}
}

void HUClient::setChatListener(ChatListener* listener) {
	mChatListener = listener;
	if (mChatClient != 0) {
		mChatClient->registerListener(mChatListener);
	}
}

void HUClient::wait() {
	mSemaphore.wait();
}

}
