#ifndef _OVERLAYPARAMETERS_H
#define _OVERLAYPARAMETERS_H

#include <Hikari.h>
#include <OgreString.h>
#include "IResolution.h"

namespace HovUni {

	template <typename T>
	class OverlayParameters {
		private:
			/** The name for the component */
			Ogre::String mName;
			/** The name of the file that has to be loaded */
			Ogre::String mFilename;
			/** The position to place the overlay */
			Hikari::Position mPosition;
			/** The resolution of the overlay */
			IResolution* mResolution;
		
		public:
			/** The class of the overlay */
			typedef T mType;

			OverlayParameters(const Ogre::String& name, const Ogre::String& filename, const Hikari::Position& position, IResolution* resolution);

			inline Ogre::String getName() { return mName; }

			inline Hikari::Position getPosition() { return mPosition; }
	};

	template <typename T>
	OverlayParameters<T>::OverlayParameters(const Ogre::String& name, const Ogre::String& filename, const Hikari::Position& position, IResolution* resolution) {
		
	}
}

#endif //_OVERLAYPARAMETERS_H