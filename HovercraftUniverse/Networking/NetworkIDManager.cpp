#include "Exception.h"
#include "NetworkIDManager.h"

namespace HovUni {

NetworkIDManager::NetworkIDManager(ZCom_Control* control) : mControl(control) {

}

NetworkIDManager::~NetworkIDManager() {

}

ZCom_ClassID NetworkIDManager::registerClass(const string& className) {
	ZCom_ClassID classID = mControl->ZCom_registerClass(className.c_str());
	mMap.insert(pair<string, ZCom_ClassID>(className,classID));
	return classID;
}


ZCom_ClassID NetworkIDManager::getID(const string& className) const {
	map_type::const_iterator it = mMap.find(className);
	if (it != mMap.end()) {
		return it->second;
	}
	THROW(NetworkException, "No such class name registered");
}

}