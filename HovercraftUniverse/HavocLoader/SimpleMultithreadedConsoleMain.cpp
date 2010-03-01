#include "windows.h"

#include "HoverCraftUniverseWorld.h"

#include "Character.h"


#include <OgreWindowEventUtilities.h>
#include "../HovercraftUniverse/InputManager.h"
#include <OgreRoot.h>
using namespace HovUni;


class KeyLister : public OIS::KeyListener, public OIS::MouseListener {

private:

	HoverCraftUniverseWorld * mHavoc;

public:

	KeyLister( HoverCraftUniverseWorld * havoc ): mHavoc(havoc) {		
	}

	/**
	 * Notifies all the listeners that the given key was pressed.
	 *
	 * @param e the key event that will be propagated to all listeners
	 * @return whether succesful
	 */
	bool keyPressed(const OIS::KeyEvent &e){
		if ( e.text == 'a'){
			mHavoc->load(".\\..\\..\\..\\art\\models\\planetgravity_L4101.hkx");
		}	
		if ( e.text == 'z'){
			mHavoc->load(".\\..\\..\\..\\art\\models\\test_Default.hkx");
		}
		if ( e.text == 'r'){
			mHavoc->load(".\\..\\..\\..\\art\\models\\simplephys_L4101.hkx");
		}
		if ( e.text == 'e' ){
			//test the contextcontainer
			CharacterContextContainer container;

			hkpCharacterState* state;
			hkpCharacterStateManager* manager = new hkpCharacterStateManager();

			state = new hkpCharacterStateOnGround();
			manager->registerState( state,	HK_CHARACTER_ON_GROUND);
			state->removeReference();

			state = new hkpCharacterStateInAir();
			manager->registerState( state,	HK_CHARACTER_IN_AIR);
			state->removeReference();

			hkpCharacterContext * orccontext = new hkpCharacterContext(manager, HK_CHARACTER_IN_AIR);	
			manager->removeReference();

			// Set new filter parameters for final output velocity filtering
			// Smoother interactions with small dynamic boxes
			orccontext->setCharacterType(hkpCharacterContext::HK_CHARACTER_RIGIDBODY);
			orccontext->setFilterParameters(0.9f,12.0f,200.0f);

			container.registerContext("ORC",orccontext);
			orccontext->removeReference();

			hkpCharacterContext * c;
			c = container.getCharacterContext("ORC");
			c->removeReference();

			c = container.getCharacterContext("Default");
			c->removeReference();
		}


		/*
		const hkReal MOUSE_SENSITIVITY = 1.0f;
		int mouseX = env->m_window->getMouse().getPosX();
		int halfWindowWidth = env->m_window->getCurrentViewport()->getWidth() >> 1;
		int halfWindowHeight = env->m_window->getCurrentViewport()->getHeight() >> 1;

		{
			hkReal inc  = hkReal(halfWindowWidth - mouseX) / halfWindowWidth;
			inc = (inc < -1.0f) ? -1.0f : inc;
			inc = (inc >  1.0f) ?  1.0f : inc;
			deltaAngle = 3.4f * inc * MOUSE_SENSITIVITY;
		}


		// Snap mouse back to middle
		env->m_window->setMousePosition(halfWindowWidth, halfWindowHeight);

		const hkgKeyboard& keyboard = env->m_window->getKeyboard();
		if (keyboard.getKeyState('A')) posX=1.f;
		if (keyboard.getKeyState('D')) posX=-1.f;
		if (keyboard.getKeyState('W')) posY=-1.f;
		if (keyboard.getKeyState('S')) posY=1.f;

		hkReal lenSqd = posY * posY + posX * posX;
		if (lenSqd > HK_REAL_MIN)
		{
			lenSqd = hkMath::sqrt(lenSqd);
			posY /= lenSqd;
			posX /= lenSqd;
		}

		

		*/

		return true;
	}

	virtual bool mouseMoved( const OIS::MouseEvent &arg ) {
		return true;
	}

	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
		return true;
	}

	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
		return true;
	}

	/**
	 * Notifies all the listeners that the given key was released.
	 *
	 * @param e the key event that will be propagated to all listeners
	 * @return whether succesful
	 */
	bool keyReleased(const OIS::KeyEvent &e){
		return true;
	}
};

class Application {
protected:

	/** The root Ogre object */
	Ogre::Root * mOgreRoot;

	/** The input manager */
	InputManager * mInputManager;

public:

	/**
	 * Constructor.
	 *
	 */
	Application(void){}

	/**
	 * Destructor.
	 */
	virtual ~Application(void){}

	/**
	 * The main method that triggers the application to run.
	 */
	void go(){
	createRoot();
	setupRenderSystem();
	createRenderWindow();
	initializeResourceGroups();
	setupInputSystem();
	setupScene();
	startRenderLoop();
}

	void createRoot(){
		mOgreRoot = new Ogre::Root();
	}

	void setupRenderSystem(){
	if (!mOgreRoot->restoreConfig() && !mOgreRoot->showConfigDialog()) {
		// TODO Throw exception
	}
	}

	void createRenderWindow(){
		mOgreRoot->initialise(true, "Hovercraft Universe");
	}

	void initializeResourceGroups(){
		Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

	void setupScene(){
		Ogre::SceneManager * sceneMgr = mOgreRoot->createSceneManager(Ogre::ST_GENERIC, "Default");
		// TODO Create a Camera manager that creates cameras for each gameview, then add this on the fly
		//		to the viewports
		Ogre::Camera * cam = sceneMgr->createCamera("Camera");
		cam->setNearClipDistance(5);
		Ogre::Viewport * vp = mOgreRoot->getAutoCreatedWindow()->addViewport(cam);

		// TODO Put somewhere else
		Ogre::SceneNode * node = sceneMgr->getRootSceneNode()->createChildSceneNode("CamNode", Ogre::Vector3(-400, 200, 400));
		node->yaw(Ogre::Degree(-45));
		node = node->createChildSceneNode("PitchNode");
		node->attachObject(cam);

		// TODO Do the operations below belong here or as in separated methods
		// Set ambient light
		sceneMgr->setAmbientLight(Ogre::ColourValue(0.25, 0.25, 0.25));
	}

	void setupInputSystem(){
		mInputManager = InputManager::getSingletonPtr();
		mInputManager->initialise(mOgreRoot->getAutoCreatedWindow());
	}
	
	void startRenderLoop() {
		//do havoc sim in background
		HoverCraftUniverseWorld mHavoc;
		
		KeyLister listener(&mHavoc);

		HovUni::InputManager::getSingletonPtr()->addKeyListener(&listener,"KB");
		HovUni::InputManager::getSingletonPtr()->addMouseListener(&listener,"MOUSE");

		// A stopwatch for waiting until the real time has passed
		hkStopwatch stopWatch;
		stopWatch.start();
		hkReal lastTime = stopWatch.getElapsedSeconds();

		//run physics at 60FPS
		hkReal timestep = 1.f / 120.f;

		while ( true )
		{
			Ogre::WindowEventUtilities::messagePump();

			HovUni::InputManager::getSingletonPtr()->capture();

			mOgreRoot->renderOneFrame(timestep);

			mHavoc.update(timestep);

			// Pause until the actual time has passed
			while (stopWatch.getElapsedSeconds() < lastTime + timestep);
				lastTime += timestep;			
		}
	}

};


int main( int argc, char * argv[] ){
//INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT) {
	Application app;

	try {
		app.go();
	} catch (Ogre::Exception & e) {
		MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}

	return 0;
}
