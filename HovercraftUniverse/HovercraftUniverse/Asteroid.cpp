#include "Asteroid.h"
#include "Exception.h"
#include <OgreStringConverter.h>

namespace HovUni {

Asteroid::Asteroid(const Ogre::String& name, const Ogre::String& category, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float processInterval):
		Entity(name,category,false,position,orientation,processInterval) {
	// Empty
}

void Asteroid::load(TiXmlElement * data) {
	TiXmlNode * node;

	// We are loading a CheckPoint!
	if (strcmp(data->Value(),"Asteroid") != 0) {
		THROW(ParseException, "Parsed entity is not an asteroid.");
	}

	// Read name
	mName = "No name";
	node = data->FirstChild("Name");
	if (node) {
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if (element) {
			mName = Ogre::String(element->GetText());
		}
	}

	// Read gravity
	mGravity = 0;
	node = data->FirstChild("Gravity");
	if (node) {
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if (element) {
			mGravity = Ogre::StringConverter::parseReal(Ogre::String(element->GetText()));
		}
	}

	// Read type
	mAsteroidType = UNKNOWN;
	node = data->FirstChild("AsteroidType");
	if (node) {
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if (element) {
			mAsteroidType = (AsteroidType) Ogre::StringConverter::parseInt(Ogre::String(element->GetText()));
		}
	}
}

Asteroid::~Asteroid(void) {
	// Empty
}

}
