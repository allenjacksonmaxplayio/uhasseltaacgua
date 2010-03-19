#ifndef HUAPPLICATION_H_
#define HUAPPLICATION_H_

#include "Application.h"

namespace HovUni {

	/**
	* Main application for the Hovercraft Universe game.
	*
	* @author Kristof Overdulve, Dirk Delahaye
	*/
	class HUApplication : public Application {
	public:

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
		 * @see Application::customSceneSetup().
		 */
		void customSceneSetup();
	};

#endif

}