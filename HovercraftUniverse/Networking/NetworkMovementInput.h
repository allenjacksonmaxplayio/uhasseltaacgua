#ifndef NETWORKMOVEMENTINPUT_H_
#define NETWORKMOVEMENTINPUT_H_

#include <zoidcom/zoidcom.h>

namespace HovUni {

/**
 * This class represents input for a network movement entity
 *
 * @author Olivier Berghmans
 */
class NetworkMovementInput {
private:
	/** Whether the entity should move forward */
	bool mForward;

	/** Whether the entity should move backward */
	bool mBackward;

	/** Whether the entity should move left */
	bool mLeft;

	/** Whether the entity should move right */
	bool mRight;

public:
	/**
	 * Constructor
	 *
	 * @param forward whether the entity should move forward
	 * @param backward whether the entity should move backward
	 * @param left whether the entity should move left
	 * @param right whether the entity should move right
	 */
	NetworkMovementInput(bool forward = false, bool backward = false, bool left = false, bool right = false);

	/**
	 * Destructor
	 */
	~NetworkMovementInput();

	/**
	 * Write the input to a bitstream
	 *
	 * @param stream the bitstream
	 */
	void pack(ZCom_BitStream& stream) const;

	/**
	 * Read the input from a bitstream
	 *
	 * @param stream the bitstream
	 */
	void unpack(ZCom_BitStream& stream);

	/**
	 * The comparison operator
	 *
	 * @param input the input to compare with
	 * @return true if it is equal
	 */
	bool operator==(const NetworkMovementInput& input);

	/** 
	 * The assignment operator
	 *
	 * @param rhs the right hand side of the assignment
	 * @return the new value
	 */
	NetworkMovementInput& operator=(const NetworkMovementInput& rhs);

};

}

#endif
