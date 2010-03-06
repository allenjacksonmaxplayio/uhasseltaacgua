#include "TrackData.h"
#include <OgreStringConverter.h>

namespace HovUni {

TrackData::TrackData(TiXmlElement * data) throw (ParseException)
{
	TiXmlNode * node;

	//We are loading a CheckPoint!
	if(strcmp(data->Value(),"Track") != 0){
		throw ParseException();
	}

	//Read name
	mName = "No name";
	node = data->FirstChild("Name");
	if ( node ){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if ( element ){
			mName = Ogre::String(element->GetText());
		}
	}

	//Read MinimumPlayers
	mMinimumPlayers = 0;
	node = data->FirstChild("MinimumPlayers");
	if ( node ){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if ( element ){
			mMinimumPlayers = Ogre::StringConverter::parseInt(Ogre::String(element->GetText()));
		}
	}

	//Read MinimumPlayers
	mMaximumPlayers = 0;
	node = data->FirstChild("MaximumPlayers");
	if ( node ){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if ( element ){
			mMaximumPlayers = Ogre::StringConverter::parseInt(Ogre::String(element->GetText()));
		}
	}

	//Read Physics File Name
	mPhysicsFileName = "";
	node = data->FirstChild("PhysicsFileName");
	if ( node ){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if ( element ){
			mPhysicsFileName = Ogre::String(element->GetText());
		}
	}
}

TrackData::~TrackData(void)
{
}

}
