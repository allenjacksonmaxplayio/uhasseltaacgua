#include "AsteroidData.h"
#include <OgreStringConverter.h>

namespace HovUni {

AsteroidData::AsteroidData( TiXmlElement * data ) throw (ParseException)
{
	TiXmlNode * node;

	//We are loading a CheckPoint!
	if(strcmp(data->Value(),"Asteroid") != 0){
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

	//Read gravity
	mGravity = 0;
	node = data->FirstChild("Gravity");
	if ( node ){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if ( element ){
			mGravity = Ogre::StringConverter::parseReal(Ogre::String(element->GetText()));
		}
	}

	//Read type
	mAsteroidType = UNKNOWN;
	node = data->FirstChild("AsteroidType");
	if ( node ){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if ( element ){
			mAsteroidType = (AsteroidType) Ogre::StringConverter::parseInt(Ogre::String(element->GetText()));
		}
	}
}

AsteroidData::~AsteroidData(void)
{
}

}
