#include "AsteroidRepresentation.h"
#include "BoostRepresentation.h"
#include "CheckPointRepresentation.h"
#include "FinishRepresentation.h"
#include "HovercraftRepresentation.h"
#include "PortalRepresentation.h"
#include "StartRepresentation.h"
#include "TrackRepresentation.h"
#include "HovercraftLoader.h"
#include "GameView.h"
#include "RepresentationManager.h"
#include <OgreSceneManager.h>

namespace HovUni {


HovercraftLoader::HovercraftLoader(Ogre::SceneManager * sceneMgr, Ogre::String hovName) : mSceneMgr(sceneMgr), mCurrNode(0), mHovName(hovName) {
	// Empty
}

HovercraftLoader::~HovercraftLoader(void) {
	// Empty
}

void HovercraftLoader::onEntity(OgreMax::Types::EntityParameters& entityparameters, const OgreMax::Types::Attachable * parent) {
	Ogre::String userData = entityparameters.extraData->userData;

	if (!userData.empty()) {
		// Fetch the type of entity
		TiXmlDocument mDocument;
		mDocument.Parse(userData.c_str());
		TiXmlElement * root = mDocument.RootElement();

		// If correct xml, read it
		if (root) {
			// Read and set the entity type
			TiXmlElement * gameEntityElm = dynamic_cast<TiXmlElement *>(root->FirstChild());
			Ogre::String entityName = Ogre::String(gameEntityElm->GetText());

			// Read the sub materials
			std::vector<Ogre::String> subMaterials;
			for (size_t subentityIndex = 0; subentityIndex < entityparameters.subentities.size(); subentityIndex++) {
				if (!entityparameters.subentities[subentityIndex].materialName.empty()) {
					subMaterials.push_back(entityparameters.subentities[subentityIndex].materialName);
				}
			}

			// Get the entity to which the representation should refer
			Entity * ent = EntityManager::getClientSingletonPtr()->getEntity(mHovName);
			if (ent) {
				// Create hovercraft representation
				EntityRepresentation * entRep = new HovercraftRepresentation(dynamic_cast<Hovercraft *>(ent), mSceneMgr, entityparameters.meshFile, entityparameters.resourceGroupName, true, entityparameters.castShadows, 
					entityparameters.renderingDistance, entityparameters.materialFile, subMaterials);
				if (entRep) {
					// Add to representation manager
					Ogre::LogManager::getSingletonPtr()->getDefaultLog()->stream() << "HovercraftLoader, success";
					RepresentationManager::getSingletonPtr()->addEntityRepresentation(entRep);
				}
			} else {
				// The entity did not exist
				Ogre::Log::Stream stream = Ogre::LogManager::getSingletonPtr()->getDefaultLog()->stream();
				stream << "Hovercraft with name |" << mHovName << "| does not exist in client." << "\n";

				stream << "Entities are: " << "\n";
				std::vector<Entity *> entities = EntityManager::getClientSingletonPtr()->getAllEntities();
				for (std::vector<Entity *>::const_iterator it = entities.begin(); it != entities.end(); it++) {
					stream << (*it)->getName() << "\t\t" << (*it)->getCategory() << "\n";
				}
			}

			// Clear xml
			mDocument.Clear();
		}
	}
}

void HovercraftLoader::onNode(OgreMax::Types::NodeParameters& nodeparameters, std::vector<OgreMax::Types::NodeAnimation> * animation, const OgreMax::Types::NodeParameters* parent) {
	Ogre::String name = nodeparameters.name;
	
	// Create node
	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode();

	// Set properties
	node->setPosition(nodeparameters.position);
	node->setOrientation(nodeparameters.orientation);
	node->setScale(nodeparameters.scale);

	// Store node as current node
	mCurrNode = node;
}

}