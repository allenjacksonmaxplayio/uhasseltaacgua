#ifndef ENITITYDESCRIPTION_H
#define ENITITYDESCRIPTION_H

#include <OgreString.h>
#include <OgreVector3.h>
#include <OgrePlatform.h>

namespace HovUni {

struct EntityDescription
{
	Ogre::String mName;
	Ogre::String mCategory;
	Ogre::Vector3 mPosition;
	Ogre::Quaternion mOrientation;

	EntityDescription(const Ogre::String& name, const Ogre::String& category, const Ogre::Vector3& position, const Ogre::Quaternion& orientation);
};

}

#endif