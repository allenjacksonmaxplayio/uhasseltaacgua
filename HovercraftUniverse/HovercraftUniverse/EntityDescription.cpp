#include "EntityDescription.h"

namespace HovUni {

	EntityDescription::EntityDescription(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, const Ogre::String& ogreentity, Ogre::Real processInterval ):
mName(name), mPosition(position), mOrientation(orientation), mOgreEntity(ogreentity), mProcessInterval(processInterval) {
}

}
