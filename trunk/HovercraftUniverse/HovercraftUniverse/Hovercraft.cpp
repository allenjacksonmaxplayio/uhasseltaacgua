#include "Hovercraft.h"
#include <OgreStringConverter.h>

#include "Havok.h"

#include "String_Replicator.h"

namespace HovUni {

const Ogre::String Hovercraft::CATEGORY("Hovercraft");

const Ogre::Real Hovercraft::MAXSPEED(200.0);

Hovercraft::Hovercraft(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, const Ogre::String& ogreentity, float processInterval):
Entity(name,CATEGORY,position,orientation,ogreentity,processInterval,8), mTilt(0.0f), mCollisionState(false), mFinished(false) {
}

Hovercraft::Hovercraft( ZCom_BitStream* announcedata ): Entity(announcedata,CATEGORY,8) {
	// Display name
	int length = announcedata->getInt(sizeof(int) * 8);
	if (length != 0) {
		mDisplayName = Ogre::String(announcedata->getString());
	} else {
		mDisplayName = "";
	}
	Ogre::LogManager::getSingletonPtr()->getDefaultLog()->stream() << "Hovercraft :: onCLientSIde: |" << mDisplayName << "|";
	mLabel = mOgreEntity;
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
	mMaximumSpeed = 0.0f;
	node = data->FirstChild("Speed");
	if(node){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if(element){
			mMaximumSpeed = Ogre::StringConverter::parseReal(Ogre::String(element->GetText()));
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

	//Read Steering
	mSteering = 0.0f;
	node = data->FirstChild("Steering");
	if(node){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if(element){
			mSteering = Ogre::StringConverter::parseReal(Ogre::String(element->GetText()));
		}
	}

	//set up fields that are not in xml
	mSpeed = 0.0f;
}

Hovercraft::~Hovercraft(void){
}


void Hovercraft::process(float timeSince){
	if ((timeSince > 0.0f) && (mNode->getRole() == eZCom_RoleAuthority)) {

		//Fetch from havok
		HavokEntity * character = Havok::getSingleton().getCharacter(mName.c_str());
		const hkVector4& position = character->getPosition();
		changePosition(Ogre::Vector3(position(0),position(1),position(2)));

		const hkVector4& velocity = character->getVelocity();
		changeVelocity(Ogre::Vector3(velocity(0),velocity(1),velocity(2)));

		const hkQuaternion& rotation = character->getOrientation();
		changeOrientation(Ogre::Quaternion(rotation(3),rotation(0),rotation(1),rotation(2)));
	}
}

void Hovercraft::processEventsServer(ControllerEvent* cEvent){
	// Save the new event in the moving status
	BasicEntityEvent* movestatus = dynamic_cast<BasicEntityEvent*>(cEvent);
	if (mControlsActive && !mFinished) {
		if (movestatus) {
		mMovingStatus = *movestatus;
		}
	} else {
		mMovingStatus.clear();
	}
}

void Hovercraft::setupReplication(){
	//set up replication
	Entity::setupReplication();

	//name
	replicateString(&mDisplayName, ZCOM_REPRULE_AUTH_2_ALL);

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

	//mMaximumSpeed
	mNode->addReplicationFloat(&mMaximumSpeed,
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
	//mSteering
	mNode->addReplicationFloat(&mSteering,
	4,
	ZCOM_REPFLAG_MOSTRECENT,
	ZCOM_REPRULE_AUTH_2_ALL
	);

	//Collision state
	mNode->addReplicationBool(&mCollisionState, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_AUTH_2_ALL);
}

void Hovercraft::setAnnouncementData(ZCom_BitStream* stream) {
	Entity::setAnnouncementData(stream);
	
	stream->addInt(mDisplayName.length(),sizeof(int) * 8);
	if ( mDisplayName.length() != 0 ){
		stream->addString(mDisplayName.c_str());
	}
}

std::string Hovercraft::getClassName(){
	return "Hovercraft";
}

}
