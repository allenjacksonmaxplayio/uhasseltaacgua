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

void UserDataFactory::parseUserData(const Ogre::String& data) {
	//parse XML that describes the user data
	mDocument.Parse(data.c_str());
	TiXmlElement * root = mDocument.RootElement();

	//if correct xml, see if user data is known
	if ( root ){

		//START
		if ( strcmp(root->Value(),"Start") == 0 ){
			Ogre::SharedPtr<StartData> start(new StartData(root));
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onStart(start);
			}
		}
		//STARTPOSITION
		if ( strcmp(root->Value(),"StartPosition") == 0 ){
			Ogre::SharedPtr<StartPositionData> startp(new StartPositionData(root));
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onStartPosition(startp);
			}
		}
		//FINISH
		else if ( strcmp(root->Value(),"Finish") == 0 ){
			Ogre::SharedPtr<FinishData> finish(new FinishData(root));
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onFinish(finish);
			}
		}
		//CHECKPOINT
		else if ( strcmp(root->Value(),"CheckPoint") == 0 ){
			Ogre::SharedPtr<CheckPointData> checkpoint(new CheckPointData(root));
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onCheckPoint(checkpoint);
			}
		}
		//ASTEROID
		else if ( strcmp(root->Value(),"Asteroid") == 0 ){
			Ogre::SharedPtr<AsteroidData> ast(new AsteroidData(root));
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onAsteroid(ast);
			}
		}
		//HOVERCRAFT
		else if ( strcmp(root->Value(),"Hovercraft") == 0 ){
			Ogre::SharedPtr<HovercraftData> hovercr(new HovercraftData(root));
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onHoverCraft(hovercr);
			}
		}
		//BOOST
		else if ( strcmp(root->Value(),"Boost") == 0 ){
			Ogre::SharedPtr<BoostData> boost(new BoostData(root));
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onBoost(boost);
			}
		}
		//PORTAL
		else if ( strcmp(root->Value(),"Portal") == 0 ){
			Ogre::SharedPtr<PortalData> portal(new PortalData(root));
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onPortal(portal);
			}
		}
		//POWERUPSPAWN
		else if ( strcmp(root->Value(),"PowerupSpawn") == 0 ){
			Ogre::SharedPtr<PowerupSpawnData> spawn(new PowerupSpawnData(root));
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onPowerupSpawn(spawn);
			}
		}
		//RESETSPAWN
		else if ( strcmp(root->Value(),"ResetSpawn") == 0 ){
			Ogre::SharedPtr<ResetSpawnData> spawn(new ResetSpawnData(root));
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onResetSpawn(spawn);
			}
		}
		//TRACK
		else if ( strcmp(root->Value(),"Track") == 0 ){
			Ogre::SharedPtr<TrackData> track(new TrackData(root));
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onTrack(track);
			}
		}

		//clear xml
		mDocument.Clear();
	}
}

}

