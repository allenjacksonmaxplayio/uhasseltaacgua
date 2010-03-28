#include "SpeedBoost.h"
#include <OgreStringConverter.h>
#include "Hovercraft.h"

namespace HovUni {

const Ogre::String SpeedBoost::CATEGORY("Boost");

SpeedBoost::SpeedBoost(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, const Ogre::String& ogreentity, float processInterval):
	Entity(name,CATEGORY,position,orientation,ogreentity,processInterval,1){
}

SpeedBoost::SpeedBoost( ZCom_BitStream* announcedata ):
	Entity(announcedata,CATEGORY,1)
{
}

void SpeedBoost::load(TiXmlElement * data) throw(ParseException){
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

SpeedBoost::~SpeedBoost(void){
}

void SpeedBoost::onEnter ( Hovercraft * hovercraft ){
	hovercraft->setSpeed(Hovercraft::MAXSPEED);
}


void SpeedBoost::onLeave( Hovercraft * hovercraft ){
}

void SpeedBoost::setupReplication(){
	//setup parent
	Entity::setupReplication();

	//mBoost
	mNode->addReplicationFloat(&mBoost,
		4,
		ZCOM_REPFLAG_MOSTRECENT,
		ZCOM_REPRULE_AUTH_2_ALL
	);
}

std::string SpeedBoost::getClassName(){
	return "SpeedBoost";
}

}