#include "Track.h"
#include <OgreStringConverter.h>
#include "String_Replicator.h"

namespace HovUni {

const Ogre::String Track::CATEGORY("Track");

Track::Track(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float processInterval):
	Entity(name,CATEGORY,position,orientation,"",processInterval,3){
}

Track::Track( ZCom_BitStream* announcedata ):
	Entity(announcedata,CATEGORY,3)
{
}


void Track::load(TiXmlElement * data) throw(ParseException){
	TiXmlNode * node;

	//We are loading a CheckPoint!
	if(strcmp(data->Value(),"Track") != 0){
		THROW(ParseException, "Given XML element is not of type track.");
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

	//Read MinimumPlayers
	mMinimumPlayers = 0;
	node = data->FirstChild("MinimumPlayers");
	if(node){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if(element){
			mMinimumPlayers = Ogre::StringConverter::parseInt(Ogre::String(element->GetText()));
		}
	}

	//Read MinimumPlayers
	mMaximumPlayers = 0;
	node = data->FirstChild("MaximumPlayers");
	if(node){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if(element){
			mMaximumPlayers = Ogre::StringConverter::parseInt(Ogre::String(element->GetText()));
		}
	}

	//Read Physics File Name
	mPhysicsFileName = "";
	node = data->FirstChild("PhysicsFileName");
	if(node){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if(element){
			mPhysicsFileName = Ogre::String(element->GetText());
		}
	}
}

Track::~Track(void){
}

void Track::setupReplication(){
	//parent
	Entity::setupReplication();

	//mName
	mNode->addReplicator(
		new String_Replicator(&mDisplayName,
		ZCOM_REPFLAG_MOSTRECENT,
		ZCOM_REPRULE_AUTH_2_ALL
	), 
	true);

	//mMinimumPlayers
	mNode->addReplicationInt(&mMinimumPlayers,		// pointer to the variable
    8,												// amount of bits(up to 255 players)
    false,											// unsigned
    ZCOM_REPFLAG_MOSTRECENT,						// always send the most recent value only
    ZCOM_REPRULE_AUTH_2_ALL							// server sends to all clients
	);

	//mMaximumPlayers
	mNode->addReplicationInt(&mMaximumPlayers,		// pointer to the variable
    8,												// amount of bits(up to 255 players)
    false,											// unsigned
    ZCOM_REPFLAG_MOSTRECENT,						// always send the most recent value only
    ZCOM_REPRULE_AUTH_2_ALL							// server sends to all clients
	);
}

std::string Track::getClassName(){
	return "Track";
}

}
