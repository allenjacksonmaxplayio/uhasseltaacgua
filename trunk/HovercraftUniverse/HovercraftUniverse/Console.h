#ifndef CONSOLE_H
#define CONSOLE_H

#include "Exception.h"

namespace HovUni {

/**
 * This class can be used to create a console.
 * CIN/CER/COUT will be forwarderd to this console.
 * An application can only have one console!
 */
class Console
{
	Console(void);

	~Console(void);
public:

	/**
	 * Create the console
	 * @param buffered lines
	 */
	static void createConsole( int lines = 500 ) throw(std::exception);

	/**
	 * Destroy the console
	 */
	static void destroyConsole();
};

}

#endif
