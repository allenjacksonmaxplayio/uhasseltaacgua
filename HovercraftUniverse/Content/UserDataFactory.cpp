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

void UserDataFactory::parseUserData(const Ogre::String& data ) {
	//parse XML that describes the user data
	mDocument.Parse(data.c_str());
	TiXmlElement * root = mDocument.RootElement();

	//if correct xml, see if user data is known
	if ( root ){

		//START
		if ( strcmp(root->Value(),"Start") == 0 ){
			Start * start = new Start(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onStart(start);
			}
		}
		//STARTPOSITION
		if ( strcmp(root->Value(),"StartPosition") == 0 ){
			StartPosition * startp = new StartPosition(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onStartPosition(startp);
			}
		}
		//FINISH
		else if ( strcmp(root->Value(),"Finish") == 0 ){
			Finish * finish = new Finish(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onFinish(finish);
			}
		}
		//CHECKPOINT
		else if ( strcmp(root->Value(),"CheckPoint") == 0 ){
			CheckPoint * checkpoint = new CheckPoint(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onCheckPoint(checkpoint);
			}
		}
		//ASTEROID
		else if ( strcmp(root->Value(),"Asteroid") == 0 ){
			Asteroid * ast = new Asteroid(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onAsteroid(ast);
			}
		}
		//HOVERCRAFT
		else if ( strcmp(root->Value(),"Hovercraft") == 0 ){
			Hovercraft * hovercr = new Hovercraft(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onHoverCraft(hovercr);
			}
		}
		//BOOST
		else if ( strcmp(root->Value(),"Boost") == 0 ){
			Boost * boost = new Boost(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onBoost(boost);
			}
		}
		//PORTAL
		else if ( strcmp(root->Value(),"Portal") == 0 ){
			Portal * portal = new Portal(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onPortal(portal);
			}
		}
		//POWERUPSPAWN
		else if ( strcmp(root->Value(),"PowerupSpawn") == 0 ){
			PowerupSpawn * spawn = new PowerupSpawn(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onPowerupSpawn(spawn);
			}
		}
		//RESETSPAWN
		else if ( strcmp(root->Value(),"ResetSpawn") == 0 ){
			ResetSpawn * spawn = new ResetSpawn(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onResetSpawn(spawn);
			}
		}
		//TRACK
		else if ( strcmp(root->Value(),"Track") == 0 ){
			Track * track = new Track(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onTrack(track);
			}
		}

		//clear xml
		mDocument.Clear();
	}
}

}

