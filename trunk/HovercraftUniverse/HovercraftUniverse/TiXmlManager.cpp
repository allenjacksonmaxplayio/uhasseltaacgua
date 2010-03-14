#include "TiXmlManager.h"


namespace HovUni {

TiXmlManager * TiXmlManager::ms_Singleton = 0;

TiXmlManager *TiXmlManager::getSingletonPtr()
{
    return ms_Singleton;
}

TiXmlManager &TiXmlManager::getSingleton()
{  
    assert(ms_Singleton);  
    return(*ms_Singleton);
}

TiXmlManager::TiXmlManager()
{
    mResourceType = "XML";

    // low, because it will likely reference other resources
    mLoadOrder = 30.0f;

    // this is how we register the ResourceManager with OGRE
    Ogre::ResourceGroupManager::getSingleton()._registerResourceManager(mResourceType, this);
}

TiXmlManager::~TiXmlManager()
{
    // and this is how we unregister it
    Ogre::ResourceGroupManager::getSingleton()._unregisterResourceManager(mResourceType);
}

TiXmlPtr TiXmlManager::load(const Ogre::String &name, const Ogre::String &group)
{
    TiXmlPtr textf = getByName(name);

    if (textf.isNull())
        textf = create(name, group);

    textf->load();
    return textf;
}

Ogre::Resource * TiXmlManager::createImpl(const Ogre::String &name, Ogre::ResourceHandle handle, 
                                            const Ogre::String &group, bool isManual, Ogre::ManualResourceLoader *loader, 
                                            const Ogre::NameValuePairList *createParams)
{
    return new TiXml(this, name, handle, group, isManual, loader);
}


}