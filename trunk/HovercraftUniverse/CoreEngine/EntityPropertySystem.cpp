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

bool EntityPropertyMap::hasProperty( int key ) const {
	return mMap.find(key) != mMap.end();
}

EntityProperty * EntityPropertyMap::getProperty( int key ){
	PropertyMap::iterator i = mMap.find(key);
	if ( i == mMap.end() ){
		return 0;
	}	
	else {
		return i->second;
	}
}

bool EntityPropertyMap::removeProperty ( int key, bool del ){

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

EntityProperty * EntityPropertyMap::removeProperty ( int key ){
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


EntityProperty::EntityProperty(int type):
	mType(type), mEntity(0), mVersion(0)
{
}

EntityProperty::~EntityProperty(void)
{
}

Entity * EntityProperty::getEntity(){
	return mEntity;
}

int EntityProperty::getProperyType() const {
	return mType;
}


EntityPropertyMapReplicator::EntityPropertyMapReplicator (EntityPropertyMap& data, ZCom_ReplicatorSetup * setup):
	ZCom_ReplicatorAdvanced(setup), mData(data) {

	m_flags |= ZCOM_REPLICATOR_INITIALIZED;
}

EntityPropertyMapReplicator::EntityPropertyMapReplicator(EntityPropertyMap& data, zU8 _flags, zU8 _rules, zU8 _intercept_id, zS16 _mindelay, zS16 _maxdelay):
	ZCom_ReplicatorAdvanced(NULL), mData(data) {
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

void EntityPropertyMapReplicator::onConnectionAdded (ZCom_ConnID _cid, eZCom_NodeRole _remoterole){

	//if i'm the server send the entire map info to the new guy
	if ( getNode()->getRole() == eZCom_RoleAuthority ){

		//for every entry in my property map send an ADD command to the new client
		
		ZCom_BitStream stream;

		//version 
		stream.addSignedInt(mData.mUpdate,sizeof(zS8)*8);
		stream.addInt(mData.mMap.size(),sizeof(zU8)*8);

		//an add command for all
		for ( EntityPropertyMap::PropertyMap::iterator i = mData.mMap.begin(); i != mData.mMap.end(); i++ ){
			stream.addInt(ADD,sizeof(zU8)*2);

			//write the type
			stream.addSignedInt(i->second->getProperyType(),sizeof(int)*8);

			//write the object
			i->second->write(&stream);		
		}

		sendDataDirect(eZCom_ReliableOrdered,_cid,&stream,0);
	}
}

void EntityPropertyMapReplicator::onDataReceived (ZCom_ConnID _cid, eZCom_NodeRole _remoterole, ZCom_BitStream &_stream, bool _store, zU32 _estimated_time_sent){
	//Data from server is cool
	if ( _remoterole == eZCom_RoleAuthority ){

		//TODO versie check

		//parse the info and update the map	
		zS8 version = _stream.getSignedInt(sizeof(zS8)*8);
		zU8 records = _stream.getInt(sizeof(zU8)*8);

		//check the type of the records and apply the updates
		for ( zU8 i = 0; i < records; i++ ){
			zU8 type = _stream.getInt(sizeof(zU8)*2);	//2BITS
			int proptype = _stream.getSignedInt(sizeof(int)*8);

			switch ( type ){
				case UPDATE:
					{
					EntityProperty * property = mData.getProperty(proptype);
					property->read(&_stream);
					break;
					}
				case ADD:
					//TODO LOOKUP AND RESTORE??
					break;
				case REMOVE:
					{
					//kill it
					mData.removeProperty(proptype,true);
					break;
					}
			};
		}
	}
	else if ( _remoterole == eZCom_RoleOwner && getNode()->getRole() == eZCom_RoleAuthority ){
		//TODO FIX SOME SYSTEM THAT DOES PERMISSIONS??
		zS8 version = _stream.getSignedInt(sizeof(zS8)*8);
		zU8 records = _stream.getInt(sizeof(zU8)*8);

		//check the type of the records and apply the updates
		for ( zU8 i = 0; i < records; i++ ){
			zU8 type = _stream.getInt(sizeof(zU8)*2);	//2BITS
			
			switch ( type ){
				case UPDATE:
					{
					EntityProperty * property = mData.getProperty(type);
					property->read(&_stream);
					break;
					}
				case ADD:
					break;
				case REMOVE:
					{
					mData.removeProperty(type,true);
					break;
					}
			};
		}

		//TODO fix version number

		//SYNC WITH OTHER CLIENTS (happens next update..)
	}
}

void EntityPropertyMapReplicator::Process (eZCom_NodeRole _localrole, zU32 _simulation_time_passed){
	if ( _localrole == eZCom_RoleAuthority || _localrole == eZCom_RoleOwner ){
		//check for updates and send them

		if ( mData.mUpdate != mUpdate ){
/*
			BitStream bs;
		
			//if i'm owner i propagate data to server, he will propagete to others!
			if ( _localrole == eZCom_RoleOwner ){
				sendDataDirect(eZCom_SendMode::eZCom_ReliableOrdered, AUTH, &bs);
			}
			else {
				sendData(eZCom_SendMode::eZCom_ReliableOrdered, &bs);
			}

			mUpdate = mData.mUpdate;*/
		}


	}
}



}
