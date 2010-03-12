#ifndef PORTAL_H
#define PORTAL_H

#include "ParseException.h"
#include <tinyxml/tinyxml.h>
#include <OgreString.h>
#include <OgreVector3.h>
#include <OgrePlatform.h>
#include "Entity.h"

namespace HovUni {

/**
 * Portal 
 * A portal is a teleportation mechanism that ports objects from begin to end
 * @author PJ	
 */
class Portal : Entity
{
private:

	/**
	 * Name of the portal
	 */
	Ogre::String mName;

	/**
	 * Start of the portal
	 */
	Ogre::Vector3 mStart;

	/**
	 * End of the portal
	 */
	Ogre::Vector3 mEnd;

public:

	/**
	 * Constructor
	 */
	Portal(const Ogre::String& name, const Ogre::String& category, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float processInterval);


	/**
	 * load
	 * @param data
	 * @throws ParseException
	 */
	void load(TiXmlElement * data) throw (ParseException);

	/**
	 * Destructor
	 */
	~Portal(void);

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
	inline void setName( const Ogre::String& name ) {
		mName = name;
	}

	/**
	 * Get start point of the portal
	 * @return start
	 */
	inline const Ogre::Vector3& getStart() const {
		return mStart;
	}

	/**
	 * Get start point of the portal
	 * @return start
	 */
	inline Ogre::Vector3& getStart() {
		return mStart;
	}

	/**
	 * Set the start point of the portal
	 * @param start
	 */
	void setStart( const Ogre::Vector3& start ){
		mStart = start;
	}

	/**
	 * Get end point of the portal
	 * @return end
	 */
	inline const Ogre::Vector3& getEnd() const {
		return mEnd;
	}

	/**
	 * Get end point of the portal
	 * @return end
	 */
	inline Ogre::Vector3& getEnd() {
		return mEnd;
	}

	/**
	 * Set the end point of the portal
	 * @param end
	 */
	void setEnd( const Ogre::Vector3& end ){
		mEnd = end;
	}

	/**
	 * Callback to process this entity. This allows to do entity specific processing
	 * (e.g. intermediate actions).
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