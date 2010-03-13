#include "UserDataFactory.h"

namespace HovUni {

//singleton

UserDataFactory* UserDataFactory::ms_Singleton = new UserDataFactory();

UserDataFactory* UserDataFactory::getSingletonPtr(void){
    return ms_Singleton;
}

UserDataFactory& UserDataFactory::getSingleton(void){
    assert(ms_Singleton);  
	return(*ms_Singleton);
}

//code

UserDataFactory::UserDataFactory(void){
}

UserDataFactory::~UserDataFactory(void){
}

void UserDataFactory::addUserDataCallback(UserDataCallback* callback){
	mUserDataCallback.push_back(callback);
}

void UserDataFactory::removeUserDataCallback(UserDataCallback* callback){
	mUserDataCallback.remove(callback);
}

void UserDataFactory::parseUserData(const Ogre::String& data, const EntityDescription& description){
	//parse XML that describes the user data
	mDocument.Parse(data.c_str());
	TiXmlElement * root = mDocument.RootElement();

	//Read some generic things of entities here
	Ogre::String ogreentity = "";
	Ogre::Real processtime = -1.0f;

	TiXmlNode * parent = root->FirstChild();
	if ( parent ){
		TiXmlNode * current = parent->FirstChild();
		while ( current ){
			TiXmlElement * element = dynamic_cast<TiXmlElement *>(current);			
			if ( element ) {
				if ( strcmp(element->Value(),"ProcessInterval") ){
					processtime = Ogre::StringConverter::parseReal(Ogre::String(element->GetText()));
				}
				else if ( strcmp(element->Value(),"OgreEntity") ){
					ogreentity = Ogre::String(element->GetText());
				}
			}
			current->NextSibling();
		}
	}

	//if correct xml, see if user data is known
	if(root){

		//START
		if(strcmp(root->Value(),"Start") == 0){
			//create
			Ogre::SharedPtr<Start> start(new Start(description.getName(),description.getPosition(), description.getOrientation(), ogreentity, processtime));
			//load
			start->load(root);
			//forward
			for(std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++){
				(*uc)->onStart(start);
			}
		}
		//STARTPOSITION
		if(strcmp(root->Value(),"StartPosition") == 0){
			//create
			Ogre::SharedPtr<StartPosition> startp(new StartPosition(description.getName(),description.getPosition(), description.getOrientation(), processtime));
			//load
			startp->load(root);
			//forward
			for(std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++){
				(*uc)->onStartPosition(startp);
			}
		}
		//FINISH
		else if(strcmp(root->Value(),"Finish") == 0){
			//create
			Ogre::SharedPtr<Finish> finish(new Finish(description.getName(),description.getPosition(), description.getOrientation(), ogreentity, processtime));
			//load
			finish->load(root);
			//forward
			for(std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++){
				(*uc)->onFinish(finish);
			}
		}
		//CHECKPOINT
		else if(strcmp(root->Value(),"CheckPoint") == 0){
			//create
			Ogre::SharedPtr<CheckPoint> checkpoint(new CheckPoint(description.getName(),description.getPosition(), description.getOrientation(), ogreentity, processtime));
			//load
			checkpoint->load(root);
			//forward
			for(std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++){
				(*uc)->onCheckPoint(checkpoint);
			}
		}
		//ASTEROID
		else if(strcmp(root->Value(),"Asteroid") == 0){
			//create
			Ogre::SharedPtr<Asteroid> asteroid(new Asteroid(description.getName(),description.getPosition(), description.getOrientation(), ogreentity, processtime));
			//load
			asteroid->load(root);
			//forward
			for(std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++){
				(*uc)->onAsteroid(asteroid);
			}
		}
		//HOVERCRAFT
		else if(strcmp(root->Value(),"Hovercraft") == 0){
			//create
			Ogre::SharedPtr<Hovercraft> hovercraft(new Hovercraft(description.getName(),description.getPosition(), description.getOrientation(), ogreentity, processtime));
			//load
			hovercraft->load(root);
			//forward
			for(std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++){
				(*uc)->onHoverCraft(hovercraft);
			}
		}
		//BOOST
		else if(strcmp(root->Value(),"Boost") == 0){
			//create
			Ogre::SharedPtr<SpeedBoost> boost(new SpeedBoost(description.getName(),description.getPosition(), description.getOrientation(), ogreentity, processtime));
			//load
			boost->load(root);
			//forward
			for(std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++){
				(*uc)->onBoost(boost);
			}
		}
		//PORTAL
		else if(strcmp(root->Value(),"Portal") == 0){
			//create
			Ogre::SharedPtr<Portal> portal(new Portal(description.getName(),description.getPosition(), description.getOrientation(), ogreentity, processtime));
			//load
			portal->load(root);
			//forward
			for(std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++){
				(*uc)->onPortal(portal);
			}
		}
		//POWERUPSPAWN
		else if(strcmp(root->Value(),"PowerupSpawn") == 0){
			//create
			Ogre::SharedPtr<PowerupSpawn> spawn(new PowerupSpawn(description.getName(),description.getPosition(), description.getOrientation(), ogreentity, processtime));
			//load
			spawn->load(root);
			//forward
			for(std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++){
				(*uc)->onPowerupSpawn(spawn);
			}
		}
		//RESETSPAWN
		else if(strcmp(root->Value(),"ResetSpawn") == 0){
			//create
			Ogre::SharedPtr<ResetSpawn> spawn(new ResetSpawn(description.getName(),description.getPosition(), description.getOrientation(), processtime));
			//load
			spawn->load(root);
			//forward
			for(std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++){
				(*uc)->onResetSpawn(spawn);
			}
		}
		//TRACK
		else if(strcmp(root->Value(),"Track") == 0){
			//create
			Ogre::SharedPtr<Track> track(new Track(description.getName(),description.getPosition(), description.getOrientation(), processtime));
			//load
			track->load(root);
			//forward
			for(std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++){
				(*uc)->onTrack(track);
			}
		}

		//clear xml
		mDocument.Clear();
	}
}

}

