#include "Finish.h"
#include "Hovercraft.h"

namespace HovUni {

const Ogre::String Finish::CATEGORY("Finish");

Finish::Finish(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, const Ogre::String& ogreentity, float processInterval):
	Entity(name,CATEGORY,position,orientation,ogreentity,processInterval,0){
}

Finish::Finish( ZCom_BitStream* announcedata ):
	Entity(announcedata,CATEGORY,0)
{
}

Finish::~Finish(void){
}

std::string Finish::getClassName(){
	return "Finish";
}

void Finish::load(TiXmlElement * data) throw(ParseException){
	//We are loading a Finish!
	if(strcmp(data->Value(),"Finish") != 0){
		THROW(ParseException, "Given XML element is not of type finish.");
	}	
}

void Finish::onEnter ( Hovercraft * hovercraft ){
	//TODO
}

void Finish::onLeave( Hovercraft * hovercraft ){
	//TODO
}



}
