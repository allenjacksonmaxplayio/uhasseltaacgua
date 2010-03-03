#include "Exception.h"

namespace HovUni {

Exception::	Exception(const std::string& msg) : mMsg(msg), mNested(0) {

}

Exception::Exception(const std::string& msg, const Exception& nested) : mMsg(msg), mNested(nested.clone()) {

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
	}
	return *this;
}

Exception* Exception::clone() const {
	return new Exception(*this);
}

std::string Exception::getMessage() const {
	return mMsg;
}

const Exception* Exception::getNested() const {
	return mNested;
}

const char* Exception::className() const {
	return typeid(*this).name();
}

std::ostream& operator<<(std::ostream& os, const Exception& ex) {
	os << ex.mMsg;
	return os;
}

void Exception::message(const std::string& msg) {
	mMsg = msg;
}

const char* Exception::what() const throw() {
	return mMsg.c_str();
}

/*
 * Exception classes
 */
HOVUNI_EXCEPTION_DEFINITION(NetworkException, Exception)

}