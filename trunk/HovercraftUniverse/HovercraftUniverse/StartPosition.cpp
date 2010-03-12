#include "StartPosition.h"
#include <OgreStringConverter.h>

namespace HovUni {

const Ogre::String StartPosition::CATEGORY("StartPosition");

StartPosition::StartPosition(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float processInterval):
	Entity(name,CATEGORY,false,position,orientation,processInterval){
}

void StartPosition::load(TiXmlElement * data) throw(ParseException){
	TiXmlNode * node;

	//We are loading a Finish!
	if(strcmp(data->Value(),"StartPosition") != 0){
		THROW(ParseException, "Given XML element is not of type start position.");
	}	

	//Read number
	mPlayerNumber = 0;
	node = data->FirstChild("PlayerNumber");
	if(node){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if(element){
			mPlayerNumber = Ogre::StringConverter::parseInt(Ogre::String(element->GetText()));
		}
	}
}

StartPosition::~StartPosition(void){
}

}
