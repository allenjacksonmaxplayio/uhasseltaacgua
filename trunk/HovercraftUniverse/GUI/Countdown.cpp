#include "Countdown.h"
#include "Exception.h"

namespace HovUni {
	Countdown::Countdown(const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder) 
		: BasicOverlay(name, fileName, width, height, position, zOrder), mStarted(false) {

	}

	void Countdown::start() {
		mStarted = true;

		try {
			this->callFunction("start", Hikari::Args());
		} catch (OverlayNotActivatedException) {
			//Ignore
		}
	}

	void Countdown::customActionAfterActivate() {
		if (mStarted) {
			start();
		}
	}
}