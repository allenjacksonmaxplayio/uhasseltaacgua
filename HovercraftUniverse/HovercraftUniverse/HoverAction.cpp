#include "HoverAction.h"
#include "HavokHovercraft.h"

#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Collide/Shape/Query/hkpShapeRayCastInput.h>
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>
#include <Physics/Internal/Collide/BroadPhase/hkpBroadPhase.h>
#include <Physics/Collide/Shape/Query/hkpRayHitCollector.h>

#include <Common/Visualize/hkDebugDisplay.h>

#include "HavokEntityType.h"
#include "Hovercraft.h"

#include <iostream>

namespace HovUni {

class UserRayHitCollector: public hkpRayHitCollector {
	private:
		hkpWorldRayCastInput m_ray;

	public:
		UserRayHitCollector( hkpWorldRayCastInput& ray ): m_ray(ray) {;}

	protected:

		virtual void addRayHit( const hkpCdBody& cdBody, const hkpShapeRayCastCollectorOutput& hitInfo )
  		{
			hkpWorldObject *object = static_cast<hkpWorldObject*>( cdBody.getRootCollidable()->getOwner() );

			if ( object->getName() )
				std::cout << object->getName() << std::endl;
			else
				std::cout << "UNKNOWN" << std::endl;

			if ( HavokEntityType::getEntityType(object) == HavokEntityType::PLANET ){
			
				std::cout << object->getName() << std::endl;

				hkVector4 hitPoint;
				hitPoint.setInterpolate4( m_ray.m_from, m_ray.m_to, hitInfo.m_hitFraction );

				HK_DISPLAY_LINE(  m_ray.m_from, hitPoint, hkColor::RED);
			}
		}		
};




//The filter
HoverAction::PlanetRayCastCallback::PlanetRayCastCallback( const hkpWorldRayCastInput& input, hkpWorldRayCastOutput* output ):
	mInput(input), mOutput(output)
{
}

hkReal HoverAction::PlanetRayCastCallback::addBroadPhaseHandle( const hkpBroadPhaseHandle* broadPhaseHandle, int castIndex ){

	const hkpCollidable* col = static_cast<hkpCollidable*>( static_cast<const hkpTypedBroadPhaseHandle*>(broadPhaseHandle)->getOwner() );
	const hkpShape* shape = col->getShape();

	if (shape)
	{
		if ( col->getType() == hkpWorldObject::BROAD_PHASE_ENTITY ){
			const hkpEntity* ent = static_cast<hkpEntity*>(col->getOwner());

			if ( HavokEntityType::getEntityType(ent) == HavokEntityType::PLANET ){


				//std::cout << "BROADPHASE FOUND " <<  ent->getName() << std::endl;


				//TODO THIS CODE IS WRONG!!!!!!!!!!!!!!!!!!!!!!

				hkpShapeRayCastInput sinput;
				const hkTransform& trans = col->getTransform();

				// transform the ray into local space
				sinput.m_from.setTransformedInversePos(trans, mInput.m_from);
				sinput.m_to.setTransformedInversePos(trans, mInput.m_to);

				// subshape filtering turned off
				sinput.m_rayShapeCollectionFilter = HK_NULL;

				HK_DISPLAY_ARROW ( sinput.m_from, sinput.m_to, hkColor::RED);

				if (shape->castRay(sinput, *mOutput))
				{
					// transform the normal back into worldspace
					mOutput->m_rootCollidable = col;
					mOutput->m_normal.setRotatedDir( trans.getRotation(), mOutput->m_normal );
				}
			}
		}
	}
	
	return mOutput->m_hitFraction;
}

//The implementation

HoverAction::HoverAction(HavokHovercraft * entity, hkpWorld * world):
	hkpUnaryAction(entity->getRigidBody()), mHovercraft(entity), mWorld(world)
{
}

HoverAction::~HoverAction(void)
{
}

void HoverAction::applyAction( const hkStepInfo& stepInfo ){

	hkpWorldRayCastInput ray;
	{
		hkVector4 offset;

		//position
		ray.m_from = mHovercraft->getRigidBody()->getPosition();
		offset = mHovercraft->getUp();
		//offset.mul4(0.1);	//dont start at very bottom  to prevent small penetrationt from stopping the hovering
		ray.m_from.add4(offset);	

		//position + inverse of up
		ray.m_to = mHovercraft->getRigidBody()->getPosition();
		offset = mHovercraft->getUp();
		offset.mul4(-2);
		ray.m_to.add4(offset);
	}

	/*UserRayHitCollector collector(ray);
	mWorld->lock();
	mWorld->castRay( ray, collector );
	mWorld->unlock();*/

	hkpWorldRayCastOutput output;
	{
		PlanetRayCastCallback rayCallback( ray, &output );

		hkpBroadPhase* broadPhase = mWorld->getBroadPhase();
		hkpBroadPhase::hkpCastRayInput rayInput;
		rayInput.m_from = ray.m_from;
		rayInput.m_toBase = &ray.m_to;
		rayInput.m_aabbCacheInfo = HK_NULL;

		broadPhase->castRay(rayInput, &rayCallback, hkSizeOf(PlanetRayCastCallback)  );
	}

	// To visualise the raycast we make use of a macro defined in "hkDebugDisplay.h" called HK_DISPLAY_LINE.
	// The macro takes three parameters: a start point, an end point and the line colour.
	// If a hit is found we display a RED line from the raycast start point to the point of intersection and mark that
	// point with a small RED cross. The intersection point is calculated using: startWorld + (result.m_mindist * endWorld).
	// We also set the object to display in RED, once again making use of the HK_SET_OBJECT_COLOR macro.
	//
	// If no hit is found we simply display a GREY line between the raycast start and end points.

	if ( output.hasHit() )
	{
		hkVector4 intersectionPointWorld;
		intersectionPointWorld.setInterpolate4( ray.m_from, ray.m_to, output.m_hitFraction );
		
		std::cout << "YEEEEEE" << std::endl;

		HK_DISPLAY_LINE( ray.m_from, intersectionPointWorld, hkColor::RED);
		//HK_SET_OBJECT_COLOR((hkUlong)output.m_rootCollidable, hkColor::RED);
	}


/*



// hovering
			hkVector4 hover;
			hkVector4 position = rb->getPosition();
			hkVector4 ground = collector.getHitContact().getPosition();

			hkVector4 difference(position(0) - ground(0), position(1) - ground(1), position(2) - ground(2));
			float distanceSquared = difference.lengthSquared3();
			float distance = difference.length3();
			float magnitude = 0.0f;
			if (distance > 0.01f && distance <= mHoveringHeight) {
				
				magnitude = (1.0f / distance) * (mCharacterGravity + mGravityForce) * mHoveringHeight;
				//magnitude = (1.0f / distanceSquared) * (mCharacterGravity + mGravityForce) * mHoveringHeight * mHoveringHeight;
				
			} else if (distance > mHoveringHeight) {
				magnitude = (1.0f / distanceSquared) * (mCharacterGravity + mGravityForce) * mHoveringHeight * mHoveringHeight * 0.95f;
			}
			
			//std::cout << magnitude << "  " << distance << std::endl;
			//difference(1) = 0;
			//std::cout << difference.length3() << " - " << difference(0) << ", " << difference(1) << ", " << difference(2) << std::endl;

			hover.setMul4(rb->getMass() * magnitude, newUp);
			rb->applyForce(stepInfo.m_deltaTime, hover);*/
}

}