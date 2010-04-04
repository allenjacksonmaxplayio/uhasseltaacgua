#ifndef EntityProperty_H_
#define EntityProperty_H_

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
	const Ogre::String mType;	

	/**
	 * The entity the property belongs to
	 */
	Entity * mEntity;

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
};

}

#endif
