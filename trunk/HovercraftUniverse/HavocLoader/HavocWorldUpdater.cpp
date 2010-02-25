#include "HavocWorldUpdater.h"

#include "SimpleGravityPhantom.h"

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

void HavocWorldUpdater::loadWorld( const char* path )
{
	hkIstream infile( path );
	HK_ASSERT( 0x215d080c, infile.isOk() );

	mPhysicsData = hkpHavokSnapshot::load( infile.getStreamReader(), &mLoadedData );

	HK_ASSERT( 0, mPhysicsData != HK_NULL );

	//Make Multi Threaded
	hkpWorldCinfo worldInfo;

	// Set the simulation type of the world to multi-threaded.
	worldInfo.m_simulationType = hkpWorldCinfo::SIMULATION_TYPE_MULTITHREADED;

	// Flag objects that fall "out of the world" to be automatically removed - just necessary for this physics scene
	worldInfo.m_broadPhaseBorderBehaviour = hkpWorldCinfo::BROADPHASE_BORDER_REMOVE_ENTITY;

	mPhysicsData->setWorldCinfo(&worldInfo);

	// Ensure non-multithreaded simulation for non-multithreaded platforms

	mPhysicsWorld = mPhysicsData->createWorld();

	mPhysicsWorld->markForWrite();

	mPhysicsWorld->setGravity( hkVector4::getZero() );

	// Set up the collision filter
	{
		hkpGroupFilter* filter = new hkpGroupFilter();
		filter->disableCollisionsBetween(1, 1);
		mPhysicsWorld->setCollisionFilter(filter);
		filter->removeReference();
	}

	// Go through all loaded rigid bodies
	for( int i = 0; i < mPhysicsData->getPhysicsSystems().getSize(); i++ )
	{
		const hkArray<hkpRigidBody*>& bodies = mPhysicsData->getPhysicsSystems()[i]->getRigidBodies();
		for( int j = 0; j < bodies.getSize(); j++ )
		{
			hkString rbName( bodies[j]->getName() );

			// If the rb is a planet (name is "planet*")
			if( rbName.beginsWith( "planet" ) )
			{
				// If the body is a representation of a gravitational field (name: "*GravField"),
				//  remove it from the simulation.
				if( rbName.endsWith( "GravField" ) )
				{
					mPhysicsWorld->removeEntity( bodies[j] );
				}
				// Otherwise, it's actually a planet.
				else
				{
					hkAabb currentAabb;
					const hkpCollidable* hullCollidable = HK_NULL;

					// Find the planet's gravity field
					hkpRigidBody* planetRigidBody = bodies[j];
					hkString gravFieldRbName;
					gravFieldRbName.printf( "%sGravField", rbName.cString() );
					hkpRigidBody* gravFieldRigidBody = mPhysicsData->findRigidBodyByName( gravFieldRbName.cString() );

					// If there's a GravField rigid body, then grab its collidable to be used for gravity calculation.
					if( gravFieldRigidBody )
					{
						hullCollidable = gravFieldRigidBody->getCollidable();
						gravFieldRigidBody->getCollidable()->getShape()->getAabb( gravFieldRigidBody->getTransform(), 0.0f, currentAabb );
					}
					else
					{
						planetRigidBody->getCollidable()->getShape()->getAabb( planetRigidBody->getTransform(), 0.0f, currentAabb );
					}

					// Scale up the planet's gravity field's AABB so it goes beyond the planet
					hkVector4 extents;
					extents.setSub4( currentAabb.m_max, currentAabb.m_min );
					hkInt32 majorAxis = extents.getMajorAxis();
					hkReal maxExtent = extents( majorAxis );
					maxExtent *= 0.4f;

					// Scale the AABB's extents
					hkVector4 extension;
					extension.setAll( maxExtent );
					currentAabb.m_max.add4( extension );
					currentAabb.m_min.sub4( extension );

					// Attach a gravity phantom to the planet so it can catch objects which come close
					SimpleGravityPhantom* gravityAabbPhantom = new SimpleGravityPhantom( planetRigidBody, currentAabb, hullCollidable );
					mPhysicsWorld->addPhantom( gravityAabbPhantom );
					gravityAabbPhantom->removeReference();

					/*
					TODO
					// Add a tracking action to the phantom so it follows the planet. This allows support for non-fixed motion type planets
					if (planetRigidBody->getMotion()->getType() != hkpMotion::MOTION_FIXED)
					{
						PhantomTrackAction* trackAction = new PhantomTrackAction( planetRigidBody, gravityAabbPhantom );
						world->addAction( trackAction );
						trackAction->removeReference();
					}*/
				}
			}
			else if ( rbName.beginsWith( "StartPos" ) ){
				//keep the position and orientation
				mStartPos = bodies[j]->getPosition();
				mStartRotation = bodies[j]->getRotation();

				//remove it from simulation
				mPhysicsWorld->removeEntity( bodies[j] );
			}

			// Update collision filter so that needless CollColl3 agents are not created.
			// For example, turrets  and geometry marked as "static" (such as the swing)
			//  should never collide with a planet, nor each other.
			if(  ( rbName.beginsWith( "planet" ) && !rbName.endsWith( "GravField" ) ) )
			{
				bodies[j]->setCollisionFilterInfo( hkpGroupFilter::calcFilterInfo( 1 ) );

				// Destroy or create agents (according to new quality type). This also removes Toi events.
				mPhysicsWorld->updateCollisionFilterOnEntity(bodies[j], HK_UPDATE_FILTER_ON_ENTITY_FULL_CHECK, HK_UPDATE_COLLECTION_FILTER_PROCESS_SHAPE_COLLECTIONS);
			}
		}
	}

	mPhysicsWorld->unmarkForWrite();
}

HavocWorldUpdater::HavocWorldUpdater( const char * file )
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
		loadWorld(file);

		hkpMultithreadConfig config;
		mPhysicsWorld->getMultithreadConfig(config);

		// Disable deactivation, so that you can view timers in the VDB. This should not be done in your game.
		mPhysicsWorld->m_wantDeactivation = false;
	}

	// When the simulation type is SIMULATION_TYPE_MULTITHREADED, in the debug build, the sdk performs checks
	// to make sure only one thread is modifying the world at once to prevent multithreaded bugs. Each thread
	// must call markForRead / markForWrite before it modifies the world to enable these checks.
	mPhysicsWorld->markForWrite();

	// We need to register all modules we will be running multi-threaded with the job queue
	mPhysicsWorld->registerWithJobQueue( jobQueue );

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
		context->addWorld(mPhysicsWorld); // add the physics world so the viewers can see it
		contexts->pushBack(context);
	}

	// Now we have finished modifying the world, release our write marker.
	mPhysicsWorld->unmarkForWrite();

	vdb = new hkVisualDebugger(*contexts);
	vdb->serve();
}

HavocWorldUpdater::~HavocWorldUpdater(void)
{
	// <PHYSICS-ONLY>: cleanup physics
	{
		mPhysicsWorld->markForWrite();
		mPhysicsWorld->removeReference();
	}

	mPhysicsData->removeReference();
	mLoadedData->removeReference();

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


void HavocWorldUpdater::update ( hkReal timestep ) {

	// <PHYSICS-ONLY>:
	// Step the physics world. This single call steps using this thread and all threads
	// in the threadPool. For other products you add jobs, call process all jobs and wait for completion.
	// See the multithreading chapter in the user guide for details
	{
		mPhysicsWorld->stepMultithreaded( jobQueue, threadPool, timestep );
	}

	// Step the visual debugger. We first synchronize the timer data
	context->syncTimers( threadPool );
	vdb->step();

	// Clear accumulated timer data in this thread and all slave threads
	hkMonitorStream::getInstance().reset();
	threadPool->clearTimerData();
}
