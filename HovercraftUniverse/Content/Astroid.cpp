#include "Astroid.h"
#include <OgreStringConverter.h>

namespace HovUni {

Astroid::Astroid( TiXmlElement * data )
{
	TiXmlNode * node;

	//We are loading a CheckPoint!
	assert(strcmp(data->GetText(),"Astroid") == 0);	

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
	mAstroidType = UNKNOWN;
	node = data->FirstChild("AstroidType");
	if ( node ){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if ( element ){
			mAstroidType = (AstroidType) Ogre::StringConverter::parseInt(Ogre::String(element->GetText()));
		}
	}
}

Astroid::~Astroid(void)
{
}

}
