#include "GameView.h"

namespace HovUni {

GameView::GameView(HUD * hud, Ogre::Camera * camera) : mHUD(hud), mCamera(camera) {
}

GameView::~GameView() {
}

void GameView::addEntityRepresentation(EntityRepresentation * entityRep) {
	// TODO Check presence
	// TODO Add entity to list
}

void GameView::removeEntityRepresentation() {
	// TODO Check presence
	// TODO Remove entity from list
}

void GameView::draw() {
	// TODO Draw the entity representations
	// TODO Draw the static objects
	// TODO Draw the hud
}

void GameView::drawEntityRepresentations() {
	// TODO Draw the entity representations
}

void drawHUD() {
	// TODO Draw the HUD
}

}