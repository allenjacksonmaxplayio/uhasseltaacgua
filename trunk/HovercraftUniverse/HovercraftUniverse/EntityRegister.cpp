#include "EntityRegister.h"

namespace HovUni {

EntityRegister::EntityRegister(void)
{
}

EntityRegister::~EntityRegister(void)
{
}

void EntityRegister::registerAll(NetworkIDManager& manager) {
	manager.registerClass("DummyHovercraft");
}

}