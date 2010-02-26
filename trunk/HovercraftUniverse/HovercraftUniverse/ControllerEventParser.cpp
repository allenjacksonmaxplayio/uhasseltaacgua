#include "ControllerEventParser.h"
#include "BasicEntityEvent.h"

namespace HovUni {

ControllerEventParser::~ControllerEventParser() {

}

ControllerEvent* ControllerEventParser::parse(ZCom_BitStream* stream) {
	ControllerEventType type = ControllerEvent::readType(stream);

	switch (type) {
		case BasicEntity:
			return BasicEntityEvent::parse(stream);
			break;
		default:
			// TODO exception
			return new BasicEntityEvent(Ogre::Vector3(0.0, 0.0, 0.0), Ogre::Vector3(0.0, 0.0, 0.0));
			break;
	}

}

}
