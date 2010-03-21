#ifndef HOVERCRAFT_H
#define HOVERCRAFT_H

#include "Entity.h"
#include <tinyxml/tinyxml.h>
#include "Exception.h"

#include "BasicEntityEvent.h"

namespace HovUni {

/**
 * @author PJ
 */ 
class Hovercraft : public Entity{
private:

	/**
	 * The moving status 
	 */
	BasicEntityEvent mMovingStatus;

	/**
	 * Tilt test 
	 */
	float mTilt;

	/**
	 * The name
	 */
	Ogre::String mDisplayName;

	/**
	 * The name
	 */
	Ogre::String mDescription;

	/**
	 * The default maximum speed
	 */
	Ogre::Real mMaximumSpeed;

	/**
	 * The current speed
	 */
	Ogre::Real mSpeed;

	/**
	 * The mass
	 */
	Ogre::Real mMass;

	/**
	 * The base acceleration without powerups
	 */
	Ogre::Real mAcceleration;

public:

	/**
	 * The maximum speed any hovercraft can reach, defined in game.userdatatypes.xml
	 */
	static const Ogre::Real MAXSPEED;

	/**
	 * The category used for hovercrafts
	 */
	static const Ogre::String CATEGORY;

	/**
	 * Constructor.
	 *
	 * @param name The name of the hovercraft
	 * @param position
	 * @param quaternion
	 * @param processInterval The process interval
	 */
	Hovercraft(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, const Ogre::String& ogreentity, float processInterval);

	/**
	 * Constructor.
	 * 
	 * @param announcedata
	 */
	Hovercraft( ZCom_BitStream* announcedata );

	/**
	 * load
	 * @param data, xml element that descripes the hovercraft
	 * @throws ParseException
	 */
	void load(TiXmlElement * data) throw(ParseException);

	/**
	 * Destructor
	 */
	~Hovercraft(void);

	/**
	 * Get the moving status
	 * @return the moving status
	 */
	inline const BasicEntityEvent& getMovingStatus() const {
		return mMovingStatus;
	}

	/**
	 * Get the name
	 * @return name
	 */
	inline Ogre::String getDisplayName() const {
		return mDisplayName;
	}

	/**
	 * Set the name
	 * @param name
	 */
	inline void setDisplayName(const Ogre::String& name) {
		mDisplayName = name;
	}

	/**
	 * Get the description
	 * @return description
	 */
	inline Ogre::String getDescription() const {
		return mDescription;
	}

	/**
	 * Set the description
	 * @param description
	 */
	inline void setDescription(const Ogre::String& description) {
		mDescription = description;
	}

	/**
	 * Get the maximum speed
	 * @return maximum speed
	 */
	inline Ogre::Real getMaximumSpeed() const {
		return mMaximumSpeed;
	}

	/**
	 * Get the current speed
	 * @return speed
	 */
	inline Ogre::Real getSpeed() const {
		return mSpeed;
	}

	/**
	 * Set the current speed
	 * @param speed
	 */
	inline void setSpeed(Ogre::Real speed) {
		mSpeed = speed;
	}

	/**
	 * Get the mass
	 * @return mass
	 */
	inline Ogre::Real getMass() const {
		return mMass;
	}

	/**
	 * Set the mass
	 * @param mass
	 */
	inline void setMass(Ogre::Real mass) {
		mMass = mass;
	}

	/**
	 * Get the acceleration
	 * @return acceleration
	 */
	inline Ogre::Real getAcceleration() const {
		return mAcceleration;
	}

	/**
	 * Set the acceleration
	 * @param acceleration
	 */
	inline void setAcceleration(Ogre::Real acceleration) {
		mAcceleration = acceleration;
	}

	/**
	 * Callback to process this entity. This allows to do entity specific processing
	 *(e.g. intermediate actions).
	 *
	 * @param timeSince the time since the last processing of the entity
	 */
	virtual void process(float timeSince);

	/**
	 * Callback to process a controller event at the server that got processed by the 
	 * controller.  Must be overriden since this class in itself has no clue which 
	 * controller properties there are.
	 *
	 * @param event a controller event
	 */
	virtual void processEventsServer(ControllerEvent* event);

	/**
	 * Callback to process a controller event at the owner that got processed by the 
	 * controller.  Must be overriden since this class in itself has no clue which 
	 * controller properties there are.
	 *
	 * @param event a controller event
	 */
	virtual void processEventsOwner(ControllerEvent* event){
	}

	/**
	 * Callback to process a controller event at other clients that got processed by the controller.  Must
	 * be overriden since this class in itself has no clue which controller properties 
	 * there are.
	 *
	 * @param event a controller event
	 */
	virtual void processEventsOther(ControllerEvent* event){
	}

	/**
	 * @see NetworkEntity::setReplication()
	 */
	void setupReplication();

	/**
	 * Get the class name for this class. This is used for registering
	 * the class with the network
	 *
	 * @return the class name
	 */
	static std::string getClassName();
};

}

#endif
