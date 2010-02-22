#ifndef USERDATAFACTORY_H
#define USERDATAFACTORY_H

#include <OgreMaxScene.hpp>
#include <list>
#include "UserDataCallback.h"

namespace HovUni {

class UserDataCallback;

/**
 * Factory class for user data types.
 * Will parse a scene and extract user data types.
 * A user can register UserDataCallback instances to receive notifications about user data creation.
 * This class is singleton, use getSingleton() to get the reference.
 * @author PJ
 */
class UserDataFactory
{
private:

	static UserDataFactory * ms_Singleton;

	std::list<UserDataCallback *> mUserDataCallback;

	TiXmlDocument mDocument;

protected:

	/**
	 * Constructor
	 */
	UserDataFactory(void);

public:

	/**
	 * Destructor
	 */
	~UserDataFactory(void);	

	/**
	 * Get a reference to the factory
	 * @return reference to the factory
	 */
    static UserDataFactory& getSingleton(void);

	/**
	 * Get a pointer to the factory
	 * @return pointer to the factory
	 */
    static UserDataFactory* getSingletonPtr(void);

	/**
	 * Add a listener for load events
	 * @param callback
	 */
	void addUserDataCallback( UserDataCallback* callback );

	/**
	 * Remove a listener for load events
	 * @param callback
	 */
	void removeUserDataCallback( UserDataCallback* callback );

	/**
	 * Will parse the scene and load all userdata
	 * @param data
	 * @param attachable, an object that has userbindings (eg Ogre Movable and SceneNode)
	 */
	template<typename T>
	void parseUserData(const Ogre::String& data, T& attachable );
};

template<typename T>
void UserDataFactory::parseUserData(const Ogre::String& data, T& attachable ) {
	//parse XML that describes the user data
	mDocument.Parse(data.c_str());
	TiXmlElement * root = mDocument.RootElement();

	//if correct xml, see if user data is known
	if ( root ){

		Userdata * data = 0;

		//START
		if ( strcmp(root->Value(),"Start") == 0 ){
			Start * start = new Start(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onStart(start);
			}
			data = start;
		}
		//STARTPOSITION
		if ( strcmp(root->Value(),"StartPosition") == 0 ){
			StartPosition * startp = new StartPosition(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onStartPosition(startp);
			}
			startp = start;
		}
		//FINISH
		else if ( strcmp(root->Value(),"Finish") == 0 ){
			Finish * finish = new Finish(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onFinish(finish);
			}
			data = finish;
		}
		//CHECKPOINT
		else if ( strcmp(root->Value(),"CheckPoint") == 0 ){
			CheckPoint * checkpoint = new CheckPoint(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onCheckPoint(checkpoint);
			}
			data = checkpoint;
		}
		//ASTEROID
		else if ( strcmp(root->Value(),"Asteroid") == 0 ){
			Asteroid * ast = new Asteroid(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onAsteroid(ast);
			}
			data = ast;
		}
		//HOVERCRAFT
		else if ( strcmp(root->Value(),"Hovercraft") == 0 ){
			Hovercraft * hovercr = new Hovercraft(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onHoverCraft(hovercr);
			}
			data = hovercr;
		}
		//BOOST
		else if ( strcmp(root->Value(),"Boost") == 0 ){
			Boost * boost = new Boost(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onBoost(boost);
			}
			data = boost;
		}
		//PORTAL
		else if ( strcmp(root->Value(),"Portal") == 0 ){
			Portal * portal = new Portal(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onPortal(portal);
			}
			data = portal;
		}
		//POWERUPSPAWN
		else if ( strcmp(root->Value(),"PowerupSpawn") == 0 ){
			PowerupSpawn * spawn = new PowerupSpawn(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onPowerupSpawn(spawn);
			}
			data = spawn;
		}
		//RESETSPAWN
		else if ( strcmp(root->Value(),"ResetSpawn") == 0 ){
			ResetSpawn * spawn = new ResetSpawn(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onResetSpawn(spawn);
			}
			data = spawn;
		}
		//TRACK
		else if ( strcmp(root->Value(),"Track") == 0 ){
			Track * track = new Track(root);
			for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
				(*uc)->onTrack(track);
			}
			data = track;
		}
		
		Ogre::UserObjectBindings& ub = attachable.getUserObjectBindings();
		ub.setUserAny("userdata",Ogre::Any(data));		

		//clear xml
		mDocument.Clear();
	}
}

}

#endif
