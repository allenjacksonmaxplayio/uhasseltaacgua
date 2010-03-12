#ifndef FINISH_H
#define FINISH_H

#include "ParseException.h"
#include <tinyxml/tinyxml.h>
#include "Entity.h"

namespace HovUni {

/**
 * @author PJ
 */ 
class Finish : public Entity{
public:

	static const Ogre::String CATEGORY;

	/**
	 * Constructor
	 */
	Finish(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float processInterval);

	/**
	 * load
	 * @param data, xml element that descripes the finish
	 * @throws ParseException
	 */
	void load(TiXmlElement * data) throw(ParseException);

	/**
	 * Destructor
	 */
	~Finish(void);

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
