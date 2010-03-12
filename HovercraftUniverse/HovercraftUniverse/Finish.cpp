#include "Finish.h"

namespace HovUni {

Finish::Finish(const Ogre::String& name, const Ogre::String& category, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float processInterval):
	Entity(name,category,false,position,orientation,processInterval)
{
}

void Finish::load( TiXmlElement * data ) throw (ParseException)
{
	//We are loading a Finish!
	if(strcmp(data->Value(),"Finish") != 0){
		throw ParseException();
	}	
}

Finish::~Finish(void)
{
}

}
