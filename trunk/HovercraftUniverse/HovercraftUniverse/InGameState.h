#ifndef INGAMESTATE_H
#define INGAMESTATE_H

#include "BasicGameState.h"
#include "HUClient.h"
#include "EntityManager.h"
#include "HUD.h"
#include "RepresentationManager.h"
#include <tinyxml/tinyxml.h>

namespace HovUni {
	/**
	 * A class that represents the ingame state.
	 * This state will take care of passing the right inputs to the right locations,
	 * managing the hud, managing the rendering scene, ...
	 *
	 * @auhtor Nick De Frangh
	 */
	class InGameState : public BasicGameState {
		private:
			/** A reference to the created client core */
			HUClient* mHUClient;

			/** The instantiation of the hud */
			HUD* mHud;

			/** Monitor the time lapsed for the HUClient */
			float mTimeLapsed;

			/** A reference to the entity manager */
			EntityManager* mEntityManager;

			/** A reference to the representation manager */
			RepresentationManager* mRepresentationManager;

			/** A boolean to mark when we want to quit */
			bool mContinue;

		public:
			/**
			 * Constructor
			 */
			InGameState(HUClient* client, TiXmlElement* HUDConfig);

			/**
			 * Function that will handle new Chat Input
			 */
			Hikari::FlashValue onChat(Hikari::FlashControl* caller, const Hikari::Arguments& args);

			/**
			 * Function called when the state gets activated
			 */
			virtual void activate();

			/**
			 * Function called when the state gets disabled
			 */
			virtual void disable();

			/**
			 * Function called every frame, do drawing functions and stuff in here
			 */
			virtual bool frameStarted(const Ogre::FrameEvent & evt);

			/**
			 * @see MouseListener::mouseMoved().
			 * Can be implemented as needed.
			 */
			virtual bool mouseMoved(const OIS::MouseEvent & e);

			/**
			 * @see MouseListener::mousePressed().
			 * Can be implemented as needed.
			 */
			virtual bool mousePressed(const OIS::MouseEvent & e, OIS::MouseButtonID id);
			
			/**
			 * @see MouseListener::mouseReleased().
			 * Can be implemented as needed.
			 */
			virtual bool mouseReleased(const OIS::MouseEvent & e, OIS::MouseButtonID id);

			/**
			 * @see KeyListener::keyPressed().
			 * Can be implemented as needed.
			 */
			virtual bool keyPressed(const OIS::KeyEvent & e);

			/**
			 * @see KeyListener::keyReleased().
			 * Can be implemented as needed.
			 */
			virtual bool keyReleased(const OIS::KeyEvent & e);

		protected:
			/**
			 * Call this function to update the hud visuals
			 */
			void updateHud();
	};
}

#endif //INGAMESTATE_H