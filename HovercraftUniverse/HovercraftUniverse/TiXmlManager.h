#ifndef TIXMLMANAGER_H
#define TIXMLMANAGER_H

#include <OgreResourceManager.h>
#include "TiXmlResource.h"

namespace HovUni {

/**
 * Resource manager for xml files
 */
class TiXmlManager : public Ogre::ResourceManager
{
private:

	static TiXmlManager * ms_Singleton;

protected:

    // must implement this from ResourceManager's interface
    Ogre::Resource *createImpl(const Ogre::String &name, Ogre::ResourceHandle handle, 
        const Ogre::String &group, bool isManual, Ogre::ManualResourceLoader *loader, 
        const Ogre::NameValuePairList *createParams);

public:

    TiXmlManager();

    virtual ~TiXmlManager();

    virtual TiXmlPtr load(const Ogre::String &name, const Ogre::String &group);

    static TiXmlManager &getSingleton();
    static TiXmlManager *getSingletonPtr();
};

}

#endif

