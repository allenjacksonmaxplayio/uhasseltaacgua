#ifndef NETWORKMOVEMENTENTITY_H_
#define NETWORKMOVEMENTENTITY_H_

#include "NetworkEntity.h"

namespace HovUni {

/**
 * This class represents a network entity that has a position and can
 * include movement.
 *
 * @author Olivier Berghmans
 */
class NetworkMovementEntity: public NetworkEntity {
private:
	/** The position */
	float mPosition[3];

public:
	/**
	 * Constructor
	 *
	 * @param replicators the estimated number of replicators for this entity
	 */
	NetworkMovementEntity(unsigned short replicators = 0);

	/**
	 * Destructor
	 */
	~NetworkMovementEntity();

	/**
	 * Get the position
	 *
	 * @param pos the array of size 3 containing the position
	 */
	void getPosition(float* pos) const;

	/**
	 * Set the position (at Authority)
	 *
	 * @param pos the array of size 3 containing the position
	 */
	void setPosition(float* pos);

private:
	/**
	 * @see NetworkEntity::setReplication()
	 */
	void setupReplication();

	/**
	 * A callback that should be implemented so the replicators for this
	 * entity can be set up. In case the number of replicators given to the
	 * constructor is zero, this callback can be implemented as empty.
	 */
	virtual void addReplicators() = 0;

};

}

#endif
