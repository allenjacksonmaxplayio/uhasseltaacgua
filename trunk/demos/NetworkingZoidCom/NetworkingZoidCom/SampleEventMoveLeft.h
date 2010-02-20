#ifndef SAMPLEEVENTMOVELEFT_H_
#define SAMPLEEVENTMOVELEFT_H_

#include "Event.h"

namespace HovUni {

class SampleEventMoveLeft: public Event
{
public:
	/**
	 * Constructor
	 *
	 * @param distance the distance to move left
	 */
	SampleEventMoveLeft(float distance);

	/**
	 * Constructor for parsing
	 */
	SampleEventMoveLeft();

	/**
	 * Destructor
	 */
	virtual ~SampleEventMoveLeft();

	/**
	 * Write the event
	 *
	 * @param stream the bitstream to append the event
	 */
	virtual void write(ZCom_BitStream* stream);

	/**
	 * Read the event
	 *
	 * @param stream the bitstream containing the event
	 */
	virtual void read(ZCom_BitStream* stream);

	/**
	 * Parse the stream to create this event
	 *
	 * @param stream the bitstream containing the event
	 * @return the event
	 */
	static SampleEventMoveLeft parse(ZCom_BitStream* stream);

private:
	/** The distance */
	float mDistance;
};

}

#endif
