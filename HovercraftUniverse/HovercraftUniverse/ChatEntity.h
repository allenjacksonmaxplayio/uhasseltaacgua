#ifndef CHATENTITY_H
#define CHATENTITY_H

#include "NetworkEntity.h"
#include "ChatEvent.h"
#include "ChatListener.h"
#include <string>
#include <vector>

namespace HovUni {

/**
 * The chat entity which holds the chat lines and allows to send lines to the chat
 *
 * @author Olivier Berghmans
 */
class ChatEntity: public NetworkEntity {
private:
	/** List of listeners to update upon incoming message */
	std::vector<ChatListener*> mListeners;

public:

	/**
	 * Constructor
	 */
	ChatEntity();

	/**
	 * Destructor
	 */
	~ChatEntity();

	/**
	 * Register a listener
	 *
	 * @param listener The listener
	 */
	void registerListener(ChatListener* listener);

	/**
	 * Send a chat line
	 *
	 * @param user the user sending the line
	 * @param line the chat line
	 */
	void sendLine(const string& user, const std::string& line);

	/**
	 * Send a chat line
	 *
	 * @param notif the notification
	 */
	void sendNotification(const std::string& notif);

	//OVERWRITEN FROM NetworkEntity

	/**
	 * @see NetworkEntity::parseEvents(ZCom_BitStream* stream, float timeSince);
	 */
	virtual void parseEvents(ZCom_BitStream* stream, float timeSince);

	/**
	 * @see NetworkEntity::setupReplication();
	 */
	virtual void setupReplication();

	/**
	 * Process a chat event at the server
	 *
	 * @param event an event
	 */
	void processEventsServer(ChatEvent* event);

	/**
	 * Process a chat event at the client
	 *
	 * @param event an event
	 */
	void processEventsClient(ChatEvent* event);

	/**
	 * Get the class name for this class. This is used for registering
	 * the class with the network
	 *
	 * @return the class name
	 */
	static std::string getClassName();
};

}

#endif
