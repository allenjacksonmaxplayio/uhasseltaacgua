#ifndef INITEVENT_H
#define INITEVENT_H

#include "GameEvent.h"

namespace HovUni {

/**
 * A generic event that can be sent on an EventInit of Zoidcom
 *
 * @author Olivier Berghmans
 */
class InitEvent : public GameEvent
{
private:
	// The bit stream
	ZCom_BitStream* mStream;

public:

	/**
	 * Constructor
	 *
	 * @param stream the init stream
	 */
	InitEvent(ZCom_BitStream* stream);

	/**
	 * Default constructor for event construction
	 */
	InitEvent();

	/**
	 * Destructor
	 */
	virtual ~InitEvent();

	/**
	 * Get the stream
	 *
	 * @return the stream
	 */
	ZCom_BitStream* getStream() {
		return mStream;
	}

	//Network functionality

	void write(ZCom_BitStream* stream) const;

	void read(ZCom_BitStream* stream);

	static InitEvent * parse(ZCom_BitStream* stream);
};

}

#endif
