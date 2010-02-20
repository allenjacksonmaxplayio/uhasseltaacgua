#ifndef SAMPLEEVENTMOVEBACKWARD_H_
#define SAMPLEEVENTMOVEBACKWARD_H_

#include "Event.h"

namespace HovUni {

class SampleEventMoveBackward: public Event
{
public:
	/**
	 * Constructor
	 *
	 * @param distance the distance to move backward
	 */
	SampleEventMoveBackward(float distance);

	/**
	 * Constructor for parsing
	 */
	SampleEventMoveBackward();

	/**
	 * Destructor
	 */
	virtual ~SampleEventMoveBackward();

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
	static SampleEventMoveBackward parse(ZCom_BitStream* stream);

private:
	/** The distance */
	float mDistance;
};

}

#endif
