#ifndef LISTENABLE_H_
#define LISTENABLE_H_

#include <vector>

namespace HovUni {

/**
 * A base class that implements basic functionality for adding and removing
 * listeners.
 *
 * @author Olivier Berghmans
 */
template<typename ListenerType>
class Listenable {
public:
	/** The type of the listeners */
	typedef ListenerType value_type;

	/** The iterator for the listeners */
	typedef typename std::vector<ListenerType *>::iterator listener_iterator;

	/** The iterator for the listeners */
	typedef typename std::vector<ListenerType *>::const_iterator listener_const_iterator;

protected:
	/** The listeners */
	std::vector<ListenerType*> mListeners;

public:
	/**
	 * Add a listener
	 *
	 * @param listener the listener which will get called back upon events
	 */
	void addListener(ListenerType* listener);

	/**
	 * Remove a listener
	 *
	 * @param listener the listener
	 */
	void removeListener(ListenerType* listener);

	/**
	 * Clear the listeners
	 *
	 * @param listener the listener
	 */
	void listenersClear();

	/**
	 * Get the begin iterator for the listeners
	 *
	 * @return the begin iterator
	 */
	listener_iterator listenersBegin();

	/**
	 * Get the begin iterator for the listeners
	 *
	 * @return the begin iterator
	 */
	listener_const_iterator listenersBegin() const;

	/**
	 * Get the end iterator for the listeners
	 *
	 * @return the end iterator
	 */
	listener_iterator listenersEnd();

	/**
	 * Get the end iterator for the listeners
	 *
	 * @return the end iterator
	 */
	listener_const_iterator listenersEnd() const;

};

}

#include "ListenableImpl.h"

#endif
