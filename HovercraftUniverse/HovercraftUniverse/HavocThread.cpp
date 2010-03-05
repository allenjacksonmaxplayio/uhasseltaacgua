#include "HavocThread.h"
#include "HoverCraftUniverseWorld.h"

namespace HovUni {

bool HavocThread::run = false;
bool HavocThread::havocdebug = false;

STARTUPINFO HavocThread::si;
PROCESS_INFORMATION HavocThread::pi;
HANDLE HavocThread::handle;


void HavocThread::StopHavocThread(){
	if ( HavocThread::run = true ){
		HavocThread::run = false;
		WaitForSingleObject(HavocThread::handle,INFINITE);
	}

	if ( HavocThread::havocdebug ){
		WaitForSingleObject( HavocThread::pi.hProcess, INFINITE );

		// Close process and thread handles. 
		CloseHandle( HavocThread::pi.hProcess );
		CloseHandle( HavocThread::pi.hThread );

		HavocThread::havocdebug = false;
	}
}

void HavocThread::StartHavocThread(){

    ZeroMemory( &si, sizeof(HavocThread::si) );
    HavocThread::si.cb = sizeof(HavocThread::si);
    ZeroMemory( &HavocThread::pi, sizeof(HavocThread::pi) );
	
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
			&HavocThread::si,            // Pointer to STARTUPINFO structure
			&HavocThread::pi )           // Pointer to PROCESS_INFORMATION structure
		) {
			HavocThread::havocdebug = true;
		}

	}

	HavocThread::run = true;
	HavocThread::handle = CreateThread( 
            NULL,			// default security attributes
            0,               // use default stack size  
            runHavoc,       // thread function name
            0,          // argument to thread function 
            0,              // use default creation flags 
            0);   // returns the thread identifier
}

DWORD WINAPI runHavoc( LPVOID lpParam ) {
	//Server means Havoc
	float timestep = 1.0f/120.0f;

	//do havoc sim in background
	HoverCraftUniverseWorld havoc (timestep);
	
	// A stopwatch for waiting until the real time has passed
	hkStopwatch stopWatch;
	stopWatch.start();
	hkReal lastTime = stopWatch.getElapsedSeconds();

	havoc.loadSceneFile(".\\..\\..\\..\\art\\models\\SimpleTrack.scene");

	while ( HavocThread::run ) {
		havoc.update();

		// Pause until the actual time has passed
		while (stopWatch.getElapsedSeconds() < lastTime + timestep);
			lastTime += timestep;			
	}

	return 0;
}

}