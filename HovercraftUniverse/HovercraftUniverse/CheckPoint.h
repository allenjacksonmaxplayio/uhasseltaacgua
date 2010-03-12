#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "Exception.h"
#include "Entity.h"
#include <OgreString.h>
#include <OgrePlatform.h>
#include <tinyxml/tinyxml.h>

namespace HovUni {

/**
 * @author PJ
 */ 
class CheckPoint : public Entity {
private:

	/**
	 * The name
	 */
	Ogre::String mName;

	/**
	 * The number
	 */
	Ogre::int32 mNumber;

public:

	/**
	 * The category used for checkpoints
	 */
	static const Ogre::String CATEGORY;

	/**
	 * Constructor
	 */
	CheckPoint(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float processInterval);

	/**
	 * Load
	 * @param data, xml element that descripes the checkpoint
	 * @throws ParseException
	 */
	void load(TiXmlElement * data) throw(ParseException);

	/**
	 * Destructor
	 */
	~CheckPoint(void);

	/**
	 * Get the name
	 * @return name
	 */
	inline Ogre::String getName() const {
		return mName;
	}

	/**
	 * Set the name
	 * @param name
	 */
	inline void setName(const Ogre::String& name) {
		mName = name;
	}

	/**
	 * Get the number
	 * @return number
	 */
	inline Ogre::int32 getNumber() const {
		return mNumber;
	}

	/**
	 * Set the number
	 * @param number
	 */
	inline void setNumber(Ogre::int32 number) {
		mNumber = number;
	}

	/**
	 * Callback to process this entity. This allows to do entity specific processing
	 *(e.g. intermediate actions).
	 *
	 * @param timeSince the time since the last processing of the entity
	 */
	virtual void process(float timeSince){
	}

	/**
	 * Callback to process a controller event at the server that got processed by the 
	 * controller.  Must be overriden since this class in itself has no clue which 
	 * controller properties there are.
	 *
	 * @param event a controller event
	 */
	virtual void processEventsServer(ControllerEvent* event){
	}

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


};

}

#endif
