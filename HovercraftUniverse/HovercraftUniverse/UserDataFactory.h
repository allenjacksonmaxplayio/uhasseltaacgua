#ifndef USERDATAFACTORY_H
#define USERDATAFACTORY_H

#include <OgreMaxScene.hpp>
#include <list>
#include "UserDataCallback.h"

namespace HovUni {

/**
 * Factory class for user data types.
 * Will parse a string and extract user data types.
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
	 */
	void parseUserData(const Ogre::String& data );
};

}

#endif
