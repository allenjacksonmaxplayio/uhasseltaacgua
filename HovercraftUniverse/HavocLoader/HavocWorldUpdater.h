#ifndef HAVOCWORLDUPDATER_H
#define HAVOCWORLDUPDATER_H

#include <OgreFrameListener.h>

// Math and base include
#include <Common/Base/hkBase.h>
#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Memory/hkThreadMemory.h>
#include <Common/Base/Memory/Memory/Pool/hkPoolMemory.h>
#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/Base/Monitor/hkMonitorStream.h>

// Dynamics includes
#include <Physics/Collide/hkpCollide.h>										
#include <Physics/Collide/Agent/ConvexAgent/SphereBox/hkpSphereBoxAgent.h>	
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>					
#include <Physics/Collide/Shape/Convex/Sphere/hkpSphereShape.h>				
#include <Physics/Collide/Dispatch/hkpAgentRegisterUtil.h>					

#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastInput.h>			
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>			

#include <Physics/Dynamics/World/hkpWorld.h>								
#include <Physics/Dynamics/Entity/hkpRigidBody.h>							
#include <Physics/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>	

#include <Common/Base/Thread/Job/ThreadPool/Cpu/hkCpuJobThreadPool.h>
#include <Common/Base/Thread/Job/ThreadPool/Spu/hkSpuJobThreadPool.h>
#include <Common/Base/Thread/JobQueue/hkJobQueue.h>

// Visual Debugger includes
#include <Common/Visualize/hkVisualDebugger.h>
#include <Physics/Utilities/VisualDebugger/hkpPhysicsContext.h>				

#include <stdio.h>
static void HK_CALL errorReport(const char* msg, void*)
{
	printf("%s", msg);
}

class HavocWorldUpdater : public Ogre::FrameListener
{
private:

	hkVisualDebugger* vdb;

	hkpPhysicsContext* context;

	hkArray<hkProcessContext*> * contexts;

	hkpWorld* physicsWorld;

	hkJobQueue* jobQueue;

	int totalNumThreadsUsed;

	hkJobThreadPool* threadPool;

	char* stackBuffer;

	hkPoolMemory* memoryManager;

	hkThreadMemory* threadMemory;

	hkpRigidBody* g_ball;

	//
	// Forward declarations
	//
	void setupPhysics(hkpWorld* physicsWorld);

	void createBrickWall( hkpWorld* world, int height, int length, const hkVector4& position, hkReal gapWidth, hkpConvexShape* box, hkVector4Parameter halfExtents );

public:

	HavocWorldUpdater(void);

	virtual ~HavocWorldUpdater(void);

	virtual bool frameStarted (const Ogre::FrameEvent &evt);
};

#endif
