#include "ResetSpawn.h"
#include <OgreStringConverter.h>

namespace HovUni {

ResetSpawn::ResetSpawn(const Ogre::String& name, const Ogre::String& category, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float processInterval):
	Entity(name,category,false,position,orientation,processInterval)
{
}

void ResetSpawn::load( TiXmlElement * data ) throw (ParseException)
{
	TiXmlNode * node;

	//We are loading a Finish!
	if(strcmp(data->Value(),"ResetSpawn") != 0){
		throw ParseException();
	}	
}

ResetSpawn::~ResetSpawn(void)
{
}

}
