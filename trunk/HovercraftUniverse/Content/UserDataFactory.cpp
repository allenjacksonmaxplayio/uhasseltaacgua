#include "UserDataFactory.h"

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

}

