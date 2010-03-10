#ifndef NETWORKCOMMAND_H_
#define NETWORKCOMMAND_H_

#include "NetworkEvent.h"
#include "NetworkCommandType.h"
#include <OgrePrerequisites.h>

namespace HovUni {

/**
 * This represents a command that can be sent between client and server.
 *
 * @author Olivier Berghmans
 */
class NetworkCommand: public NetworkEvent<NetworkCommandType>
{
public:
	/**
	 * Constructor
	 *
	 * @param type the type of the command
	 */
	NetworkCommand(NetworkCommandType type);

	/**
	 * Destructor
	 */
	~NetworkCommand();
};

}

#endif
