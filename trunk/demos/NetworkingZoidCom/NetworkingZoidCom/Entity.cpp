#include "StdAfx.h"
#include "Entity.h"

namespace HovUni {

Entity::Entity(void) : mNode(0) {
	mNode = new ZCom_Node();
}

Entity::~Entity(void) {
	if (mNode) {
		delete mNode;
		mNode = 0;
	}
}

void Entity::processEvents() {
	while (mNode->checkEventWaiting()) {
		eZCom_Event type;
		eZCom_NodeRole remote_role;
		ZCom_ConnID conn_id;

		ZCom_BitStream* data = mNode->getNextEvent(&type, &remote_role, &conn_id);

		if (remote_role == eZCom_RoleAuthority && type == eZCom_EventRemoved) {
			mDeleteMe = true;
		} else if (type == eZCom_EventUser) {
			// Delegate to the user events callback
			Event e = Event::parse(data);
			processEntityEvents(e);
		}
	}
}

ZCom_Node* Entity::getNetworkNode() {
	return mNode;
}

}
