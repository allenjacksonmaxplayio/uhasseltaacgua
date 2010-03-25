#ifndef HUAPPLICATION_H_
#define HUAPPLICATION_H_

#include "Application.h"
#include "ClientPreparationLoader.h"

namespace HovUni {

	/**
	* Main application for the Hovercraft Universe game.
	*
	* @author Kristof Overdulve, Dirk Delahaye
	*/
	class HUApplication : public Application {
	public:

		/** The client preparation loader that can be used to read and reread scenes to render */
		static ClientPreparationLoader * msPreparationLoader;

		/**
		* Constructor.
		*/
		HUApplication();

		/**
		* Destructor.
		*/
		~HUApplication();

		/**
		 * @see Application::playMusic().
		 */
		void playMusic(SoundManager * soundMgr);

		/**
		 * @see Application::getInitialGameState().
		 */
		BasicGameState * getInitialGameState();

		/**
		 * @see Application::customSceneSetup().
		 */
		void customSceneSetup();

		/**
		 * @see Application::init().
		 */
		void init();
	};

#endif

}