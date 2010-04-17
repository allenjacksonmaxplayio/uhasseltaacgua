#include "Countdown.h"
#include "Exception.h"

namespace HovUni {
	Countdown::Countdown(const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder) 
			: BasicOverlay(name, fileName, width, height, position, zOrder), mStarted(false) {
		this->setBParameter(BasicOverlay::ALPHAHACK, true);
	}

	void Countdown::start(long milliseconds) {
		mStarted = true;
		mTime = milliseconds % 9000;

		try {
			this->callFunction("start", Hikari::Args(mTime));
		} catch (OverlayNotActivatedException) {
			//Ignore
		}
	}

	void Countdown::resync(long milliseconds) {
		if (mStarted) {
			try {
				this->callFunction("resync", Hikari::Args(milliseconds % 9000));
			} catch (OverlayNotActivatedException) {
				mTime = milliseconds % 9000;
			}
		}
	}

	void Countdown::customActionAfterActivate() {
		if (mStarted) {
			start(mTime);
		}
	}
}