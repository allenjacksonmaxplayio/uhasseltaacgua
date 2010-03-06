#include "BoostData.h"
#include <OgreStringConverter.h>

namespace HovUni {

BoostData::BoostData(TiXmlElement * data) throw (ParseException)
{
	TiXmlNode * node;

	//We are loading a Boost!
	if (strcmp(data->Value(),"Boost") != 0){
		throw ParseException();
	}

	//Read BoostData
	mBoost = 0.0f;
	node = data->FirstChild("Boost");
	if ( node ){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if ( element ){
			mBoost = Ogre::StringConverter::parseReal(Ogre::String(element->GetText()));
		}
	}
}

BoostData::~BoostData(void)
{
}

}
