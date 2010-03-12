#include "Boost.h"
#include <OgreStringConverter.h>

namespace HovUni {

Boost::Boost(const Ogre::String& name, const Ogre::String& category, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float processInterval):
	Entity(name,category,false,position,orientation,processInterval)
{
}

void Boost::load(TiXmlElement * data) throw (ParseException)
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

Boost::~Boost(void)
{
}

}
