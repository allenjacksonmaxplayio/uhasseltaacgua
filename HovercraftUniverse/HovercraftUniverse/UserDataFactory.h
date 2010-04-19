#ifndef USERDATAFACTORY_H
#define USERDATAFACTORY_H

#include <OgreMaxScene.hpp>
#include <list>

#include "UserDataCallback.h"
#include "EntityDescription.h"

namespace HovUni {

/**
 * Factory class for user data types.
 * Will parse a string and extract user data types.
 * A user can register UserDataCallback instances to receive notifications about user data creation.
 * This class is singleton, use getSingleton() to get the reference.
 * @author PJ
 */
class UserDataFactory{
private:

	std::list<UserDataCallback *> mUserDataCallback;

	TiXmlDocument mDocument;

public:

	/**
	 * Constructor
	 */
	UserDataFactory(void);

	/**
	 * Destructor
	 */
	~UserDataFactory(void);	

	/**
	 * Add a listener for load events
	 * @param callback
	 */
	void addUserDataCallback(UserDataCallback* callback);

	/**
	 * Remove a listener for load events
	 * @param callback
	 */
	void removeUserDataCallback(UserDataCallback* callback);

	/**
	 * Will parse the scene and load all userdata
	 * @param data
	 * @param entity description
	 */
	void parseUserData(const Ogre::String& data, const EntityDescription& description);
};

}

#endif
