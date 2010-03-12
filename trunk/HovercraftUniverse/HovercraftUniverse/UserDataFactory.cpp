#include "UserDataFactory.h"
#include "UserData.h"

namespace HovUni {

//singleton

UserDataFactory* UserDataFactory::ms_Singleton = new UserDataFactory();

UserDataFactory* UserDataFactory::getSingletonPtr(void)
{
    return ms_Singleton;
}

UserDataFactory& UserDataFactory::getSingleton(void)
{
    assert( ms_Singleton );  return ( *ms_Singleton );
}

//code

UserDataFactory::UserDataFactory(void)
{
}

UserDataFactory::~UserDataFactory(void)
{
}

void UserDataFactory::addUserDataCallback( UserDataCallback* callback ){
	mUserDataCallback.push_back(callback);
}

void UserDataFactory::removeUserDataCallback( UserDataCallback* callback ){
	mUserDataCallback.remove(callback);
}

void UserDataFactory::parseUserData(const Ogre::String& data, EntityDescription& description) {
	//parse XML that describes the user data
	mDocument.Parse(data.c_str());
	TiXmlElement * root = mDocument.RootElement();

	//if correct xml, see if user data is known
	if ( root ){

		//START
		if ( strcmp(root->Value(),"Start") == 0 ){
			Ogre::SharedPtr<Start> start(new Start(description.mName,description.mCategory,description.mPosition,description.mOrientation,-1));
			start->load(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onStart(start);
			}
		}
		//STARTPOSITION
		if ( strcmp(root->Value(),"StartPosition") == 0 ){
			Ogre::SharedPtr<StartPosition> startp(new StartPosition(description.mName,description.mCategory,description.mPosition,description.mOrientation,-1));
			startp->load(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onStartPosition(startp);
			}
		}
		//FINISH
		else if ( strcmp(root->Value(),"Finish") == 0 ){
			Ogre::SharedPtr<Finish> finish(new Finish(description.mName,description.mCategory,description.mPosition,description.mOrientation,-1));
			finish->load(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onFinish(finish);
			}
		}
		//CHECKPOINT
		else if ( strcmp(root->Value(),"CheckPoint") == 0 ){
			Ogre::SharedPtr<CheckPoint> checkpoint(new CheckPoint(description.mName,description.mCategory,description.mPosition,description.mOrientation,-1));
			checkpoint->load(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onCheckPoint(checkpoint);
			}
		}
		//ASTEROID
		else if ( strcmp(root->Value(),"Asteroid") == 0 ){
			Ogre::SharedPtr<Asteroid> ast(new Asteroid(description.mName,description.mCategory,description.mPosition,description.mOrientation,-1));
			ast->load(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onAsteroid(ast);
			}
		}
		//HOVERCRAFT
		else if ( strcmp(root->Value(),"Hovercraft") == 0 ){
			Ogre::SharedPtr<Hovercraft> hovercr(new Hovercraft(description.mName,description.mCategory,description.mPosition,description.mOrientation,-1));
			hovercr->load(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onHoverCraft(hovercr);
			}
		}
		//BOOST
		else if ( strcmp(root->Value(),"Boost") == 0 ){
			Ogre::SharedPtr<Boost> boost(new Boost(description.mName,description.mCategory,description.mPosition,description.mOrientation,-1));
			boost->load(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onBoost(boost);
			}
		}
		//PORTAL
		else if ( strcmp(root->Value(),"Portal") == 0 ){
			Ogre::SharedPtr<Portal> portal(new Portal(description.mName,description.mCategory,description.mPosition,description.mOrientation,-1));
			portal->load(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onPortal(portal);
			}
		}
		//POWERUPSPAWN
		else if ( strcmp(root->Value(),"PowerupSpawn") == 0 ){
			Ogre::SharedPtr<PowerupSpawn> spawn(new PowerupSpawn(description.mName,description.mCategory,description.mPosition,description.mOrientation,-1));
			spawn->load(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onPowerupSpawn(spawn);
			}
		}
		//RESETSPAWN
		else if ( strcmp(root->Value(),"ResetSpawn") == 0 ){
			Ogre::SharedPtr<ResetSpawn> spawn(new ResetSpawn(description.mName,description.mCategory,description.mPosition,description.mOrientation,-1));
			spawn->load(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onResetSpawn(spawn);
			}
		}
		//TRACK
		else if ( strcmp(root->Value(),"Track") == 0 ){
			Ogre::SharedPtr<Track> track(new Track(description.mName,description.mCategory,description.mPosition,description.mOrientation,-1));
			track->load(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onTrack(track);
			}
		}

		//clear xml
		mDocument.Clear();
	}
}

}

