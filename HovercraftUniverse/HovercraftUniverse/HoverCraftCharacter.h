#ifndef HOVERCRAFTCHARACTER_H
#define HOVERCRAFTCHARACTER_H

#include "Character.h"

namespace HovUni {

class HoverCraftCharacter : public Character
{
private:

	hkBool HoverCraftCharacter::reorientCharacter( const hkRotation& rotation );

public:

	HoverCraftCharacter( hkpWorld * world, hkpCharacterRigidBodyCinfo * info,  hkpCharacterContext * characterContext);

	virtual ~HoverCraftCharacter(void);

	virtual void update( UserInput & input );
};

}

#endif
