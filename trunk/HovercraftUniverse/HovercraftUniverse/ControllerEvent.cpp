#include "ControllerEvent.h"

namespace HovUni {

ControllerEvent::ControllerEvent(ControllerEventType type) : NetworkEvent<ControllerEventType>(type) {

}

ControllerEvent::~ControllerEvent() {

}

void ControllerEvent::write(ZCom_BitStream* stream) const {

}

void ControllerEvent::read(ZCom_BitStream* stream) {

}

}
