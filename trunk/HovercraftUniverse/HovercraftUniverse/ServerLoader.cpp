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
}

ServerLoader::~ServerLoader(void) {
}

void ServerLoader::parseUserData(const Ogre::String& data, const EntityDescription& description){
	//parse XML that describes the user data
	TiXmlDocument mDocument;
	mDocument.Parse(data.c_str());
	TiXmlElement * root = mDocument.RootElement();

	//if correct xml, see if user data is known
	if(root){

		//Read some generic things of entities here
		Ogre::String ogreentity = "";
		Ogre::Real processtime = -1.0f;

		TiXmlNode * current = root->FirstChild();
		while ( current ){
			TiXmlElement * element = dynamic_cast<TiXmlElement *>(current);			
			if ( element ) {
				if ( strcmp(element->Value(),"ProcessInterval") == 0 ){
					processtime = Ogre::StringConverter::parseReal(Ogre::String(element->GetText()));
				}
				else if ( strcmp(element->Value(),"OgreEntity") == 0 ){
					ogreentity = Ogre::String(element->GetText());
				}
			}
			current = current->NextSibling();
		}


		//START
		if(strcmp(root->Value(),"Start") == 0){
			//create
			Start * start(new Start(description.getName(),description.getPosition(), description.getOrientation(), ogreentity, processtime));
			//load
			start->load(root);
			//forward
			onStart(start);
		}
		//STARTPOSITION
		if(strcmp(root->Value(),"StartPosition") == 0){
			//create
			StartPosition * startp(new StartPosition(description.getName(),description.getPosition(), description.getOrientation(), processtime));
			//load
			startp->load(root);
			//forward
			onStartPosition(startp);
		}
		//FINISH
		else if(strcmp(root->Value(),"Finish") == 0){
			//create
			Finish * finish(new Finish(description.getName(),description.getPosition(), description.getOrientation(), ogreentity, processtime));
			//load
			finish->load(root);
			//forward
			onFinish(finish);
		}
		//CHECKPOINT
		else if(strcmp(root->Value(),"CheckPoint") == 0){
			//create
			CheckPoint * checkpoint(new CheckPoint(description.getName(),description.getPosition(), description.getOrientation(), ogreentity, processtime));
			//load
			checkpoint->load(root);
			//forward
			onCheckPoint(checkpoint);
		}
		//ASTEROID
		else if(strcmp(root->Value(),"Asteroid") == 0){
			//create
			Asteroid * asteroid(new Asteroid(description.getName(),description.getPosition(), description.getOrientation(), ogreentity, processtime));
			//load
			asteroid->load(root);
			//forward
			onAsteroid(asteroid);
		}
		//HOVERCRAFT
		else if(strcmp(root->Value(),"Hovercraft") == 0){
			//create
			Hovercraft * hovercraft(new Hovercraft(description.getName(),0,description.getPosition(), description.getOrientation(), ogreentity, processtime));
			//load
			hovercraft->load(root);
			//forward
			onHoverCraft(hovercraft);
		}
		//BOOST
		else if(strcmp(root->Value(),"Boost") == 0){
			//create
			SpeedBoost * boost(new SpeedBoost(description.getName(),description.getPosition(), description.getOrientation(), ogreentity, processtime));
			//load
			boost->load(root);
			//forward
			onBoost(boost);
		}
		//PORTAL
		else if(strcmp(root->Value(),"Portal") == 0){
			//create
			Portal * portal(new Portal(description.getName(),description.getPosition(), description.getOrientation(), ogreentity, processtime));
			//load
			portal->load(root);
			//forward
			onPortal(portal);
		}
		//POWERUPSPAWN
		else if(strcmp(root->Value(),"PowerupSpawn") == 0){
			//create
			PowerupSpawn * spawn(new PowerupSpawn(description.getName(),description.getPosition(), description.getOrientation(), ogreentity, processtime));
			//load
			spawn->load(root);
			//forward
			onPowerupSpawn(spawn);
		}
		//RESETSPAWN
		else if(strcmp(root->Value(),"ResetSpawn") == 0){
			//create
			ResetSpawn * spawn(new ResetSpawn(description.getName(),description.getPosition(), description.getOrientation(), processtime));
			//load
			spawn->load(root);
			//forward
			onResetSpawn(spawn);
		}
		//TRACK
		else if(strcmp(root->Value(),"Track") == 0){
			//create
			Track * track(new Track());
			//load
			track->load(root);
			//forward
			onTrack(track);
		}

		//clear xml
		mDocument.Clear();
	}
}

void ServerLoader::load(const Ogre::String& filename) {
	Havok::start(filename.c_str(), this);
}

void ServerLoader::onSceneUserData(const Ogre::String& userDataReference, const Ogre::String& userData) {
	if (!userData.empty()) {
		EntityDescription desc("Track", Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
		parseUserData(userData, desc);
	}
}

void ServerLoader::onExternal(OgreMax::Types::ExternalItem& externalitem) {
	mExternalitem = &externalitem;
	if (!externalitem.userData.empty()) {
		EntityDescription desc(externalitem.name, externalitem.position, externalitem.rotation);
		parseUserData(externalitem.userData, desc);
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
			parseUserData(entityparameters.extraData->userData, desc);
		}
	}
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
