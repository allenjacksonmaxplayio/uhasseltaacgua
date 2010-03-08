#include "Havoc.h"
#include "HavocThread.h"

namespace HovUni {

HoverCraftUniverseWorld * Havoc::ms_world = 0;

Havoc::Havoc(void)
{
}

Havoc::~Havoc(void)
{
}

void Havoc::start() {
	//Server means Havoc
	float timestep = 1.0f/120.0f;

	//do havoc sim in background
	ms_world = new HoverCraftUniverseWorld (timestep);

	HavocThread::StartHavocThread();
}


HoverCraftUniverseWorld * Havoc::getSingletonPtr() {
	return ms_world;
}


HoverCraftUniverseWorld& Havoc::getSingleton() {
	assert(ms_world);
	return *ms_world;
}

void Havoc::stop() {
	HavocThread::StopHavocThread();

	delete ms_world;
}

}
