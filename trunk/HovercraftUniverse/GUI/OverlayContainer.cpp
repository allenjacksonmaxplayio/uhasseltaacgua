#include "OverlayContainer.h"

namespace HovUni {

	void OverlayContainer::addOverlay(const std::string& name, BasicOverlay * overlay) {
		//Check for duplicates
		if (mOverlays.find(name) == mOverlays.end()) {
			mOverlays[name] = overlay;
		}
	}

	void OverlayContainer::removeOverlay(const std::string& name) {
		// Check if item exists
		if (mOverlays.find(name) != mOverlays.end()) {
			mOverlays.erase(mOverlays.find(name));
		} else {
			// Doesn't Exist
		}
	}

	std::map<std::string, BasicOverlay *>& OverlayContainer::getOverlays() {
		return mOverlays;
	}

}