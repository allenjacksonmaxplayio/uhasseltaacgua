#ifndef CHATENTITY_H
#define CHATENTITY_H

#include "NetworkEntity.h"
#include "ChatEvent.h"
#include <vector>
#include <string>

namespace HovUni {

/**
 * The chat entity which holds the chat lines and allows to send lines to the chat
 *
 * @author Olivier Berghmans
 */
class ChatEntity: public NetworkEntity {
private:
	/** The maximum number of lines kept in the list */
	unsigned mSize;

	/** The list of chat lines */
	std::vector<std::string> mList;

public:

	/**
	 * Constructor
	 *
	 * @param size the number of lines that are kept in the cache
	 */
	ChatEntity(unsigned size);

	/**
	 * Destructor
	 */
	~ChatEntity();

	/**
	 * Send a chat line
	 *
	 * @param user the user sending the line
	 * @param line the chat line
	 */
	void sendLine(const string& user, const std::string& line);

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

private:

	/**
	 * Add a line to the list
	 *
	 * @param line the line
	 */
	void addLine(const std::string& line);
};

}

#endif
