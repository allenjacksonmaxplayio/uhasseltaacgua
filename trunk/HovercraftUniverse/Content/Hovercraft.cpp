#include "Hovercraft.h"
#include <OgreStringConverter.h>

namespace HovUni {

namespace Content {

Hovercraft::Hovercraft(TiXmlElement * data)
{
	TiXmlNode * node;
	
	//We are loading a Hovercraft!
	assert(strcmp(data->GetText(),"Hovercraft") == 0);	

	//Read name
	mName = "No name";
	node = data->FirstChild("Name");
	if ( node ){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if ( element ){
			mName = Ogre::String(element->GetText());
		}
	}

	//Read Description
	mDescription = "";
	node = data->FirstChild("Description");
	if ( node ){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if ( element ){
			mDescription = Ogre::String(element->GetText());
		}
	}

	//Read Speed
	mSpeed = 0.0f;
	node = data->FirstChild("Speed");
	if ( node ){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if ( element ){
			mSpeed = Ogre::StringConverter::parseReal(Ogre::String(element->GetText()));
		}
	}

	//Read Speed
	mMass = 0.0f;
	node = data->FirstChild("Mass");
	if ( node ){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if ( element ){
			mMass = Ogre::StringConverter::parseReal(Ogre::String(element->GetText()));
		}
	}

	//Read Acceleration
	mAcceleration = 0.0f;
	node = data->FirstChild("Acceleration");
	if ( node ){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if ( element ){
			mAcceleration = Ogre::StringConverter::parseReal(Ogre::String(element->GetText()));
		}
	}
}

Hovercraft::~Hovercraft(void)
{
}

}

}
