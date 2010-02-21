#ifndef OVERLAYNOTACTIVATEDEXCEPTION_H
#define OVERLAYNOTACTIVATEDEXCEPTION_H

#include <exception>

namespace HovUni {
	class OverlayNotActivatedException : public std::exception {
		virtual const char* what() const throw() {
			return "The overlay is not active at the moment";
		}
	};
}

#endif //OVERLAYNOTACTIVATEDEXCEPTION_H