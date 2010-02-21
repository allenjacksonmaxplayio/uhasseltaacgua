#ifndef OVERLAYCONTAINER_H
#define OVERLAYCONTAINER_H

#include "BasicOverlay.h"
#include <string>

namespace HovUni{
	class OverlayContainer {
		friend class GUIManager;

		private:
			std::map<std::string, BasicOverlay *> mOverlays;

		public:
			void addOverlay(const std::string& name, BasicOverlay * overlay);
			void removeOverlay(const std::string& name);

		private:
			std::map<std::string, BasicOverlay *>& getOverlays();
	};
}

#endif //OVERLAYCONTAINER_H