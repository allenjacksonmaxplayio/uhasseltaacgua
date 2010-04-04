#include "EntityPropertySystem.h"
#include "Entity.h"

namespace HovUni {

EntityPropertyMap::EntityPropertyMap( Entity * entity ):
	mEntity(entity), mUpdate(0) {
}

EntityPropertyMap::~EntityPropertyMap(){
	
	//destroy all properties
	for ( PropertyMap::iterator i = mMap.begin(); i != mMap.end(); i++ ){
		delete i->second;
		i->second = 0;
	}
	mMap.clear();
}

bool EntityPropertyMap::addProperty( EntityProperty * property  ){	
	property->mEntity = mEntity;
	
	std::pair<PropertyMap::iterator,bool> r = mMap.insert(Property(property->getProperyType(),property));
	
	update();

	return r.second;
}

bool EntityPropertyMap::hasProperty( const Ogre::String& key ) const {
	return mMap.find(key) != mMap.end();
}

EntityProperty * EntityPropertyMap::getProperty( const Ogre::String& key ){
	PropertyMap::iterator i = mMap.find(key);
	if ( i == mMap.end() ){
		return 0;
	}	
	else {
		return i->second;
	}
}

bool EntityPropertyMap::removeProperty ( const Ogre::String& key, bool del ){

	PropertyMap::iterator i = mMap.find(key);
	if ( i == mMap.end() ){
		return false;
	}	
	else {
		mMap.erase(i);

		if ( del )
			delete i->second;

		update();

		return true;
	}
}

bool EntityPropertyMap::removeProperty ( EntityProperty * property, bool del ){
	return removeProperty(property->getProperyType(),del);
}

EntityProperty * EntityPropertyMap::removeProperty ( const Ogre::String& key ){
	PropertyMap::iterator i = mMap.find(key);
	if ( i == mMap.end() ){
		return 0;
	}	
	else {
		EntityProperty * result = i->second;
		mMap.erase(i);
	
		update();

		return result;
	}
}

EntityProperty * EntityPropertyMap::removeProperty ( EntityProperty * property ){
	PropertyMap::iterator i = mMap.find(property->getProperyType());
	if ( i == mMap.end() ){
		return 0;
	}	
	else {
		mMap.erase(i);

		update();

		return property;
	}
}

void EntityPropertyMap::update(){
	mUpdate++;
}


EntityProperty::EntityProperty(const Ogre::String& type):
	mType(type), mEntity(0), mVersion(0)
{
}

EntityProperty::~EntityProperty(void)
{
}

void EntityProperty::write(ZCom_BitStream * bitstream){
	bitstream->addSignedInt(mVersion,sizeof(int) * 8);
	bitstream->addString(mType.c_str());
}

void EntityProperty::read(ZCom_BitStream * bitstream){

	mVersion = bitstream->getSignedInt(sizeof(int)*8);

	int size = bitstream->getStringLength();

	if ( size < 2048 ){
		const char * buffer = bitstream->getStringStatic();
		mType = Ogre::String(buffer);
	}
	else {
		char * buffer = new char[size];
		bitstream->getString(buffer,size);	
		mType = Ogre::String(buffer);
		delete [] buffer;
	}
}


Entity * EntityProperty::getEntity(){
	return mEntity;
}

const Ogre::String& EntityProperty::getProperyType() const {
	return mType;
}


EntityPropertyMapReplicator::EntityPropertyMapReplicator (EntityPropertyMap& data, ZCom_ReplicatorSetup * setup):
	ZCom_ReplicatorBasic(setup), mData(data) {

	m_flags |= ZCOM_REPLICATOR_INITIALIZED;
}

EntityPropertyMapReplicator::EntityPropertyMapReplicator(EntityPropertyMap& data, zU8 _flags, zU8 _rules, zU8 _intercept_id, zS16 _mindelay, zS16 _maxdelay):
	ZCom_ReplicatorBasic(NULL), mData(data) {
	// make sure m_setup will be deleted when the replicator is deleted
	_flags |= ZCOM_REPFLAG_SETUPAUTODELETE;

	// create the setup object
	m_setup = new ZCom_ReplicatorSetup(_flags, _rules, _intercept_id, _mindelay, _maxdelay);

	// out of mem
	if (!m_setup) {
		return;
	}

	m_flags |= ZCOM_REPLICATOR_INITIALIZED;
}

bool EntityPropertyMapReplicator::checkState(){
	return true;
}

void EntityPropertyMapReplicator::packData(ZCom_BitStream * stream){

}

void EntityPropertyMapReplicator::unpackData(ZCom_BitStream * stream, bool store, zU32 estimated_time_sent){
}

void* EntityPropertyMapReplicator::peekData(){
	return 0;
}

void EntityPropertyMapReplicator::clearPeekData(){
}

void EntityPropertyMapReplicator::Process(eZCom_NodeRole localrole, zU32 simulation_time_passed){
}

}
