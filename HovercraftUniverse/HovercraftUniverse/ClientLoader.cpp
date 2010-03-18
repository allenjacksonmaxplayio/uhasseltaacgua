#include "AsteroidRepresentation.h"
#include "BoostRepresentation.h"
#include "CheckPointRepresentation.h"
#include "FinishRepresentation.h"
#include "HovercraftRepresentation.h"
#include "PortalRepresentation.h"
#include "StartRepresentation.h"
#include "TrackRepresentation.h"
#include "ClientLoader.h"
#include "GameView.h"
#include "RepresentationManager.h"
#include <OgreSceneManager.h>

namespace HovUni {


ClientLoader::ClientLoader(Ogre::SceneManager * sceneMgr) : mSceneMgr(sceneMgr), mCurrNode(0) {
	// Empty
}

ClientLoader::~ClientLoader(void) {
	// Empty
}

void ClientLoader::StartedLoad(){
	//TODO notify server??
}

void ClientLoader::FinishedLoad(bool success) {
	//TODO notify server!!
}

void ClientLoader::UpdatedLoadProgress(Ogre::Real progress) {
	//TODO notify server??
}

void ClientLoader::onSceneData(const OgreMax::Version& formatVersion, const OgreMax::Version& minOgreVersion, const OgreMax::Version& ogreMaxVersion, const Ogre::String& author, const Ogre::String& application, OgreMax::Types::UpAxis upAxis, Ogre::Real unitsPerMeter, const Ogre::String& unitType) {
	// We do nothing with this
}

void ClientLoader::onSkyBox(OgreMax::Types::SkyBoxParameters& skyBoxParameters, std::vector<OgreMax::Types::NodeAnimation> * animation ) {
	// Not yet supported
}

void ClientLoader::onSkyDome(OgreMax::Types::SkyDomeParameters& skyDomeParameters, std::vector<OgreMax::Types::NodeAnimation> * animation) {
	// Not yet supported
}

void ClientLoader::onClipping(Ogre::Real environmentNear, Ogre::Real environmentFar) {
	// Not yet(?) supported
}

void ClientLoader::onAmbientColour(const Ogre::ColourValue& colour) {
	// Just set the value of the colour of the ambient light
	mSceneMgr->setAmbientLight(colour);	
}

void ClientLoader::onShadowProperties(OgreMax::Types::ShadowParameters& parameter) {
	// Not yet supported
}

void ClientLoader::onBackgroundColour(const Ogre::ColourValue& colour) {
	// Not yet(?) supported
}

void ClientLoader::onLight(OgreMax::Types::LightParameters& light, const OgreMax::Types::Attachable * parent) {
	// Not yet supported
}
    
void ClientLoader::onCamera(OgreMax::Types::CameraParameters& params, const OgreMax::Types::Attachable * parent) {
	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Position camera: " << params.position << "\n";

	// These settings only effect the free roaming camera in all game views and not the tracking cameras
	std::vector<GameView *> gameViews = RepresentationManager::getSingletonPtr()->getGameViews();
	for (std::vector<GameView *>::const_iterator it = gameViews.begin(); it != gameViews.end(); it++) {
		// Get camera and apply modifications to free roaming camera
		RaceCamera * cam = (*it)->getCamera();

		// TODO Currently FOV, clipping distances, etc ... are ignored by the parser. This could be applied in a later stage.
		if (mCurrNode) {
			// Use the parent position and orientation
			cam->setFreeroam(mCurrNode->getPosition(), mCurrNode->getOrientation());
		} else {
			// Use the camera position and orientation
			cam->setFreeroam(params.position, params.orientation, params.direction);
		}
	}
}

void ClientLoader::onEntity(OgreMax::Types::EntityParameters& entityparameters, const OgreMax::Types::Attachable * parent) {
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
			Entity * ent = EntityManager::getClientSingletonPtr()->getEntity(entityName);
			if (ent) {
				EntityRepresentation * entRep = 0;
				bool visible = !(entityparameters.visibility == OgreMax::Types::OBJECT_HIDDEN);
				if (ent->getCategory() == Asteroid::CATEGORY) {
					// Create asteroid representation
					entRep = new AsteroidRepresentation(dynamic_cast<Asteroid *>(ent), mSceneMgr, entityparameters.meshFile, entityparameters.resourceGroupName, visible, entityparameters.castShadows, 
						entityparameters.renderingDistance, entityparameters.materialFile, subMaterials);
				} else if (ent->getCategory() == SpeedBoost::CATEGORY) {
					// Create boost representation
					entRep = new BoostRepresentation(dynamic_cast<SpeedBoost *>(ent), mSceneMgr, entityparameters.meshFile, entityparameters.resourceGroupName, visible, entityparameters.castShadows, 
						entityparameters.renderingDistance, entityparameters.materialFile, subMaterials);
				} else if (ent->getCategory() == CheckPoint::CATEGORY) {
					// Create checkpoint representation
					entRep = new CheckPointRepresentation(dynamic_cast<CheckPoint *>(ent), mSceneMgr, entityparameters.meshFile, entityparameters.resourceGroupName, visible, entityparameters.castShadows, 
						entityparameters.renderingDistance, entityparameters.materialFile, subMaterials);
				} else if (ent->getCategory() == Finish::CATEGORY) {
					// Create finish representation
					entRep = new FinishRepresentation(dynamic_cast<Finish *>(ent), mSceneMgr, entityparameters.meshFile, entityparameters.resourceGroupName, visible, entityparameters.castShadows, 
						entityparameters.renderingDistance, entityparameters.materialFile, subMaterials);
				} else if (ent->getCategory() == Hovercraft::CATEGORY) {
					// Create hovercraft representation
					entRep = new HovercraftRepresentation(dynamic_cast<Hovercraft *>(ent), mSceneMgr, entityparameters.meshFile, entityparameters.resourceGroupName, visible, entityparameters.castShadows, 
						entityparameters.renderingDistance, entityparameters.materialFile, subMaterials);
				} else if (ent->getCategory() == Portal::CATEGORY) {
					// Create portal representation
					entRep = new PortalRepresentation(dynamic_cast<Portal *>(ent), mSceneMgr, entityparameters.meshFile, entityparameters.resourceGroupName, visible, entityparameters.castShadows, 
						entityparameters.renderingDistance, entityparameters.materialFile, subMaterials);
				} else if (ent->getCategory() == Start::CATEGORY) {
					// Create start representation
					entRep = new StartRepresentation(dynamic_cast<Start *>(ent), mSceneMgr, entityparameters.meshFile, entityparameters.resourceGroupName, visible, entityparameters.castShadows, 
						entityparameters.renderingDistance, entityparameters.materialFile, subMaterials);
				} else if (ent->getCategory() == Track::CATEGORY) {
					// Create track representation
					entRep = new TrackRepresentation(dynamic_cast<Track *>(ent), mSceneMgr, entityparameters.meshFile, entityparameters.resourceGroupName, visible, entityparameters.castShadows, 
						entityparameters.renderingDistance, entityparameters.materialFile, subMaterials);
				} else {
					// Unrecognized entity, ignore
				}

				if (entRep) {
					// Add to representation manager
					RepresentationManager::getSingletonPtr()->addEntityRepresentation(entRep);
				}
			} else {
				// The entity did not exist
				Ogre::Log::Stream stream = Ogre::LogManager::getSingletonPtr()->getDefaultLog()->stream();
				stream << "Entity with name |" << entityName << "| does not exist in client." << "\n";

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

void ClientLoader::onNode(OgreMax::Types::NodeParameters& nodeparameters, std::vector<OgreMax::Types::NodeAnimation> * animation, const OgreMax::Types::NodeParameters* parent) {
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