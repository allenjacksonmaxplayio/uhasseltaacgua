#ifndef HAVOCWORLDUPDATER_H
#define HAVOCWORLDUPDATER_H

// Math and base include
#include <Common/Base/hkBase.h>
#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Memory/hkThreadMemory.h>
#include <Common/Base/Memory/Memory/Pool/hkPoolMemory.h>
#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>

// Dynamics includes
#include <Physics/Collide/hkpCollide.h>										
#include <Physics/Collide/Agent/ConvexAgent/SphereBox/hkpSphereBoxAgent.h>	
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>					
#include <Physics/Collide/Shape/Convex/Sphere/hkpSphereShape.h>				
#include <Physics/Collide/Dispatch/hkpAgentRegisterUtil.h>	
#include <Physics/Collide/Filter/Group/hkpGroupFilterSetup.h>

#include <Physics/Utilities/Serialize/hkpHavokSnapshot.h>
#include <Physics/Utilities/Serialize/hkpPhysicsData.h>

#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastInput.h>			
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>			

#include <Physics/Dynamics/World/hkpWorld.h>								
#include <Physics/Dynamics/Entity/hkpRigidBody.h>							
#include <Physics/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>	

#include <Common/Base/Thread/Job/ThreadPool/Cpu/hkCpuJobThreadPool.h>
#include <Common/Base/Thread/Job/ThreadPool/Spu/hkSpuJobThreadPool.h>
#include <Common/Base/Thread/JobQueue/hkJobQueue.h>
#include <Common/Serialize/Packfile/hkPackfileReader.h>

// Visual Debugger includes
#include <Common/Visualize/hkVisualDebugger.h>
#include <Physics/Utilities/VisualDebugger/hkpPhysicsContext.h>				

#include <stdio.h>
static void HK_CALL errorReport(const char* msg, void*)
{
	printf("%s", msg);
}

class hkpPhysicsData;

class HavocWorldUpdater
{
public:

	// Current world's up vector. This changes as the simulation progresses.
 	static hkVector4 m_worldUp;

protected:

	void loadWorld( const char* path );

	hkpWorld* mPhysicsWorld;

	hkPackfileReader::AllocatedData* mLoadedData;

	hkpPhysicsData* mPhysicsData;

	hkVector4 mStartPos;

	hkQuaternion mStartRotation;

private:

	hkVisualDebugger* vdb;

	hkpPhysicsContext* context;

	hkArray<hkProcessContext*> * contexts;

	hkJobQueue* jobQueue;

	int totalNumThreadsUsed;

	hkJobThreadPool* threadPool;

	char* stackBuffer;

	hkPoolMemory* memoryManager;

	hkThreadMemory* threadMemory;

public:

	HavocWorldUpdater( const char * file );

	virtual ~HavocWorldUpdater(void);

	void update( hkReal timestep );
};

#endif
