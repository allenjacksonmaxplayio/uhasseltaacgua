#include "PowerupSpawn.h"

namespace HovUni {

PowerupSpawn::PowerupSpawn(const Ogre::String& name, const Ogre::String& category, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float processInterval):
	Entity(name,category,false,position,orientation,processInterval)
{
}

void PowerupSpawn::load( TiXmlElement * data) throw (ParseException)
{
	//We are loading a CheckPoint!
	if(strcmp(data->Value(),"PowerupSpawn") != 0){
		throw ParseException();
	}
}

PowerupSpawn::~PowerupSpawn(void)
{
}

}
