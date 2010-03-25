#include "HavokThread.h"
#include "Havok.h"
#include "CustomOgreMaxScene.h"
#include "Loader.h"

namespace {

	struct LoadParameter {
		HovUni::Loader * loader;
		const char * file;
	};

}

namespace HovUni {

bool HavokThread::run = false;
bool HavokThread::havokdebug = false;

HANDLE HavokThread::startevent;
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

void HavokThread::StartHavokThread( const char * filename, Loader * loader ){

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

	HavokThread::startevent = CreateEvent( 
        NULL,               // default security attributes
        TRUE,               // manual-reset event
        FALSE,              // initial state is nonsignaled
        TEXT("Havoc Start Event")  // object name
        ); 

	LoadParameter params;
	params.file = filename;
	params.loader = loader;

	HavokThread::run = true;
	HavokThread::handle = CreateThread( 
            NULL,			// default security attributes
            0,               // use default stack size  
            runHavok,       // thread function name
            &params,          // argument to thread function 
            0,              // use default creation flags 
            0);   // returns the thread identifier

	//wait untill at least the havoc world is set up
	WaitForSingleObject (HavokThread::startevent,INFINITE);

	//delete creation event
	CloseHandle(HavokThread::startevent);
}

DWORD WINAPI runHavok( LPVOID lpParam ) {

	LoadParameter * params = (LoadParameter*) lpParam;

	HoverCraftUniverseWorld world(1.0f/120.0f);

	Havok::ms_world = &world;

	//load havok world should be done in THIS thread
	CustomOgreMaxScene scene;
	scene.Load(params->file,params->loader);

	//notify that the world has loaded
	SetEvent(HavokThread::startevent);

	// A stopwatch for waiting until the real time has passed
	hkStopwatch stopWatch;
	stopWatch.start();
	hkReal lastTime = stopWatch.getElapsedSeconds();

	while ( HavokThread::run ) {
		world.step();

		// Pause until the actual time has passed
		while (stopWatch.getElapsedSeconds() < lastTime + world.getTimeStep());
			lastTime += world.getTimeStep();			
	}

	return 0;
}

}