#include "EntityRegister.h"
#include "Lobby.h"
#include "ChatEntity.h"

#include "Start.h"
#include "Finish.h"
#include "Asteroid.h"
#include "Hovercraft.h"
#include "CheckPoint.h"
#include "StartPosition.h"
#include "SpeedBoost.h"
#include "Track.h"
#include "Portal.h"
#include "PowerupSpawn.h"
#include "ResetSpawn.h"

namespace HovUni {

EntityRegister::EntityRegister(void)
{
}

EntityRegister::~EntityRegister(void)
{
}

void EntityRegister::registerAll(NetworkIDManager& manager) {
	manager.registerClass(Lobby::getClassName());
	manager.registerClass(ChatEntity::getClassName());

	//Entities
	manager.registerClass(Asteroid::getClassName());
	manager.registerClass(CheckPoint::getClassName());
	manager.registerClass(Finish::getClassName());
	manager.registerClass(Hovercraft::getClassName());
	manager.registerClass(Portal::getClassName());
	manager.registerClass(PowerupSpawn::getClassName());
	manager.registerClass(ResetSpawn::getClassName());
	manager.registerClass(SpeedBoost::getClassName());
	manager.registerClass(Start::getClassName());
	manager.registerClass(StartPosition::getClassName());

	manager.registerClass("DummyHovercraft");
}

}