#ifndef ABSTRACTHAVOCWORLD_H
#define ABSTRACTHAVOCWORLD_H

// Math and base include
#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Memory/hkThreadMemory.h>
#include <Common/Base/Memory/Memory/Pool/hkPoolMemory.h>

// World representation
#include <Physics/Utilities/Serialize/hkpPhysicsData.h>
#include <Physics/Dynamics/World/hkpWorld.h>	
#include <Common/Serialize/Packfile/hkPackfileReader.h>

// Visual Debugger includes
#include <Common/Visualize/hkVisualDebugger.h>
#include <Physics/Utilities/VisualDebugger/hkpPhysicsContext.h>	

namespace HovUni {

/**
 * Abstract class which handles a lot of basic functionality for a multithreaded havoc program
 */
class AbstractHavocWorld
{
private:

	// Visual Debugger
	hkVisualDebugger* vdb;

	hkpPhysicsContext* context;

	hkArray<hkProcessContext*> * contexts;

	//The real deal
	hkJobQueue* jobQueue;

	int totalNumThreadsUsed;

	hkJobThreadPool* threadPool;

	char* stackBuffer;

	hkPoolMemory* memoryManager;

	hkThreadMemory* threadMemory;

protected:

	/**
	 * A flag that shows if a world is loaded
	 */
	bool mIsLoaded;

	/**
	 * The world used in simulation
	 */
	hkpWorld* mPhysicsWorld;

	/**
	 * The world in memory as loaded from file
	 */
	hkPackfileReader::AllocatedData* mLoadedData;
	hkpPhysicsData* mPhysicsData;

public:

	/**
	 * Constructor
	 */
	AbstractHavocWorld(void);

	/**
	 * Destructor
	 */
	~AbstractHavocWorld(void);

	/**
	 * Load a hkv file
	 * This will fill the mPhysicsWorld, mLoadedData and mPhysicsData
	 * It will also set the loaded flag
	 * @param filanem
	 */
	virtual void load ( const char * filename );

	/**
	 * Unload the world, removing everything from memory and setting is loaded flag to false
	 */
	virtual void unload ();

	/**
	 * Check the loaded flag
	 * @return true if world is loaded, false if not
	 */
	inline bool isLoaded() const {
		return mIsLoaded;
	}
	
	/**
	 * Update the world
	 * @param timestep since previous update
	 * @return false if not loaded, true otherwise
	 */
	bool update( hkReal timestep );
};

}

#endif
