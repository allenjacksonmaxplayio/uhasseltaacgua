#include "Portal.h"
#include <OgreStringConverter.h>

namespace HovUni {

Portal::Portal(TiXmlElement * data)
{
	TiXmlNode * node;
	
	//We are loading a Portal!
	assert(strcmp(data->Value(),"Portal") == 0);	

	//Read name
	mName = "No name";
	node = data->FirstChild("Name");
	if ( node ){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if ( element ){
			mName = Ogre::String(element->GetText());
		}
	}

	//Read Start
	node = data->FirstChild("Start");
	if ( node ){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if ( element ){
			Ogre::String value = Ogre::String(element->GetText());
			Ogre::vector<Ogre::String>::type split = Ogre::StringUtil::split(value,",");
			assert(split.size()==3);
			for ( int i = 0; i < 3; i++ ){
				mStart[i] = Ogre::StringConverter::parseReal(split[i]);
			}			
		}
	}

	//Read End
	node = data->FirstChild("End");
	if ( node ){
		TiXmlElement* element = dynamic_cast<TiXmlElement*>(node);
		if ( element ){
			Ogre::String value = Ogre::String(element->GetText());
			Ogre::vector<Ogre::String>::type split = Ogre::StringUtil::split(value,",");
			assert(split.size()==3);
			for ( int i = 0; i < 3; i++ ){
				mEnd[i] = Ogre::StringConverter::parseReal(split[i]);
			}			
		}
	}
}

Portal::~Portal(void)
{
}

}
