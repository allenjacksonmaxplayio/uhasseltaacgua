#include "MessageBox.h"
#include "GUIManager.h"

namespace HovUni {
	MessageBox::MessageBox(const Ogre::String& message, const Ogre::String& name, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder)
		: BasicOverlay(name, "messagebox.swf", width, height, position, zOrder), mMessage(message) {
		this->bind("onOk", Hikari::FlashDelegate(this, &MessageBox::onOk));
	}

	void MessageBox::customActionAfterActivate() {
		//Set the text
		callFunction("setText", Hikari::Args(mMessage));
	}

	Hikari::FlashValue MessageBox::onOk(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		GUIManager::getSingletonPtr()->disableOverlay(this);
		delete this;

		return "success";
	}
}