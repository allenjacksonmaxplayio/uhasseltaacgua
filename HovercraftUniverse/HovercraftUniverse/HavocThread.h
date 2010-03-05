#ifndef HAVOCTHREAD_H
#define HAVOCTHREAD_H

#include "windows.h"

namespace HovUni {

DWORD WINAPI runHavoc( LPVOID lpParam );

class HavocThread {

private:

	friend DWORD WINAPI runHavoc( LPVOID lpParam );

	static bool run;

	static HANDLE handle;

	static bool havocdebug;
	static STARTUPINFO si;
    static PROCESS_INFORMATION pi;

public:

	static void StartHavocThread();

	static void StopHavocThread();

};

}

#endif