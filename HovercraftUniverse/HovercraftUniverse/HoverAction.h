#ifndef HOVER_ACTION_H
#define HOVER_ACTION_H

#include <Physics/Dynamics/Action/hkpUnaryAction.h>
#include <Physics/Internal/Collide/BroadPhase/hkpBroadPhaseCastCollector.h>
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastInput.h>

class hkpWorld;

namespace HovUni {

class HavokHovercraft;

class HoverAction : public hkpUnaryAction
{
private:

	/**
	 * The hovercraft
	 */
	HavokHovercraft * mHovercraft;

	hkpWorld * mWorld;

public:

	static const hkUlong HK_HOVERACTION_ID = 0x28024501;

	HoverAction(HavokHovercraft * entity, hkpWorld * world);

	~HoverAction(void);

private:

	// This class links the output of the broadphase raycaster to the narrowphase raycaster.
	class PlanetRayCastCallback : public hkpBroadPhaseCastCollector
	{
		public:
		
			PlanetRayCastCallback( const hkpWorldRayCastInput& input, hkpWorldRayCastOutput* output );

		protected:
			// the function which is called every time the broadphase raycaster hits the aabb of an
			// object. This implementation checks the type of object and calls object->raycast if
			// necessary
			virtual	hkReal addBroadPhaseHandle( const hkpBroadPhaseHandle* broadPhaseHandle, int castIndex );

		private:
			// The information about the ray start and end point
			hkpWorldRayCastInput   mInput;

			// A pointer to the result data structure
			hkpWorldRayCastOutput* mOutput;
	};


	virtual void applyAction( const hkStepInfo& stepInfo );

	virtual hkpAction* clone( const hkArray<hkpEntity*>& newEntities, const hkArray<hkpPhantom*>& newPhantoms ) const { 
		return HK_NULL; 
	}
};

}

#endif
