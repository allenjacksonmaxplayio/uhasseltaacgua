#pragma once

#define ZCOM_REPFLAG_SETUPAUTODELETE   (1L << 6)
#include <zoidcom/zoidcom_node.h>

class Entity
{
protected:
	ZCom_Node* mNode;
	bool mDeleteMe;
public:
	Entity(void);
	virtual ~Entity(void);
	void processNodeEvents();
	ZCom_Node* getNetworkNode();
};
