#include "CustomOgreMaxScene.h"
#include "Exception.h"
#include "EntityDescription.h"
#include "DedicatedServer.h"
#include "GameEntities.h"

//Race state
#include "RaceState.h"
#include "RacePlayer.h"
#include "PlayerSettings.h"
#include "NetworkIDManager.h"
#include "EntityManager.h"
#include "HovercraftAIController.h"

// Physics
#include "Havok.h"
#include "HoverCraftUniverseWorld.h"

namespace HovUni {

ServerLoader::ServerLoader() :
	mHovercraftWorld(0), mLoadingHovercrafts(false) {
	mUserDataFactory.addUserDataCallback(this);
}

ServerLoader::~ServerLoader(void) {
	mUserDataFactory.removeUserDataCallback(this);
}

void ServerLoader::load(const Ogre::String& filename) {
	Havok::start(filename.c_str(), this);
}

void ServerLoader::onSceneUserData(const Ogre::String& userDataReference, const Ogre::String& userData) {
	if (!userData.empty()) {
		EntityDescription desc("Track", Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
		mUserDataFactory.parseUserData(userData, desc);
	}
}

void ServerLoader::onExternal(OgreMax::Types::ExternalItem& externalitem) {
	mExternalitem = &externalitem;
	if (!externalitem.userData.empty()) {
		EntityDescription desc(externalitem.name, externalitem.position, externalitem.rotation);
		mUserDataFactory.parseUserData(externalitem.userData, desc);
	}
	mExternalitem = 0;
}

void ServerLoader::onEntity(OgreMax::Types::EntityParameters& entityparameters, const OgreMax::Types::Attachable * parent) {
	//should be called when loading hovercrafts
	if (mLoadingHovercrafts) {
		if (!entityparameters.extraData.isNull() && entityparameters.extraData->HasUserData()) {
			mCurrentHovercraft = entityparameters.name;
			Ogre::String name = mPlayer->getSettings()->getPlayerName() + "_" + Ogre::StringConverter::toString(mPosition);
			EntityDescription desc(name, Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
			mUserDataFactory.parseUserData(entityparameters.extraData->userData, desc);
		}
	}
}

void ServerLoader::StartedLoad() {
	setLoading(true);
}

void ServerLoader::FinishedLoad(bool success) {

	if (mLoadingHovercrafts) {
		return;
	}

	if (success) {
		//add players
		const RaceState::playermap::list_type& map = mRaceState->getPlayers();

		mLoadingHovercrafts = true;

		int j = 0;
		for (RaceState::playermap::const_iterator i = map.begin(); i != map.end(); i++) {
			//set player and position
			mPlayer = i->second;
			mPosition = j;

			//call hovercraft loader
			CustomOgreMaxScene scene;
			scene.Load(mPlayer->getSettings()->getHovercraft() + ".scene", this);

			j++;
		}

		mLoadingHovercrafts = false;
	}

	setLoading(false);
}

void ServerLoader::onTrack(Track * track) {
	//TODO USE OGRE RESOURCES

	Ogre::String filename = ".\\levels\\" + track->getPhysicsFileName();

	mHovercraftWorld = Havok::getSingletonPtr();

	const char * physicsfile = filename.c_str();
	if (!mHovercraftWorld->load(physicsfile)) {
		//loading failed
		THROW(ParseException, "Could not load our physics file.");
	}

	delete track;
}

void ServerLoader::onAsteroid(Asteroid * asteroid) {
	if (mExternalitem == 0) {
		THROW(ParseException, "This should be an external item.");
	}

	//create Physics
	mHovercraftWorld->createAsteroid(asteroid,mExternalitem);

	//add to entity manager
	EntityManager::getServerSingletonPtr()->registerEntity(asteroid);

	//network register asteroid
	asteroid->networkRegister(NetworkIDManager::getServerSingletonPtr(), Asteroid::getClassName(), true);
}

void ServerLoader::onStart(Start * start) {
	if (!mExternalitem) {
		THROW(ParseException, "This should be an external item.");
	}

	//create start
	mHovercraftWorld->createStart(start, mExternalitem);

	//add to entity manager
	EntityManager::getServerSingletonPtr()->registerEntity(start);

	//network register asteroid
	start->networkRegister(NetworkIDManager::getServerSingletonPtr(), Start::getClassName(), true);
}

void ServerLoader::onStartPosition(StartPosition * startposition) {
	if (!mExternalitem) {
		THROW(ParseException, "This should be an external item.");
	}

	//add to entity manager
	EntityManager::getServerSingletonPtr()->registerEntity(startposition);

	//network register asteroid
	startposition->networkRegister(NetworkIDManager::getServerSingletonPtr(), StartPosition::getClassName(), true);
}

void ServerLoader::onCheckPoint(CheckPoint * checkpoint) {
	if (!mExternalitem) {
		THROW(ParseException, "This should be an external item.");
	}

	//create Physics
	mHovercraftWorld->createCheckpoint(checkpoint,mExternalitem);

	//add to entity manager
	EntityManager::getServerSingletonPtr()->registerEntity(checkpoint);

	//network register asteroid
	checkpoint->networkRegister(NetworkIDManager::getServerSingletonPtr(), CheckPoint::getClassName(), true);
}

void ServerLoader::onFinish(Finish * finish) {
	if (!mExternalitem) {
		THROW(ParseException, "This should be an external item.");
	}

	mHovercraftWorld->createFinish(finish,mExternalitem);

	//add to entity manager
	EntityManager::getServerSingletonPtr()->registerEntity(finish);

	//network register asteroid
	finish->networkRegister(NetworkIDManager::getServerSingletonPtr(), Finish::getClassName(), true);
}

void ServerLoader::onHoverCraft(Hovercraft * hovercraft) {
	Ogre::String filename = ".\\hovercraft\\" + mPlayer->getSettings()->getHovercraft() + ".hkx";
	hkString hovercraftname(filename.c_str());

	// TODO Is this the correct place to add the AI controller?
	if (mPlayer->isBot()) {
		HovercraftAIController* ai = new HovercraftAIController(DedicatedServer::getConfig()->getValue("Server", "BotAI", "scripts/AI/PathFollowing.lua"));
		hovercraft->setController(ai);
		ai->initialize();
	}

	//Get the start positions
	std::vector<Entity*> startpositions = EntityManager::getServerSingletonPtr()->getEntities(StartPosition::CATEGORY);
	StartPosition * myposition = dynamic_cast<StartPosition *>(startpositions.at(mPosition));
	Ogre::Vector3 ogre_position = myposition->getPosition();
	hkVector4 havok_position;
	havok_position.set(ogre_position[0],ogre_position[1],ogre_position[2]);

	mHovercraftWorld->addHovercraft(hovercraft, hovercraftname, mCurrentHovercraft.c_str(), havok_position);
	EntityManager::getServerSingletonPtr()->registerEntity(hovercraft);

	hovercraft->changePosition(ogre_position);
	hovercraft->getNetworkNode()->setOwner(mPlayer->getSettings()->getID(), true);
	hovercraft->networkRegister(NetworkIDManager::getServerSingletonPtr(), Hovercraft::getClassName(), true);
}

void ServerLoader::onPortal(Portal * portal) {
	if (!mExternalitem) {
		THROW(ParseException, "This should be an external item.");
	}

	mHovercraftWorld->createPortal(portal,mExternalitem);

	//add to entity manager
	EntityManager::getServerSingletonPtr()->registerEntity(portal);

	//network register asteroid
	portal->networkRegister(NetworkIDManager::getServerSingletonPtr(), Portal::getClassName(), true);
}

void ServerLoader::onBoost(SpeedBoost * boost) {
	if (!mExternalitem) {
		THROW(ParseException, "This should be an external item.");
	}

	mHovercraftWorld->createBoost(boost, mExternalitem);

	//add to entity manager
	EntityManager::getServerSingletonPtr()->registerEntity(boost);

	//network register asteroid
	boost->networkRegister(NetworkIDManager::getServerSingletonPtr(), SpeedBoost::getClassName(), true);
}

void ServerLoader::onPowerupSpawn(PowerupSpawn * powerupspawn) {
	if (!mExternalitem) {
		THROW(ParseException, "This should be an external item.");
	}

	//add to entity manager
	EntityManager::getServerSingletonPtr()->registerEntity(powerupspawn);

	//network register asteroid
	powerupspawn->networkRegister(NetworkIDManager::getServerSingletonPtr(), PowerupSpawn::getClassName(), true);
}

void ServerLoader::onResetSpawn(ResetSpawn * spawn) {
	if (!mExternalitem) {
		THROW(ParseException, "This should be an external item.");
	}

	//add to entity manager
	EntityManager::getServerSingletonPtr()->registerEntity(spawn);

	//network register asteroid
	spawn->networkRegister(NetworkIDManager::getServerSingletonPtr(), ResetSpawn::getClassName(), true);
}

}
