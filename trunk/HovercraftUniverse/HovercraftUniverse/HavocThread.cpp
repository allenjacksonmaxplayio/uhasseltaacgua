#include "HavocThread.h"
#include "Havoc.h"

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
	// A stopwatch for waiting until the real time has passed
	hkStopwatch stopWatch;
	stopWatch.start();
	hkReal lastTime = stopWatch.getElapsedSeconds();

	Havoc::getSingleton().loadSceneFile(".\\..\\..\\..\\art\\models\\SimpleTrack.scene");
	Havoc::getSingleton().addCharacter("NAME1","BLA",0);
	Havoc::getSingleton().addCharacter("NAME2","BLA",1);

	while ( HavocThread::run ) {
		Havoc::getSingleton().step();

		

		// Pause until the actual time has passed
		while (stopWatch.getElapsedSeconds() < lastTime + Havoc::getSingleton().getTimeStep());
			lastTime += Havoc::getSingleton().getTimeStep();			
	}

	return 0;
}

}