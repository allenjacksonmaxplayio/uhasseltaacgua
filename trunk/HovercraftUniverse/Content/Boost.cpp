#include "Boost.h"
#include <OgreStringConverter.h>

namespace HovUni {

Boost::Boost(TiXmlElement * data) throw (ParseException)
{
	TiXmlNode * node;

	//We are loading a CheckPoint!
	if (strcmp(data->Value(),"Boost") != 0){
		throw ParseException();
	}

	//Read boost
	mBoost = 0.0f;
	node = data->FirstChild("Boost");
	if ( node ){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if ( element ){
			mBoost = Ogre::StringConverter::parseReal(Ogre::String(element->GetText()));
		}
	}
}

Boost::~Boost(void)
{
}

}
