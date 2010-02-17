#include "StartPosition.h"
#include <OgreStringConverter.h>

namespace HovUni {

StartPosition::StartPosition( TiXmlElement * data ) throw (ParseException)
{
	TiXmlNode * node;

	//We are loading a Finish!
	if(strcmp(data->Value(),"StartPosition") != 0){
		throw ParseException();
	}	

	//Read number
	mPlayerNumber = 0;
	node = data->FirstChild("PlayerNumber");
	if ( node ){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if ( element ){
			mPlayerNumber = Ogre::StringConverter::parseInt(Ogre::String(element->GetText()));
		}
	}
}

StartPosition::~StartPosition(void)
{
}

}
