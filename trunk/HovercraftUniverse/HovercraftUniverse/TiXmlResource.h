#ifndef TIXMLRESOURCE_H
#define TIXMLRESOURCE_H

#include <OgreResourceManager.h>
#include <tinyxml/tinyxml.h>

namespace HovUni {

/**
 * A class that allows xml files to be loaded using the ogre resource manager.
 * The xml will be stored in a tinyxml node.
 */
class TiXml : public Ogre::Resource
{
private:

	TiXmlDocument mTiXmlDocument;

public:
	TiXml(Ogre::ResourceManager *creator, const Ogre::String &name, 
        Ogre::ResourceHandle handle, const Ogre::String &group, bool isManual = false, 
        Ogre::ManualResourceLoader *loader = 0);

	~TiXml(void);

	/**
	 * Get the TiXmlDocument
	 * @return the TiXmlDocument
	 */
	TiXmlDocument& getTiXmlDocument();

protected:

    // must implement these from the Ogre::Resource interface
    void loadImpl();
    void unloadImpl();
    size_t calculateSize() const;
};

class TiXmlPtr : public Ogre::SharedPtr<TiXml> 
{
public:
    TiXmlPtr();

    explicit TiXmlPtr(TiXml *rep);

    TiXmlPtr(const TiXmlPtr &r);

    TiXmlPtr(const Ogre::ResourcePtr &r);

    /// Operator used to convert a ResourcePtr to a TextFilePtr
    TiXmlPtr& operator=(const Ogre::ResourcePtr& r);
};

}

#endif
