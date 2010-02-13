#include "UserDataCallback.h"
#include "UserDataFactory.h"

namespace HovUni {

	UserDataCallback::UserDataCallback( bool reg ){
		if ( reg ){
			UserDataFactory::getSingleton().addUserDataCallback(this);
		}
	}

	UserDataCallback::~UserDataCallback(){
		UserDataFactory::getSingleton().removeUserDataCallback(this);
	}

}