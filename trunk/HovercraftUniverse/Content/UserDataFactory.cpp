#include "UserDataFactory.h"
#include "UserDataCallback.h"

namespace HovUni {

//singleton

UserDataFactory* UserDataFactory::ms_Singleton = new UserDataFactory();

UserDataFactory* UserDataFactory::getSingletonPtr(void)
{
    return ms_Singleton;
}

UserDataFactory& UserDataFactory::getSingleton(void)
{
    assert( ms_Singleton );  return ( *ms_Singleton );
}

//code

UserDataFactory::UserDataFactory(void)
{
}

UserDataFactory::~UserDataFactory(void)
{
}

void UserDataFactory::addUserDataCallback( UserDataCallback* callback ){
	mUserDataCallback.push_back(callback);
}

void UserDataFactory::removeUserDataCallback( UserDataCallback* callback ){
	mUserDataCallback.remove(callback);
}

void UserDataFactory::parseUserData(OgreMax::OgreMaxScene* scene) {
	OgreMax::OgreMaxScene::ObjectExtraDataMap& map = scene->GetAllObjectExtraData();
	for ( OgreMax::OgreMaxScene::ObjectExtraDataMap::iterator i = map.begin(); i != map.end(); i++ ){
		//parse XML that describes the user data
		mDocument.Parse(i->second->userData.c_str());
		TiXmlElement * root = mDocument.RootElement();

		//if correct xml, see if user data is known
		if ( root ){
			//START
			if ( strcmp(root->Value(),"Start") == 0 ){
				Start * start = new Start(root);
				start->setMovableObject(i->second->object);
				for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
					(*uc)->onStart(start);
				}
			}
			//STARTPOSITION
			if ( strcmp(root->Value(),"StartPosition") == 0 ){
				StartPosition * startp = new StartPosition(root);
				startp->setMovableObject(i->second->object);
				for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
					(*uc)->onStartPosition(startp);
				}
			}
			//FINISH
			else if ( strcmp(root->Value(),"Finish") == 0 ){
				Finish * finish = new Finish(root);
				finish->setMovableObject(i->second->object);
				for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
					(*uc)->onFinish(finish);
				}
			}
			//CHECKPOINT
			else if ( strcmp(root->Value(),"CheckPoint") == 0 ){
				CheckPoint * checkpoint = new CheckPoint(root);
				checkpoint->setMovableObject(i->second->object);
				for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
					(*uc)->onCheckPoint(checkpoint);
				}
			}
			//ASTEROID
			else if ( strcmp(root->Value(),"Asteroid") == 0 ){
				Asteroid * ast = new Asteroid(root);
				ast->setMovableObject(i->second->object);
				for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
					(*uc)->onAsteroid(ast);
				}
			}
			//HOVERCRAFT
			else if ( strcmp(root->Value(),"Hovercraft") == 0 ){
				Hovercraft * hovercr = new Hovercraft(root);
				hovercr->setMovableObject(i->second->object);
				for ( std::list<UserDataCallback*>::iterator uc = mUserDataCallback.begin(); uc != mUserDataCallback.end(); uc++ ){
					(*uc)->onHoverCraft(hovercr);
				}
			}
		}

		//clear xml
		mDocument.Clear();
	}
}

}

