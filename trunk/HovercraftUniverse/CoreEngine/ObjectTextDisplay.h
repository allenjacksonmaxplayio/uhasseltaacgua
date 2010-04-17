#include <OgreMovableObject.h>
#include <OgreCamera.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayElement.h>
#include <OgreLogManager.h>


namespace HovUni {
	/**
	*	Ogre Entity Overlay.
	*	@author Dirk Delahaye
	*/
	class ObjectTextDisplay {
	protected:
		const Ogre::MovableObject* m_p;
		const Ogre::Camera* m_c;
		bool m_enabled;
		Ogre::Overlay* m_pOverlay;
		Ogre::OverlayElement* m_pText;
		Ogre::OverlayContainer* m_pContainer;
		Ogre::String m_text;
		Ogre::String mOverlayName;
	public:
		ObjectTextDisplay(const Ogre::MovableObject* p, const Ogre::Camera* c);
		virtual ~ObjectTextDisplay();
		void enable(bool enable);
		void setText(const Ogre::String& text);
		void update();
	};
}
