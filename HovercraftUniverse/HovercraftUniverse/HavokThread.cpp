#include "HavokThread.h"
#include "Havok.h"

namespace HovUni {

bool HavokThread::run = false;
bool HavokThread::havokdebug = false;

STARTUPINFO HavokThread::si;
PROCESS_INFORMATION HavokThread::pi;
HANDLE HavokThread::handle;


void HavokThread::StopHavokThread(){
	if ( HavokThread::run = true ){
		HavokThread::run = false;
		WaitForSingleObject(HavokThread::handle,INFINITE);
	}

	if ( HavokThread::havokdebug ){
		WaitForSingleObject( HavokThread::pi.hProcess, INFINITE );

		// Close process and thread handles. 
		CloseHandle( HavokThread::pi.hProcess );
		CloseHandle( HavokThread::pi.hThread );

		HavokThread::havokdebug = false;
	}
}

void HavokThread::StartHavokThread(){

    ZeroMemory( &si, sizeof(HavokThread::si) );
    HavokThread::si.cb = sizeof(HavokThread::si);
    ZeroMemory( &HavokThread::pi, sizeof(HavokThread::pi) );
	
	DWORD fileAttr;
    fileAttr = GetFileAttributes("hkVisualDebugger.exe");
	if (0xFFFFFFFF != fileAttr){

		if (CreateProcess( "hkVisualDebugger.exe",   // No module name (use command line)
			NULL,        // Command line
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			FALSE,          // Set handle inheritance to FALSE
			0,              // No creation flags
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			&HavokThread::si,            // Pointer to STARTUPINFO structure
			&HavokThread::pi )           // Pointer to PROCESS_INFORMATION structure
		) {
			HavokThread::havokdebug = true;
		}

	}

	HavokThread::run = true;
	HavokThread::handle = CreateThread( 
            NULL,			// default security attributes
            0,               // use default stack size  
            runHavok,       // thread function name
            0,          // argument to thread function 
            0,              // use default creation flags 
            0);   // returns the thread identifier
}

DWORD WINAPI runHavok( LPVOID lpParam ) {
	// A stopwatch for waiting until the real time has passed
	hkStopwatch stopWatch;
	stopWatch.start();
	hkReal lastTime = stopWatch.getElapsedSeconds();

	HoverCraftUniverseWorld& world = Havok::getSingleton();

	world.loadSceneFile(".\\..\\..\\..\\art\\models\\SimpleTrack.scene");
	world.addCharacter("NAME1","BLA",0);
	world.addCharacter("NAME2","BLA",1);

	while ( HavokThread::run ) {
		world.step();

		// Pause until the actual time has passed
		while (stopWatch.getElapsedSeconds() < lastTime + world.getTimeStep());
			lastTime += world.getTimeStep();			
	}

	return 0;
}

}