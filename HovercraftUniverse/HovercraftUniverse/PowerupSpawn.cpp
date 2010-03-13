#include "PowerupSpawn.h"

namespace HovUni {

const Ogre::String PowerupSpawn::CATEGORY("PowerupSpawn");

PowerupSpawn::PowerupSpawn(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, const Ogre::String& ogreentity, float processInterval):
	Entity(name,CATEGORY,false,position,orientation,ogreentity,processInterval){
}

void PowerupSpawn::load(TiXmlElement * data) throw(ParseException){
	//We are loading a CheckPoint!
	if(strcmp(data->Value(),"PowerupSpawn") != 0){
		THROW(ParseException, "Given XML element is not of type powerup spawn.");
	}
}

PowerupSpawn::~PowerupSpawn(void){
}

}
