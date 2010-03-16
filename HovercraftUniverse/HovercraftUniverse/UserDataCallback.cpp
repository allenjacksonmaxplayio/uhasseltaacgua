#include "UserDataCallback.h"
#include "UserDataFactory.h"

namespace HovUni {

	UserDataCallback::UserDataCallback(bool reg){
		if(reg){
			UserDataFactory::getSingleton().addUserDataCallback(this);
		}
	}

	UserDataCallback::~UserDataCallback(){
		UserDataFactory::getSingleton().removeUserDataCallback(this);
	}

	void UserDataCallback::onAsteroid( Asteroid * asteroid) { 
		delete asteroid; 
	}

	void UserDataCallback::onStart(Start * start) { 
		delete start; 
	}

	void UserDataCallback::onStartPosition(StartPosition * startposition) { 
		delete startposition;
	}

	void UserDataCallback::onCheckPoint(CheckPoint * checkpoint) { 
		delete checkpoint;
	}

	void UserDataCallback::onFinish(Finish * finish) { 
		delete finish;
	}

	void UserDataCallback::onHoverCraft(Hovercraft * hovercraft) { 
		delete hovercraft;
	}

	void UserDataCallback::onTrack(Track * track) { 
		delete track; 
	}


	void UserDataCallback::onPortal(Portal * portal) { 
		delete portal; 
	}

	void UserDataCallback::onBoost(SpeedBoost * boost) { 
		delete boost;
	}

	void UserDataCallback::onPowerupSpawn(PowerupSpawn * powerupspawn) {
		delete powerupspawn;
	}

	void UserDataCallback::onResetSpawn(ResetSpawn * spawn) { 
		delete spawn;
	}

}