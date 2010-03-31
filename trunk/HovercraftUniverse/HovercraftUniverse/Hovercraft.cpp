#include "Hovercraft.h"
#include <OgreStringConverter.h>

#include "Havok.h"

#include "String_Replicator.h"

namespace HovUni {

const Ogre::String Hovercraft::CATEGORY("Hovercraft");

const Ogre::Real Hovercraft::MAXSPEED(5000);

Hovercraft::Hovercraft(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, const Ogre::String& ogreentity, float processInterval):
	Entity(name,CATEGORY,position,orientation,ogreentity,processInterval,6), mTilt(0.0f)
	{

		//fill some defaults for testing
		mSpeed = 0;
		mMaximumSpeed = 50000;
		mAcceleration = 1000;
		mMass = 50;
}

Hovercraft::Hovercraft( ZCom_BitStream* announcedata ):
	Entity(announcedata,CATEGORY,6)
{
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

	//set up fields that are not in xml
	mSpeed = 0.0f;
}

Hovercraft::~Hovercraft(void){
}


void Hovercraft::process(float timeSince){
	if ( (timeSince > 0.0f) && (mNode->getRole() == eZCom_RoleAuthority)) {

		//Fetch from havok
		HavokEntity * character = Havok::getSingleton().getCharacter(mName.c_str());
		const hkVector4& position = character->getPosition();
		changePosition(Ogre::Vector3(position(0),position(1),position(2)));

		const hkVector4& velocity = character->getVelocity();
		changeVelocity(Ogre::Vector3(velocity(0),velocity(1),velocity(2)));

		const hkQuaternion& rotation = character->getOrientation();
		changeOrientation(Ogre::Quaternion(rotation(3),rotation(0),rotation(1),rotation(2)));


		//std::cout << rotation(0) << "," << rotation(1) << "," << rotation(2) << "," << rotation(3) << std::endl;

		//changeOrientation(Ogre::Quaternion(rotation(3),rotation(0),rotation(1),rotation(2)));

		/*Ogre::Vector3 accumulatedDirection = Ogre::Vector3::ZERO;
		float accumulatedRotation = 0.0f;
		float accumulatedTilt = mTilt;
		

		// calculate new direction
		if (mMovingStatus.moveLeft()) { 
			// check direction, we won't allow turning without moving
			if (mMovingStatus.moveForward()) {
				accumulatedRotation += 1.0f;
			} else if (mMovingStatus.moveBackward()) {
				accumulatedRotation -= 1.0f;
			}
			// set tilt
			if ((mMovingStatus.moveForward() || mMovingStatus.moveBackward()) && mTilt > -20.0f) {
				mTilt -= 0.5f;
			}
		}
		if (mMovingStatus.moveRight()) { 
			// check direction, we won't allow turning without moving
			if (mMovingStatus.moveForward()) {
				accumulatedRotation -= 1.0f;
			} else if (mMovingStatus.moveBackward()) {
				accumulatedRotation += 1.0f;
			}
			// set tilt
			if ((mMovingStatus.moveForward() || mMovingStatus.moveBackward()) && mTilt < 20.0f) {
				mTilt += 0.5f;
			}
		}
		// if not turning, lower tilt
		if ((!mMovingStatus.moveLeft() && !mMovingStatus.moveRight()) || 
					((mMovingStatus.moveLeft() || mMovingStatus.moveRight()) && (!mMovingStatus.moveForward() && !mMovingStatus.moveBackward()))) {
			mTilt *= 0.9f;
		}
		

		// calculate orientation
		// TODO: Should be the UpVector, but in the tilt test this would give weird results...
		//Ogre::Quaternion quat = Ogre::Quaternion(Ogre::Degree(Ogre::Real(accumulatedRotation)), getUpVector());
		Ogre::Quaternion rotation = Ogre::Quaternion(Ogre::Degree(Ogre::Real(accumulatedRotation)), Ogre::Vector3::UNIT_Y);
		changeOrientation(rotation);

		//calculate tilt
		accumulatedTilt = mTilt - accumulatedTilt;
		Ogre::Quaternion tilt = Ogre::Quaternion(Ogre::Degree(Ogre::Real(accumulatedTilt)), getOrientation());
		changeOrientation(tilt);

		

		// move forward and/or backward
		if (mMovingStatus.moveForward()) { 
			accumulatedDirection += getOrientation(); 
		}
		if (mMovingStatus.moveBackward()) { 
			accumulatedDirection -= getOrientation(); 
		}
		accumulatedDirection.normalise();
	
		changePosition(getPosition() + accumulatedDirection * timeSince * 100);*/
	}
}

void Hovercraft::processEventsServer(ControllerEvent* event){
	// Save the new event in the moving status
	BasicEntityEvent* movestatus = dynamic_cast<BasicEntityEvent*>(event);
	if (movestatus) {
		mMovingStatus = *movestatus;
	}
}

void Hovercraft::setupReplication(){
	//set up replication
	Entity::setupReplication();

	//name
	replicateString(&mDisplayName);

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
}

std::string Hovercraft::getClassName(){
	return "Hovercraft";
}

}
