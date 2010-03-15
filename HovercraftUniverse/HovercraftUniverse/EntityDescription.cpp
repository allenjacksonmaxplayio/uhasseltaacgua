#include "EntityDescription.h"

namespace HovUni {

	EntityDescription::EntityDescription(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, const Ogre::Vector3& upvector):
mName(name), mPosition(position), mOrientation(orientation), mUpVector(upvector) {
}

}
