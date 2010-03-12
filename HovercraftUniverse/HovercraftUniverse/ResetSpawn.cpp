#include "ResetSpawn.h"
#include <OgreStringConverter.h>

namespace HovUni {

const Ogre::String ResetSpawn::CATEGORY("ResetSpawn");

ResetSpawn::ResetSpawn(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float processInterval):
	Entity(name,CATEGORY,false,position,orientation,processInterval)
{
}

void ResetSpawn::load(TiXmlElement * data) throw(ParseException)
{
	//We are loading a Finish!
	if(strcmp(data->Value(),"ResetSpawn") != 0){
		throw ParseException();
	}	
}

ResetSpawn::~ResetSpawn(void)
{
}

}
