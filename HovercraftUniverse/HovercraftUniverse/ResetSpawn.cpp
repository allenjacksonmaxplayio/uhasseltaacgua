#include "ResetSpawn.h"
#include <OgreStringConverter.h>

namespace HovUni {

const Ogre::String ResetSpawn::CATEGORY("ResetSpawn");

ResetSpawn::ResetSpawn(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, const Ogre::Vector3& upVector, float processInterval):
	Entity(name,CATEGORY,false,position,orientation,upVector,"",processInterval,0){
}

void ResetSpawn::load(TiXmlElement * data) throw(ParseException){
	//We are loading a Finish!
	if(strcmp(data->Value(),"ResetSpawn") != 0){
		THROW(ParseException, "Given XML element is not of type reset spawn.");
	}	
}

ResetSpawn::~ResetSpawn(void){
}

std::string ResetSpawn::getClassName(){
	return "ResetSpawn";
}

}
