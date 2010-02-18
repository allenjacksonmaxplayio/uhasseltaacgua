#ifndef UNINITIALISEDEXCEPTION_H
#define UNINITIALISEDEXCEPTION_H

#include <exception>

namespace HovUni {
	class UninitialisedException : public std::exception {
		virtual const char* what() const throw() {
			return "Object was not initialised";
		}
	};
}

#endif //UNINITIALISEDEXCEPTION_H