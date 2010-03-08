#include "Havok.h"
#include "HavokThread.h"

namespace HovUni {

HoverCraftUniverseWorld * Havok::ms_world = 0;

Havok::Havok(void)
{
}

Havok::~Havok(void)
{
}

void Havok::start() {
	//Server means Havok
	float timestep = 1.0f/120.0f;

	//do Havok sim in background
	ms_world = 0;
	HavokThread::StartHavokThread();
}


HoverCraftUniverseWorld * Havok::getSingletonPtr() {
	return ms_world;
}


HoverCraftUniverseWorld& Havok::getSingleton() {
	assert(ms_world);
	return *ms_world;
}

void Havok::stop() {
	HavokThread::StopHavokThread();
	ms_world = 0;
}

}
