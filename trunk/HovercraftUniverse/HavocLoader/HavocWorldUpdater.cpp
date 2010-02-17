#include "HavocWorldUpdater.h"

// Keycode
#include <Common/Base/keycode.cxx>

#if !defined USING_HAVOK_PHYSICS
#error Physics is needed to build this demo. It is included in the common package for reference only.
#endif

// Classlists
#define INCLUDE_HAVOK_PHYSICS_CLASSES
#define HK_CLASSES_FILE <Common/Serialize/Classlist/hkClasses.h>
#include <Common/Serialize/Util/hkBuiltinTypeRegistry.cxx>

// Generate a custom list to trim memory requirements
#define HK_COMPAT_FILE <Common/Compat/hkCompatVersions.h>
#include <Common/Compat/hkCompat_None.cxx>

HavocWorldUpdater::HavocWorldUpdater(void)
{
	//
	// Initialize the base system including our memory system
	//

	memoryManager = new hkPoolMemory();
	threadMemory = new hkThreadMemory(memoryManager);
	hkBaseSystem::init( memoryManager, threadMemory, errorReport );
	memoryManager->removeReference();

	// We now initialize the stack area to 100k (fast temporary memory to be used by the engine).
	int stackSize = 0x100000;
	stackBuffer = hkAllocate<char>( stackSize, HK_MEMORY_CLASS_BASE);
	hkThreadMemory::getInstance().setStackArea( stackBuffer, stackSize);

	//
	// Initialize the multi-threading classes, hkJobQueue, and hkJobThreadPool
	//

	// They can be used for all Havok multithreading tasks. In this exmaple we only show how to use
	// them for physics, but you can reference other multithreading demos in the demo framework
	// to see how to multithread other products. The model of usage is the same as for physics.
	// The hkThreadpool has a specified number of threads that can run Havok jobs.  These can work
	// alongside the main thread to perform any Havok multi-threadable computations.
	// The model for running Havok tasks in Spus and in auxilary threads is identical.  It is encapsulated in the
	// class hkJobThreadPool.  On PLAYSTATION(R)3 we initialize the SPU version of this class, which is simply a SPURS taskset.
	// On other multi-threaded platforms we initialize the CPU version of this class, hkCpuJobThreadPool, which creates a pool of threads
	// that run in exactly the same way.  On the PLAYSTATION(R)3 we could also create a hkCpuJobThreadPool.  However, it is only
	// necessary (and advisable) to use one Havok PPU thread for maximum efficiency. In this case we simply use this main thread
	// for this purpose, and so do not create a hkCpuJobThreadPool.

	// We can cap the number of threads used - here we use the maximum for whatever multithreaded platform we are running on. This variable is
	// set in the following code sections.
		
	// Get the number of physical threads available on the system
	hkHardwareInfo hwInfo;
	hkGetHardwareInfo(hwInfo);
	totalNumThreadsUsed = hwInfo.m_numThreads;

	// We use one less than this for our thread pool, because we must also use this thread for our simulation
	hkCpuJobThreadPoolCinfo threadPoolCinfo;
	threadPoolCinfo.m_numThreads = totalNumThreadsUsed - 1;

	// This line enables timers collection, by allocating 200 Kb per thread.  If you leave this at its default (0),
	// timer collection will not be enabled.
	threadPoolCinfo.m_timerBufferPerThreadAllocation = 200000;
	threadPool = new hkCpuJobThreadPool( threadPoolCinfo );

	// We also need to create a Job queue. This job queue will be used by all Havok modules to run multithreaded work.
	// Here we only use it for physics.
	hkJobQueueCinfo info;
	info.m_jobQueueHwSetup.m_numCpuThreads = totalNumThreadsUsed;
	jobQueue = new hkJobQueue(info);

	//
	// Enable monitors for this thread.
	//

	// Monitors have been enabled for thread pool threads already (see above comment).
	hkMonitorStream::getInstance().resize(200000);

	//
	// <PHYSICS-ONLY>: Create the physics world.
	// At this point you would initialize any other Havok modules you are using.
	//
	{
		// The world cinfo contains global simulation parameters, including gravity, solver settings etc.
		hkpWorldCinfo worldInfo;

		// Set the simulation type of the world to multi-threaded.
		worldInfo.m_simulationType = hkpWorldCinfo::SIMULATION_TYPE_MULTITHREADED;

		// Flag objects that fall "out of the world" to be automatically removed - just necessary for this physics scene
		worldInfo.m_broadPhaseBorderBehaviour = hkpWorldCinfo::BROADPHASE_BORDER_REMOVE_ENTITY;

		physicsWorld = new hkpWorld(worldInfo);

		// Disable deactivation, so that you can view timers in the VDB. This should not be done in your game.
		physicsWorld->m_wantDeactivation = false;


		// When the simulation type is SIMULATION_TYPE_MULTITHREADED, in the debug build, the sdk performs checks
		// to make sure only one thread is modifying the world at once to prevent multithreaded bugs. Each thread
		// must call markForRead / markForWrite before it modifies the world to enable these checks.
		physicsWorld->markForWrite();


		// Register all collision agents, even though only box - box will be used in this particular example.
		// It's important to register collision agents before adding any entities to the world.
		hkpAgentRegisterUtil::registerAllAgents( physicsWorld->getCollisionDispatcher() );

		// We need to register all modules we will be running multi-threaded with the job queue
		physicsWorld->registerWithJobQueue( jobQueue );

		// Create all the physics rigid bodies
		setupPhysics( physicsWorld );
	}

	//
	// Initialize the VDB
	//

	// <PHYSICS-ONLY>: Register physics specific visual debugger processes
	// By default the VDB will show debug points and lines, however some products such as physics and cloth have additional viewers
	// that can show geometries etc and can be enabled and disabled by the VDB app.
	{
		contexts = new hkArray<hkProcessContext*>();


		// The visual debugger so we can connect remotely to the simulation
		// The context must exist beyond the use of the VDB instance, and you can make
		// whatever contexts you like for your own viewer types.
		context = new hkpPhysicsContext();
		hkpPhysicsContext::registerAllPhysicsProcesses(); // all the physics viewers
		context->addWorld(physicsWorld); // add the physics world so the viewers can see it
		contexts->pushBack(context);

		// Now we have finished modifying the world, release our write marker.
		physicsWorld->unmarkForWrite();
	}

	vdb = new hkVisualDebugger(*contexts);
	vdb->serve();
}

HavocWorldUpdater::~HavocWorldUpdater(void)
{
	//
	// Clean up physics and graphics
	//

	// <PHYSICS-ONLY>: cleanup physics
	{
		physicsWorld->markForWrite();
		physicsWorld->removeReference();
	}
	vdb->removeReference();

	// Contexts are not reference counted at the base class level by the VDB as
	// they are just interfaces really. So only delete the context after you have
	// finished using the VDB.
	context->removeReference();

	delete jobQueue;

	//
	// Clean up the thread pool
	//
	threadPool->removeReference();

	// Deallocate stack area
	threadMemory->setStackArea(0, 0);
	hkDeallocate(stackBuffer);

	threadMemory->removeReference();

	delete contexts;

	// Quit base system
	hkBaseSystem::quit();
}

bool HavocWorldUpdater::frameStarted (const Ogre::FrameEvent &evt) {
	if ( evt.timeSinceLastEvent == 0 )
		return true;


	// <PHYSICS-ONLY>:
	// Step the physics world. This single call steps using this thread and all threads
	// in the threadPool. For other products you add jobs, call process all jobs and wait for completion.
	// See the multithreading chapter in the user guide for details
	{
		physicsWorld->stepMultithreaded( jobQueue, threadPool, evt.timeSinceLastEvent );
	}

	// Step the visual debugger. We first synchronize the timer data
	context->syncTimers( threadPool );
	vdb->step();

	// Clear accumulated timer data in this thread and all slave threads
	hkMonitorStream::getInstance().reset();
	threadPool->clearTimerData();

	return true;
}


void HavocWorldUpdater::createBrickWall( hkpWorld* world, int height, int length, const hkVector4& position, hkReal gapWidth, hkpConvexShape* box, hkVector4Parameter halfExtents )
{
	hkVector4 posx = position;
	// do a raycast to place the wall
	{
		hkpWorldRayCastInput ray;
		ray.m_from = posx;
		ray.m_to = posx;

		ray.m_from(1) += 20.0f;
		ray.m_to(1)   -= 20.0f;

		hkpWorldRayCastOutput result;
		world->castRay( ray, result );
		posx.setInterpolate4( ray.m_from, ray.m_to, result.m_hitFraction );
	}
	// move the start point
	posx(0) -= ( gapWidth + 2.0f * halfExtents(0) ) * length * 0.5f;
	posx(1) -= halfExtents(1) + box->getRadius();

	hkArray<hkpEntity*> entitiesToAdd;

	for ( int x = 0; x < length; x ++ )		// along the ground
	{
		hkVector4 pos = posx;
		for( int ii = 0; ii < height; ii++ )
		{
			pos(1) += (halfExtents(1) + box->getRadius())* 2.0f;

			hkpRigidBodyCinfo boxInfo;
			boxInfo.m_mass = 10.0f;
			hkpMassProperties massProperties;
			hkpInertiaTensorComputer::computeBoxVolumeMassProperties(halfExtents, boxInfo.m_mass, massProperties);

			boxInfo.m_mass = massProperties.m_mass;
			boxInfo.m_centerOfMass = massProperties.m_centerOfMass;
			boxInfo.m_inertiaTensor = massProperties.m_inertiaTensor;
			boxInfo.m_solverDeactivation = boxInfo.SOLVER_DEACTIVATION_MEDIUM;
			boxInfo.m_shape = box;
			//boxInfo.m_qualityType = HK_COLLIDABLE_QUALITY_DEBRIS;
			boxInfo.m_restitution = 0.0f;

			boxInfo.m_motionType = hkpMotion::MOTION_BOX_INERTIA;

			{
				boxInfo.m_position = pos;
				hkpRigidBody* boxRigidBody = new hkpRigidBody(boxInfo);
				world->addEntity( boxRigidBody );
				boxRigidBody->removeReference();
			}

			pos(1) += (halfExtents(1) + box->getRadius())* 2.0f;
			pos(0) += halfExtents(0) * 0.6f;
			{
				boxInfo.m_position = pos;
				hkpRigidBody* boxRigidBody = new hkpRigidBody(boxInfo);
				entitiesToAdd.pushBack(boxRigidBody);
			}
			pos(0) -= halfExtents(0) * 0.6f;
		}
		posx(0) += halfExtents(0)* 2.0f + gapWidth;
	}
	world->addEntityBatch( entitiesToAdd.begin(), entitiesToAdd.getSize());

	for (int i=0; i < entitiesToAdd.getSize(); i++){ entitiesToAdd[i]->removeReference(); }
}

void HavocWorldUpdater::setupPhysics(hkpWorld* physicsWorld)
{
	//
	//  Create the ground box
	//
	{
		hkVector4 groundRadii( 70.0f, 2.0f, 140.0f );
		hkpConvexShape* shape = new hkpBoxShape( groundRadii , 0 );

		hkpRigidBodyCinfo ci;

		ci.m_shape = shape;
		ci.m_motionType = hkpMotion::MOTION_FIXED;
		ci.m_position = hkVector4( 0.0f, -2.0f, 0.0f );
		ci.m_qualityType = HK_COLLIDABLE_QUALITY_FIXED;

		physicsWorld->addEntity( new hkpRigidBody( ci ) )->removeReference();
		shape->removeReference();
	}

	hkVector4 groundPos( 0.0f, 0.0f, 0.0f );
	hkVector4 posy = groundPos;

	//
	// Create the walls
	//

	int wallHeight = 8;
	int wallWidth  = 8;
	int numWalls = 6;
	hkVector4 boxSize( 1.0f, 0.5f, 0.5f);
	hkpBoxShape* box = new hkpBoxShape( boxSize , 0 );
	box->setRadius( 0.0f );

	hkReal deltaZ = 25.0f;
	posy(2) = -deltaZ * numWalls * 0.5f;

	for ( int y = 0; y < numWalls; y ++ )			// first wall
	{
		createBrickWall( physicsWorld, wallHeight, wallWidth, posy, 0.2f, box, boxSize );
		posy(2) += deltaZ;
	}
	box->removeReference();

	//
	// Create a ball moving towards the walls
	//

	const hkReal radius = 1.5f;
	const hkReal sphereMass = 150.0f;

	hkVector4 relPos( 0.0f,radius + 0.0f, 50.0f );

	hkpRigidBodyCinfo info;
	hkpMassProperties massProperties;
	hkpInertiaTensorComputer::computeSphereVolumeMassProperties(radius, sphereMass, massProperties);

	info.m_mass = massProperties.m_mass;
	info.m_centerOfMass  = massProperties.m_centerOfMass;
	info.m_inertiaTensor = massProperties.m_inertiaTensor;
	info.m_shape = new hkpSphereShape( radius );
	info.m_position.setAdd4(posy, relPos );
	info.m_motionType  = hkpMotion::MOTION_BOX_INERTIA;

	info.m_qualityType = HK_COLLIDABLE_QUALITY_BULLET;


	hkpRigidBody* sphereRigidBody = new hkpRigidBody( info );
	g_ball = sphereRigidBody;


	physicsWorld->addEntity( sphereRigidBody );
	sphereRigidBody->removeReference();
	info.m_shape->removeReference();

	hkVector4 vel(  0.0f,4.9f, -100.0f );
	sphereRigidBody->setLinearVelocity( vel );
}
