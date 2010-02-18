#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <OgreMaxScene.hpp>

namespace HovUni {

class MapLoader
{
private:

	OgreMax::OgreMaxScene mScene;

protected:

	MapLoader(void);

public:

	~MapLoader(void);

	void Load( const Ogre::String& value );
};

}

#endif