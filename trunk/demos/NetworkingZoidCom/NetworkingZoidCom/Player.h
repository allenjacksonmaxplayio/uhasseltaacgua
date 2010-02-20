#pragma once

#include "Entity.h"
#include "Event.h"
#include <zoidcom/zoidcom_control.h>

using HovUni::Event;

class Player: public HovUni::Entity
{
	static ZCom_ClassID mClassID;
public:
	Player(ZCom_Control* control);
	~Player(void);
	virtual void processEntityEvents(const Event& event);

	static void registerClass(ZCom_Control* control);
	static ZCom_ClassID getClassID();
};
