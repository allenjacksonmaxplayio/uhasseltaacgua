#ifndef EntityProperty_H_
#define EntityProperty_H_

#include <zoidcom/zoidcom.h>
#include <map>

namespace HovUni {

class Entity;
class EntityProperty;
class EntityPropertyMapReplicator;

/**
 * The container for properties, it is a wrapper arround a map
 * @author Pieter-Jan Pintens
 */
class EntityPropertyMap {

private:

	/**
	 * The replicator is our friend
	 */
	friend class EntityPropertyMapReplicator;

	/**
	 * The entity the map belongs to
	 */
	Entity * mEntity;

	/**
	 * The actual map
	 */
	std::map<int,EntityProperty*> mMap;

	/**
	 * The current version
	 */
	signed char mUpdate;

public:
	typedef std::pair<int,EntityProperty*> Property;
	typedef std::map<int,EntityProperty*> PropertyMap;

	/**
	 * Constructor
	 */
	EntityPropertyMap( Entity * entity );

	/**
	 * Destructor
	 */
	~EntityPropertyMap();

	/**
	 * Add a property to the map if no property with same key exists in the map
	 *
	 * @param property
	 * @return true if added, false if property with same key already exists
	 */
	bool addProperty( EntityProperty * property  );

	/**
	 * Check if the property with given key exists in the map
	 * 
	 * @return true if the property with given key exists in the map, false otherwise
	 */
	bool hasProperty( int key ) const;

	/**
	 * Get the property with given key
	 * 
	 * @return the property with given key, null if not found
	 */
	EntityProperty * getProperty( int key );

	/**
	 * Remove propery with given key from the map
	 *
	 * @param key, the key of the property
	 * @param del, if true the property will be deleted aswell
	 * @return true if property removed, false if no such property found
	 */
	bool removeProperty ( int key, bool del = true );

	/**
	 * Remove propery from the map
	 *
	 * @param property, the property
	 * @param del, if true the property will be deleted aswell
	 * @return true if property removed, false if no such property found
	 */
	bool removeProperty ( EntityProperty * property, bool del = true );

	/**
	 * Remove propery with given key from the map
	 *
	 * @param key, the key of the property
	 * @return the property removed from the map, null if no such property found
	 */
	EntityProperty * removeProperty ( int key );

	/**
	 * Remove propery from the map
	 *
	 * @param property, the property
	 * @return the property removed from the map, null if no such property found
	 */
	EntityProperty * removeProperty ( EntityProperty * property );

	/**
	 * Call this method when there is an update that needs to be propagated over network
	 */
	void update();
};


/**
 * The base class for properties that can be attached to an entity
 * @author Pieter-Jan Pintens
 */
class EntityProperty
{
protected:

	/**
	 * The map is our friend so it can set entity
	 */
	friend class EntityPropertyMap;

	/**
	 * The type
	 */
	int mType;	

	/**
	 * The entity the property belongs to
	 */
	Entity * mEntity;

	/**
	 * The version of the property
	 */
	signed char mVersion;

public:

	/**
	 * Constructor
	 *
	 * @param type
	 * @param entity
	 */
	EntityProperty( int type );

	/**
	 * Destructor
	 */
	virtual ~EntityProperty(void);

	/**
	 * Get the entity this property belongs to
	 * @return the entity this property belongs to
	 */
	Entity * getEntity();

	/**
	 * Get the property type
	 * @return the property type
	 */
	int getProperyType() const;

	/**
	 * Write this property to bitstream
	 *
	 * @param bitstream
	 */
	virtual void write(ZCom_BitStream * bitstream) = 0;

	/**
	 * Read this property to bitstream
	 *
	 * @param bitstream
	 */
	virtual void read(ZCom_BitStream * bitstream) const = 0;

	/**
	 * Call this method when there is an update that needs to be propagated over network
	 */
	void update();
};

/**
 * Replicator for the property map
 */
class EntityPropertyMapReplicator : public ZCom_ReplicatorAdvanced {

private:

	enum TYPE {
		ADD = 0x0,
		UPDATE = 0x1,
		REMOVE = 0x2
	};

	/**
	 * Data
	 */
	EntityPropertyMap& mData;

	/**
	 * The version of the map
	 */
	unsigned char mUpdate;

	//keep copy of the authority

public:

	EntityPropertyMapReplicator (EntityPropertyMap& data, ZCom_ReplicatorSetup * setup);

	EntityPropertyMapReplicator(EntityPropertyMap& data, zU8 _flags, zU8 _rules, zU8 _intercept_id = 0, zS16 _mindelay = -1, zS16 _maxdelay = -1);

	virtual void onConnectionAdded (ZCom_ConnID _cid, eZCom_NodeRole _remoterole);
 	//A node has become relevant on the specified connection and thus to this replicator, too. 

	virtual void onConnectionRemoved (ZCom_ConnID _cid, eZCom_NodeRole _remoterole){
	}
 	//The node on this connection is no longer relevant. 

	virtual void onDataReceived (ZCom_ConnID _cid, eZCom_NodeRole _remoterole, ZCom_BitStream &_stream, bool _store, zU32 _estimated_time_sent);
 	//Data has been received from the replicator of a remote node. 

	virtual void onLocalRoleChanged (eZCom_NodeRole _oldrole, eZCom_NodeRole _newrole){
	}
 	//The role of the local node which owns this replicator has changed. 

	virtual void onPacketReceived (ZCom_ConnID _cid){
	}
 	//The given connection has received a packet. 
	
	virtual void onPreSendData (ZCom_ConnID _cid, eZCom_NodeRole _remoterole, zU32 *_lastupdate){
	}
 	//Zoidcom is about to transmit data to the given client. 
	
	virtual void onRemoteRoleChanged (ZCom_ConnID _cid, eZCom_NodeRole _oldrole, eZCom_NodeRole _newrole){
	}
 	//The role of a node on a remote connection has changed it's role. 

	virtual void Process (eZCom_NodeRole _localrole, zU32 _simulation_time_passed);
 	//Do any kind of processing. 

};

}

#endif
