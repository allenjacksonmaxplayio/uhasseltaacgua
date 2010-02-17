#include "CheckPoint.h"
#include <OgreStringConverter.h>

namespace HovUni {

CheckPoint::CheckPoint( TiXmlElement * data ) throw (ParseException)
{
	TiXmlNode * node;

	//We are loading a CheckPoint!
	if(strcmp(data->Value(),"CheckPoint") != 0){
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

	//Read number
	mNumber = 0;
	node = data->FirstChild("Number");
	if ( node ){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if ( element ){
			mNumber = Ogre::StringConverter::parseInt(Ogre::String(element->GetText()));
		}
	}
}

CheckPoint::~CheckPoint(void)
{
}

}
