#include "TiXmlResource.h"

namespace HovUni {

TiXml::TiXml(Ogre::ResourceManager *creator, const Ogre::String &name, 
        Ogre::ResourceHandle handle, const Ogre::String &group, bool isManual, 
		Ogre::ManualResourceLoader *loader) :
	Ogre::Resource(creator, name, handle, group, isManual, loader){

		/* If you were storing a pointer to an object, then you would set that pointer to NULL here.
		*/

		/* For consistency with StringInterface, but we don't add any parameters here
		That's because the Resource implementation of StringInterface is to
		list all the options that need to be set before loading, of which 
		we have none as such. Full details can be set through scripts.
		*/
		 createParamDictionary("XML");

	}

TiXml::~TiXml(void) {
}

TiXmlDocument& TiXml::getTiXmlDocument() {
	return mTiXmlDocument;
}

void TiXml::loadImpl(){
	Ogre::FileInfoListPtr file = Ogre::ResourceGroupManager::getSingleton().findResourceFileInfo(mGroup,mName);
	if ( !file->empty() ){
		mTiXmlDocument.LoadFile(file->at(0).filename.c_str());
	}	
}

void TiXml::unloadImpl(){
	mTiXmlDocument.Clear();
}

size_t TiXml::calculateSize() const {
	return 1;
}


////////////////////


TiXmlPtr::TiXmlPtr() : Ogre::SharedPtr<TiXml>() {
}

TiXmlPtr::TiXmlPtr(TiXml *rep) : Ogre::SharedPtr<TiXml>(rep) {
}

TiXmlPtr::TiXmlPtr(const TiXmlPtr &r) : Ogre::SharedPtr<TiXml>(r) {
} 
    
TiXmlPtr::TiXmlPtr(const Ogre::ResourcePtr &r) : Ogre::SharedPtr<TiXml>(){
	if( r.isNull() )
		return;
	// lock & copy other mutex pointer
	OGRE_LOCK_MUTEX(*r.OGRE_AUTO_MUTEX_NAME)
	OGRE_COPY_AUTO_SHARED_MUTEX(r.OGRE_AUTO_MUTEX_NAME)
	pRep = static_cast<TiXml*>(r.getPointer());
	pUseCount = r.useCountPointer();
	useFreeMethod = r.freeMethod();
	if (pUseCount){
		++(*pUseCount);
	}
}

/// Operator used to convert a ResourcePtr to a TextFilePtr
TiXmlPtr& TiXmlPtr::operator=(const Ogre::ResourcePtr& r){
	if(pRep == static_cast<TiXml*>(r.getPointer()))
		return *this;
	release();
	if( r.isNull() )
		return *this; // resource ptr is null, so the call to release above has done all we need to do.
	// lock & copy other mutex pointer
	OGRE_LOCK_MUTEX(*r.OGRE_AUTO_MUTEX_NAME)
	OGRE_COPY_AUTO_SHARED_MUTEX(r.OGRE_AUTO_MUTEX_NAME)
	pRep = static_cast<TiXml*>(r.getPointer());
	pUseCount = r.useCountPointer();
	useFreeMethod = r.freeMethod();
	if (pUseCount){
		++(*pUseCount);
	}
	return *this;
}

}
