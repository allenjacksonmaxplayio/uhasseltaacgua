#include "NetworkCommand.h"
#include <boost/thread.hpp>

namespace HovUni {

NetworkCommand::NetworkCommand(NetworkCommandType type) : NetworkEvent<NetworkCommandType>(type) {

}

NetworkCommand::~NetworkCommand() {

}

}