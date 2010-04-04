#ifndef EntityProperty_H_
#define EntityProperty_H_

#include <zoidcom/zoidcom.h>
#include <OgreString.h>
#include <map>

namespace HovUni {

class Entity;
class EntityProperty;

/**
 * The container for properties, it is a wrapper arround a map
 * @author Pieter-Jan Pintens
 */
class EntityPropertyMap {

private:

	/**
	 * The entity the map belongs to
	 */
	Entity * mEntity;

	/**
	 * The actual map
	 */
	std::map<Ogre::String,EntityProperty*> mMap;

	/**
	 * The current version
	 */
	int mUpdate;

public:
	typedef std::pair<Ogre::String,EntityProperty*> Property;
	typedef std::map<Ogre::String,EntityProperty*> PropertyMap;

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
	bool hasProperty( const Ogre::String& key ) const;

	/**
	 * Get the property with given key
	 * 
	 * @return the property with given key, null if not found
	 */
	EntityProperty * getProperty( const Ogre::String& key );

	/**
	 * Remove propery with given key from the map
	 *
	 * @param key, the key of the property
	 * @param del, if true the property will be deleted aswell
	 * @return true if property removed, false if no such property found
	 */
	bool removeProperty ( const Ogre::String& key, bool del = true );

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
	EntityProperty * removeProperty ( const Ogre::String& key );

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
	Ogre::String mType;	

	/**
	 * The entity the property belongs to
	 */
	Entity * mEntity;

	/**
	 * The version of the property
	 */
	int mVersion;

public:

	/**
	 * Constructor
	 *
	 * @param type
	 * @param entity
	 */
	EntityProperty( const Ogre::String& type );

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
	const Ogre::String& getProperyType() const;

	/**
	 * Write this property to bitstream
	 * This method must be overwriten and the parent must be called
	 *
	 * @param bitstream
	 */
	void write(ZCom_BitStream * bitstream);

	/**
	 * Read this property to bitstream
	 * This method must be overwriten and the parent must be called
	 *
	 * @param bitstream
	 */
	void read(ZCom_BitStream * bitstream);

	/**
	 * Call this method when there is an update that needs to be propagated over network
	 */
	void update();

};

/**
 * Replicator for the property map
 */
class EntityPropertyMapReplicator : public ZCom_ReplicatorBasic {

private:

	/**
	 * Data
	 */
	EntityPropertyMap& mData;

public:

	EntityPropertyMapReplicator (EntityPropertyMap& data, ZCom_ReplicatorSetup * setup);

	EntityPropertyMapReplicator(EntityPropertyMap& data, zU8 _flags, zU8 _rules, zU8 _intercept_id = 0, zS16 _mindelay = -1, zS16 _maxdelay = -1);

	/**
	 * Check the state of the variable to replicate
	 *
	 * @return true if there needs to be an update
	 */
	bool checkState();

	/**
	 * Pack the data in the stream in order to send an update
	 *
	 * @param _stream the stream
	 */
	void packData(ZCom_BitStream *_stream);

	/**
	 * Unpack the data from a stream after receiving an update
	 *
	 * @param _stream the stream
	 * @param _store whether to store the new data
	 * @param _estimated_time_sent indicator of when the data was approximately sent
	 */
	void unpackData(ZCom_BitStream *_stream, bool _store, zU32 _estimated_time_sent);

	/**
	 * Peek at the data without actually unpacking it
	 */
	void* peekData();

	/**
	 * Clear data used when peeking at data
	 */
	void clearPeekData();

	/**
	 * Process
	 *
	 * @param _localrole the local node role
	 * @param _simulation_time_passed the time passed in the simulation
	 */
	void Process(eZCom_NodeRole _localrole, zU32 _simulation_time_passed);

};

}

#endif
