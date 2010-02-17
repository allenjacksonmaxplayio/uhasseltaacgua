#pragma once

#include "Entity.h"
#include <zoidcom/zoidcom_control.h>

class Player: public Entity
{
	static ZCom_ClassID mClassID;
public:
	Player(ZCom_Control* control);
	~Player(void);

	static void registerClass(ZCom_Control* control);
	static ZCom_ClassID getClassID();
};
