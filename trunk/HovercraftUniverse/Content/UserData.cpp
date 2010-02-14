#include "UserData.h"
#include <OgreSharedPtr.h>

namespace HovUni {

UserData::UserData()
{	
}

UserData::~UserData(void)
{
	mMovableObject->getUserObjectBindings().eraseUserAny("userdata");
}

void UserData::setMovableObject( Ogre::MovableObject * movobj ) {
	mMovableObject = movobj;
	mMovableObject->getUserObjectBindings().setUserAny("userdata",Ogre::Any(this));		
}

}
