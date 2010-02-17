#pragma once

#include "Entity.h"
#include <zoidcom/zoidcom_control.h>

class Tree : public Entity
{
	static ZCom_ClassID mClassID;
public:
	Tree(ZCom_Control* control);
	~Tree(void);

	static void registerClass(ZCom_Control* control);
	static ZCom_ClassID getClassID();
};
