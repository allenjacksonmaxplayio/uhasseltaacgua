#include "Hovercraft.h"
#include <OgreStringConverter.h>
#include "String_Replicator.h"

namespace HovUni {

const Ogre::String Hovercraft::CATEGORY("Hovercraft");

Hovercraft::Hovercraft(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, const Ogre::String& ogreentity, float processInterval):
	Entity(name,CATEGORY,false,position,orientation,ogreentity,processInterval,5){
}

void Hovercraft::load(TiXmlElement * data) throw(ParseException){
	TiXmlNode * node;
	
	//We are loading a Hovercraft!
	if(strcmp(data->Value(),"Hovercraft") != 0){
		THROW(ParseException, "Given XML element is not of type hovercraft.");
	}

	//Read name
	mDisplayName = "No name";
	node = data->FirstChild("Name");
	if(node){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if(element){
			mDisplayName = Ogre::String(element->GetText());
		}
	}

	//Read Description
	mDescription = "";
	node = data->FirstChild("Description");
	if(node){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if(element){
			mDescription = Ogre::String(element->GetText());
		}
	}

	//Read Speed
	mSpeed = 0.0f;
	node = data->FirstChild("Speed");
	if(node){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if(element){
			mSpeed = Ogre::StringConverter::parseReal(Ogre::String(element->GetText()));
		}
	}

	//Read mass
	mMass = 0.0f;
	node = data->FirstChild("Mass");
	if(node){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if(element){
			mMass = Ogre::StringConverter::parseReal(Ogre::String(element->GetText()));
		}
	}

	//Read Acceleration
	mAcceleration = 0.0f;
	node = data->FirstChild("Acceleration");
	if(node){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if(element){
			mAcceleration = Ogre::StringConverter::parseReal(Ogre::String(element->GetText()));
		}
	}
}

Hovercraft::~Hovercraft(void){
}

void Hovercraft::setupReplication(){
	//mDisplayName
	mNode->addReplicator(
		new String_Replicator(&mDisplayName,
		ZCOM_REPFLAG_MOSTRECENT,
		ZCOM_REPRULE_AUTH_2_ALL
	), 
	true);

	//mDescription
	mNode->addReplicator(
		new String_Replicator(&mDescription,
		ZCOM_REPFLAG_MOSTRECENT,
		ZCOM_REPRULE_AUTH_2_ALL
	), 
	true);

	//mAcceleration
	mNode->addReplicationFloat(&mAcceleration,
	4,
	ZCOM_REPFLAG_MOSTRECENT,
	ZCOM_REPRULE_AUTH_2_ALL
	);

	//mMass
	mNode->addReplicationFloat(&mMass,
	4,
	ZCOM_REPFLAG_MOSTRECENT,
	ZCOM_REPRULE_AUTH_2_ALL
	);

	//mSpeed
	mNode->addReplicationFloat(&mSpeed,
	4,
	ZCOM_REPFLAG_MOSTRECENT,
	ZCOM_REPRULE_AUTH_2_ALL
	);
}

}
