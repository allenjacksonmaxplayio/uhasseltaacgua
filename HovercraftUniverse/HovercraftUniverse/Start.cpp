#include "Start.h"

namespace HovUni {

Start::Start(const Ogre::String& name, const Ogre::String& category, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float processInterval):
	Entity(name,category,false,position,orientation,processInterval)
{
}

void Start::load( TiXmlElement * data )
{
	//We are loading a Start!
	if(strcmp(data->Value(),"Start") != 0){
		throw ParseException();
	}
}

Start::~Start(void)
{
}

}
