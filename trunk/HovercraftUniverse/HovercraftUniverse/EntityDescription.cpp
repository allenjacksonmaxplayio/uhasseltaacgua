#include "EntityDescription.h"

namespace HovUni {

EntityDescription::EntityDescription(const Ogre::String& name, const Ogre::String& category, const Ogre::Vector3& position, const Ogre::Quaternion& orientation):
	mName(name), mCategory(category), mPosition(position), mOrientation(orientation)
 {
}

}
