#include "EntityRegister.h"
#include "Lobby.h"

namespace HovUni {

EntityRegister::EntityRegister(void)
{
}

EntityRegister::~EntityRegister(void)
{
}

void EntityRegister::registerAll(NetworkIDManager& manager) {
	manager.registerClass(Lobby::getClassName());
	manager.registerClass("DummyHovercraft");
}

}