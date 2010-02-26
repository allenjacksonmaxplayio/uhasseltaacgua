#ifndef ENTITYTYPE_H
#define ENTITYTYPE_H

class hkpWorldObject;

namespace HovUni {

/**
 * Class used to annotate havoc world objects with an object type.
 */
class EntityType {

private:

	static int ENITYTYPEPROPERTY;	

public:
	
	enum Type {	
		NOTSET,
		CHARACTER,
		STATIC
	};

	/**
	 * Get the entity type
	 * @param object
	 * @return EntityType
	 */
	static Type getEntityType( hkpWorldObject * object );

	/**
	 * Update the entity type, this should be done only when propery already set
	 * @param object
	 * @param type
	 */
	static void updateEntityType( hkpWorldObject * object, Type type );

	/**
	 * Set the entity type, this should be done only once
	 * @param object
	 * @param type
	 */
	static void setEntityType( hkpWorldObject * object, Type type );
};

}

#endif 