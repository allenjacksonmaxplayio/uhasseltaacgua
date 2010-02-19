#include "HikariDemo.h"
#include "GUIManager.h"

#include <iostream>

using namespace Ogre;
using namespace Hikari;

using std::endl;
using std::cout;

HikariDemo::HikariDemo() : root(0), shouldQuit(false), renderWin(0), sceneMgr(0), inputMgr(0)
{
	lastTime = timer.getMilliseconds();

	root = new Root();

	shouldQuit = !root->showConfigDialog();
	if(shouldQuit) return;

	renderWin = root->initialise(true, "HikariDemo");
	sceneMgr = root->createSceneManager("DefaultSceneManager");
	WindowEventUtilities::addWindowEventListener(renderWin, this);

	createScene();

	setupHikari();

	loadInputSystem();
}

HikariDemo::~HikariDemo()
{
	WindowEventUtilities::removeWindowEventListener(renderWin, this);

	if(inputMgr)
		delete inputMgr;
	if (webcam)
		delete webcam;
	if(root)
		delete root;
}

void HikariDemo::createScene()
{
	sceneMgr->setAmbientLight(ColourValue::White);
	sceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_ADDITIVE);

	Camera* camera = sceneMgr->createCamera("MainCam");
	viewport = renderWin->addViewport(camera);
	viewport->setBackgroundColour(ColourValue(0.2f, 0.2f, 0.2f));

	camera->setAspectRatio((float)viewport->getActualWidth() / (float)viewport->getActualHeight());
}

void HikariDemo::setupHikari()
{
	//Initialise the GUIManager
	HovUni::GUIManager::init("..\\..\\Media\\GUI", viewport);

	//Create Flash overlays
	webcam = new HovUni::BasicOverlay("webcam", "WebcamViewer.swf", 300, 300, Hikari::Position(Hikari::RelativePosition::Center));

	//Display the Flash overlays
	HovUni::GUIManager::getSingletonPtr()->activateOverlay(*webcam);
}

void HikariDemo::update()
{
	HovUni::GUIManager::getSingletonPtr()->update();

	root->renderOneFrame();
	Ogre::WindowEventUtilities::messagePump();
	inputMgr->capture();
}

void HikariDemo::loadInputSystem()
{
	inputMgr = InputManager::getSingletonPtr();
    inputMgr->initialise(renderWin);
	inputMgr->addMouseListener(HovUni::GUIManager::getSingletonPtr(), "MouseListener");
	inputMgr->addKeyListener(HovUni::GUIManager::getSingletonPtr(), "KeyListener");
}

void HikariDemo::windowMoved(RenderWindow* rw) {

}

void HikariDemo::windowResized(RenderWindow* rw) {
	inputMgr->setWindowExtents(rw->getWidth(), rw->getHeight());
}

void HikariDemo::windowClosed(RenderWindow* rw)  {
	shouldQuit = true;
}

void HikariDemo::windowFocusChange(RenderWindow* rw) {
}
