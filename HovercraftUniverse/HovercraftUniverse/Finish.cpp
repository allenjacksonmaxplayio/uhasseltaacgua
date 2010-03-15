#include "Finish.h"

namespace HovUni {

const Ogre::String Finish::CATEGORY("Finish");

Finish::Finish(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, const Ogre::Vector3& upVector, const Ogre::String& ogreentity, float processInterval):
	Entity(name,CATEGORY,false,position,orientation,upVector,ogreentity,processInterval,0){
}

void Finish::load(TiXmlElement * data) throw(ParseException){
	//We are loading a Finish!
	if(strcmp(data->Value(),"Finish") != 0){
		THROW(ParseException, "Given XML element is not of type finish.");
	}	
}

Finish::~Finish(void){
}

std::string Finish::getClassName(){
	return "Finish";
}

}
