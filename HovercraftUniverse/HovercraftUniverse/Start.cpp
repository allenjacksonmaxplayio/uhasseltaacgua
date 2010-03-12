#include "Start.h"

namespace HovUni {

const Ogre::String Start::CATEGORY("Start");

Start::Start(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float processInterval):
	Entity(name,CATEGORY,false,position,orientation,processInterval){
}

void Start::load(TiXmlElement * data){
	//We are loading a Start!
	if(strcmp(data->Value(),"Start") != 0){
		throw ParseException();
	}
}

Start::~Start(void){
}

}
