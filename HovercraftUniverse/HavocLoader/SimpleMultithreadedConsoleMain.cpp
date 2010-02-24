#include "HavocWorldUpdater.h"


int main( int argc, char * argv [] )
{
		HavocWorldUpdater mHavoc ("test.hkx");

		// A stopwatch for waiting until the real time has passed
		hkStopwatch stopWatch;
		stopWatch.start();
		hkReal lastTime = stopWatch.getElapsedSeconds();

		hkReal timestep = 1.f / 60.f;

		while ( true )
		{
			mHavoc.update(timestep);

			// Pause until the actual time has passed
			while (stopWatch.getElapsedSeconds() < lastTime + timestep);
			lastTime += timestep;
		}

    return 0;
}