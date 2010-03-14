#ifndef MOUSEVISUALISATION_H
#define MOUSEVISUALISATION_H

#include <Ogre.h>
#include <OgrePanelOverlayElement.h>

namespace HovUni {
	class MouseVisualisation {
		private:
			Ogre::Overlay* mGuiOverlay;
			Ogre::OverlayContainer* mCursorContainer;
			Ogre::TexturePtr mTexture;
			Ogre::MaterialPtr mMaterial;

			Ogre::Real mWindowWidth;
			Ogre::Real mWindowHeight;

		public:
			MouseVisualisation();

			~MouseVisualisation(void) {}

			void setImage(const Ogre::String& filename);

			void setWindowDimensions(unsigned int width, unsigned int height);

			void setVisible(bool visible);

			void updatePosition(int x, int y);

			Ogre::Real clamp(Ogre::Real a, Ogre::Real min, Ogre::Real max);
	};
}
#endif //MOUSEVISUALISATION_H
