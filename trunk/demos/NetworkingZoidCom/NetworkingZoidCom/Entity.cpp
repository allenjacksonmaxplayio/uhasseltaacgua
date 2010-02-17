#include "StdAfx.h"
#include "Entity.h"

Entity::Entity(void) : mNode(0) {
	mNode = new ZCom_Node();
}

Entity::~Entity(void) {
	if (mNode) {
		delete mNode;
		mNode = 0;
	}
}

void Entity::processNodeEvents() {
	while (mNode->checkEventWaiting()) {
		eZCom_Event type;
		eZCom_NodeRole remote_role;
		ZCom_ConnID conn_id;

		ZCom_BitStream* data = mNode->getNextEvent(&type, &remote_role, &conn_id);

		if (remote_role == eZCom_RoleAuthority && type == eZCom_EventRemoved) {
			mDeleteMe = true;
		} else if (type == eZCom_EventUser) {
			const char* text = data->getStringStatic();
			zU32 number = data->getInt(8);
			cout << "User event occurred: " << (int) number << " " << text << endl;
			if (mNode->getRole() == eZCom_RoleAuthority) {
				ZCom_BitStream* event = new ZCom_BitStream();
				event->addString("Moved Up");
				event->addInt(40, 8);
				mNode->sendEvent(eZCom_Unreliable, ZCOM_REPRULE_AUTH_2_ALL, event);
			}
		}
	}
}

ZCom_Node* Entity::getNetworkNode() {
	return mNode;
}
