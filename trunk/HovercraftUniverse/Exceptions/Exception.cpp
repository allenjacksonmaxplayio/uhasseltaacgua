#include "Exception.h"

#include <sstream>

namespace HovUni {

Exception::	Exception(const std::string& msg) : mMsg(msg), mNested(0), mFilename(0) {

}

Exception::Exception(const std::string& msg, const char* filename, unsigned line) : mMsg(msg), mNested(0), mFilename(filename), mLineNumber(line) {

}

Exception::Exception(const std::string& msg, const Exception& nested) : mMsg(msg), mNested(nested.clone()), mFilename(0) {

}

Exception::Exception(const std::string& msg, const Exception& nested, const char* filename, unsigned line) : mMsg(msg), mNested(nested.clone()), mFilename(filename), mLineNumber(line) {

}
	
Exception::Exception(const Exception& ex) : mMsg(ex.mMsg), mNested(0) {
	mNested = (ex.mNested ? ex.mNested->clone() : 0);
}
	
Exception::~Exception() throw() {

}

Exception& Exception::operator=(const Exception& ex) {
	if (&ex != this) {
		delete mNested;
		mMsg = ex.mMsg;
		mNested = (ex.mNested ? ex.mNested->clone() : 0);
		mFilename = ex.mFilename;
		mLineNumber = ex.mLineNumber;
	}
	return *this;
}

Exception* Exception::clone() const {
	return new Exception(*this);
}

std::string Exception::getMessage() const {
	std::stringstream msg (std::stringstream::in | std::stringstream::out);
	
	msg << className() << " : " << mMsg;
	
	if (mFilename) {
		msg << "[FILE: " << mFilename << " (" << mLineNumber << ")]";
	}

	if (mNested) {
		msg << std::endl << "\t> " << *mNested;
	}

	return mMsg;
}

const Exception* Exception::getNested() const {
	return mNested;
}

const char* Exception::className() const {
	return typeid(*this).name();
}

std::ostream& operator<<(std::ostream& os, const Exception& ex) {
	os << ex.getMessage();
	return os;
}

void Exception::message(const std::string& msg) {
	mMsg = msg;
}

const char* Exception::what() const throw() {
	return getMessage().c_str();
}

/*
 * Exception classes
 */
HOVUNI_EXCEPTION_DEFINITION(NetworkException, Exception)

}