#ifndef HAVOKHOVERCRAFTCOLLISIONEFFECT_H
#define HAVOKHOVERCRAFTCOLLISIONEFFECT_H

#include <Physics/Dynamics/Action/hkpUnaryAction.h>
#include <Physics/Dynamics/Collide/hkpCollisionListener.h>

namespace HovUni {

class HavokHovercraft;
class HavokHovercraftCollisionEffect;

class HovercraftCollisionListener : public hkpCollisionListener {

private:

	HavokHovercraftCollisionEffect * mCollisionEffect;

public:

	HovercraftCollisionListener(HavokHovercraftCollisionEffect * mCollisionEffect);

	void  contactPointAddedCallback (hkpContactPointAddedEvent &e);

	void  contactPointConfirmedCallback (hkpContactPointConfirmedEvent &e);
	 
	void  contactPointRemovedCallback (hkpContactPointRemovedEvent &e);
	 
	void  contactProcessCallback (hkpContactProcessEvent &e);
};

class HavokHovercraftCollisionEffect: public hkpUnaryAction
{
private:

	friend class HovercraftCollisionListener;
	
	HovercraftCollisionListener * mListener;
	
	HavokHovercraft * mHovercraft;

	hkVector4 mBounceVector;

	bool mHasCollision;

public:
	HavokHovercraftCollisionEffect(HavokHovercraft * hovercraft);

	~HavokHovercraftCollisionEffect(void);

	virtual void applyAction( const hkStepInfo& stepInfo );

	virtual hkpAction* clone( const hkArray<hkpEntity*>& newEntities, const hkArray<hkpPhantom*>& newPhantoms ) const { 
		return HK_NULL; 
	}
};

}

#endif