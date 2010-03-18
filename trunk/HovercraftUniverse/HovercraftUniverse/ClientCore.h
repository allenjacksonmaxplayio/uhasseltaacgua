#ifndef CLIENTCORE_H_
#define CLIENTCORE_H_

#include "NetworkClient.h"
#include "EntityManager.h"
#include "NetworkIDManager.h"
#include "Lobby.h"

namespace HovUni {

/**
 * This class represents the core of the client. It holds the controls
 * for the networking etc.
 *
 * @author Olivier Berghmans
 */
class ClientCore: public NetworkClient
{
private:
	/** The entity manager */
	EntityManager * mEntityManager;

	/** The entity manager */
	NetworkIDManager* mIDManager;

	/** The lobby */
	Lobby* mLobby;

	/** The scene manager */
	Ogre::SceneManager * mSceneMgr;

public:
	/**
	 * Constructor for a client using a remote connection
	 *
	 * @param name the name of the server
	 * @param port the port of the server
	 */
	ClientCore(const char* name, unsigned int port = 2375);

	/**
	 * Constructor for a client using a local connection. This client
	 * must be running in the same instance of a program as the server. 
	 * It is used for combining the client and server to avoid the
	 * overhead of real network.
	 */
	ClientCore();

	/**
	 * Destructor
	 */
	~ClientCore();

	/**
	 * Process incoming and outgoing packets
	 */
	virtual void process();

	//TODO remove
	void start();

private:
	/**
	 * Initialize the class
	 */
	void initialize();

//
// ZCom_Control callbacks
//
public:
	/**
	 * Connection process finished (Client).
	 *
	 * @param id The connection's ID
	 * @param result The result of the connection process
	 * @param reply The reply given by the destination
	 */
	void ZCom_cbConnectResult(ZCom_ConnID id, eZCom_ConnectResult result, ZCom_BitStream& reply);

	/**
	 * Connection has been closed and is about to be deleted (Server, Client).
	 *
	 * @param id The connection's ID
	 * @param reason Reason code. If reason is eZCom_ClosedDisconnect, then reasondata might contain more info.
	 * @param reasondata The reason of the disconnector.
	 */
	void ZCom_cbConnectionClosed(ZCom_ConnID id, eZCom_CloseReason reason, ZCom_BitStream& reasondata);

	/**
	 * Direct data has been received (Server, Client).
	 *
	 * @param id The connection's ID
	 * @param data The data received
	 */
	void ZCom_cbDataReceived(ZCom_ConnID id, ZCom_BitStream& data);

	/**
	 * ZoidLevel migration process finished (Server, Client).
	 *
	 * @param id The connection's ID
	 * @param result Result of the migration process
	 * @param new_level New ZoidLevel of the connection
	 * @param reason Additional data passed by the server
	 */
	void ZCom_cbZoidResult(ZCom_ConnID id, eZCom_ZoidResult result, zU8 new_level, ZCom_BitStream& reason);

	/**
	 * Server requests to create a new node for a new dynamic object/node (Client).
	 *
	 * @param id The connection's ID
	 * @param requested_class Class ID of the requested node
	 * @param announcedata Data set by the server
	 * @param role Role the newly created node will posses
	 * @param net_id The network ID of the requested node. Not needed directly here but may be useful.
	 */
	void ZCom_cbNodeRequest_Dynamic(ZCom_ConnID id, ZCom_ClassID requested_class, ZCom_BitStream* announcedata, eZCom_NodeRole role, ZCom_NodeID net_id);

};

}

#endif
