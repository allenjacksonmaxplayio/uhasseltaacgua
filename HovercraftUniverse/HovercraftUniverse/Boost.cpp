#include "Boost.h"
#include <OgreStringConverter.h>

namespace HovUni {

const Ogre::String Boost::CATEGORY("Boost");

Boost::Boost(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float processInterval):
	Entity(name,CATEGORY,false,position,orientation,processInterval,1){
}

void Boost::load(TiXmlElement * data) throw(ParseException){
	TiXmlNode * node;

	//We are loading a Boost!
	if(strcmp(data->Value(),"Boost") != 0){
		THROW(ParseException, "Given XML element is not of type boost.");
	}

	//Read BoostData
	mBoost = 0.0f;
	node = data->FirstChild("Boost");
	if(node){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if(element){
			mBoost = Ogre::StringConverter::parseReal(Ogre::String(element->GetText()));
		}
	}
}

Boost::~Boost(void){
}

void Boost::setupReplication(){
	//mBoost
	mNode->addReplicationFloat(&mBoost,
		4,
		ZCOM_REPFLAG_MOSTRECENT,
		ZCOM_REPRULE_AUTH_2_ALL
	);
}

}
