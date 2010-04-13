#include "Application.h"
#include "AsteroidRepresentation.h"
#include "BoostRepresentation.h"
#include "CheckPointRepresentation.h"
#include "FinishRepresentation.h"
#include "HovercraftRepresentation.h"
#include "PortalRepresentation.h"
#include "StartRepresentation.h"
#include "TrackRepresentation.h"
#include "ClientPreparationLoader.h"
#include "GameView.h"
#include "RepresentationManager.h"
#include <OgreSceneManager.h>

namespace HovUni {

ClientPreparationLoader::ClientPreparationLoader() :
	mCurrFilename("") {
	// Create a loader
	mLoader = new ClientLoader(Application::msSceneMgr);
}

ClientPreparationLoader::~ClientPreparationLoader(void) {
	// Destroy the loader
	if (mLoader) {
		delete mLoader;
		mLoader = 0;
	}
}

void ClientPreparationLoader::FinishedLoad(bool success) {
	if (success) {
		// The filename should be loadable
		assert(!mCurrFilename.empty());
		mPreparationEntries.push_back(ClientPreparationEntry(mLoader, mCurrEntitiesFound, mCurrFilename));
	}

	// Clean up for next file
	mCurrEntitiesFound.clear();
	mCurrFilename = "";
}

void ClientPreparationLoader::onEntity(OgreMax::Types::EntityParameters& entityparameters,
		const OgreMax::Types::Attachable * parent) {
	Ogre::String userData = entityparameters.extraData->userData;

	if (!userData.empty()) {
		// Fetch the type of entity
		TiXmlDocument mDocument;
		mDocument.Parse(userData.c_str());
		TiXmlElement * root = mDocument.RootElement();

		// If correct xml, read it
		if (root) {
			// Read and set the entity type
			TiXmlElement * gameEntityElm = dynamic_cast<TiXmlElement *> (root->FirstChild());
			Ogre::String entityName = Ogre::String(gameEntityElm->GetText());

			if (!entityName.empty()) {
				// Add entity
				mCurrEntitiesFound.push_back(entityName);
			}

			// Clear xml
			mDocument.Clear();
		}
	}
}

void ClientPreparationLoader::registerLoader(Ogre::String filename) {
	mCurrFilename = filename;

	// Load the file for which a loader must be created
	load(mCurrFilename);
}

void ClientPreparationLoader::update(Ogre::String entityName) {
	for (std::vector<ClientPreparationEntry>::iterator it = mPreparationEntries.begin(); it != mPreparationEntries.end(); it++) {
		if ((*it).entityFound(entityName)) {
			// Activate loader, since all entities were found. Then remove the preparation entries
			(*it).activateLoader();
			it = mPreparationEntries.erase(it);

			// Break out of loop
			if (it == mPreparationEntries.end()) {
				break;
			}
		}
	}
}

ClientPreparationEntry::ClientPreparationEntry(ClientLoader * loader, std::vector<Ogre::String> entitiesToFind,
		Ogre::String filename) :
	mLoader(loader), mEntitiesToFind(entitiesToFind), mFilename(filename) {
	// All was initialized
}

bool ClientPreparationEntry::entityFound(Ogre::String entityName) {
	for (std::vector<Ogre::String>::const_iterator it = mEntitiesToFind.begin(); it != mEntitiesToFind.end(); it++) {
		if ((*it) == entityName) {
			mEntitiesToFind.erase(it);
			break;
		}
	}

	return mEntitiesToFind.empty();
}

void ClientPreparationEntry::activateLoader() {
	assert(mEntitiesToFind.empty());
	mLoader->load(mFilename);
}

}
