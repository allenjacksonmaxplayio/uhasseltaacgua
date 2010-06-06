#include "BasicView.h"

namespace HovUni {

	BasicView::BasicView(Ogre::RenderWindow* renderWindow, Ogre::SceneManager* sceneManager, const Ogre::String& name) : mRenderWindow(renderWindow), mSceneManager(sceneManager), mViewName(name) {
		//Create a camera for this view
		//TODO: We might need some sort of naming convention?
		mOgreCamera = mSceneManager->createCamera(mViewName+"_CAM");
		mOgreCamera->setNearClipDistance(0.1f);
		mOgreCamera->setFarClipDistance(30000.0f);

		//Create a viewport for this view
		mViewport = mRenderWindow->addViewport(mOgreCamera);

		//Fix the aspect ratio
		mOgreCamera->setAspectRatio(Ogre::Real(mViewport->getActualWidth()) / Ogre::Real(mViewport->getActualHeight()));
	}

	BasicView::~BasicView() {
	}

	void BasicView::draw(Ogre::Real timeSinceLastFrame) {
		
	}
}