#include "NetworkCommand.h"

namespace HovUni {

NetworkCommand::NetworkCommand(NetworkCommandType type) : NetworkEvent<NetworkCommandType>(type) {

}

NetworkCommand::~NetworkCommand() {

}

}