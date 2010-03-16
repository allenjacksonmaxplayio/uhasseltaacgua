namespace HovUni {

template <typename EventType, unsigned N>
NetworkEvent<EventType, N>::NetworkEvent(EventType type) : mType(type) {

}

template <typename EventType, unsigned N>
NetworkEvent<EventType, N>::~NetworkEvent() {

}

template <typename EventType, unsigned N>
EventType NetworkEvent<EventType, N>::getType() const {
	return mType;
}

template <typename EventType, unsigned N>
void NetworkEvent<EventType, N>::serialize(ZCom_BitStream* stream) const {
	// Write the type of the event
	if (N != 0) {
		stream->addInt((int) mType, N);
	} else {
		stream->addInt((int) mType, 1);
	}

	// Write the data of the event
	write(stream);
}

template <typename EventType, unsigned N>
void NetworkEvent<EventType, N>::deserialize(ZCom_BitStream* stream) {
	// Read the type of the event
	if (N != 0) {
		mType = (EventType) (int) stream->getInt(N);
	} else {
		mType = (EventType) (int) stream->getInt(1);
	}

	// Read the data of the event
	read(stream);
}

template <typename EventType, unsigned N>
EventType NetworkEvent<EventType, N>::readType(ZCom_BitStream* stream) {
	ZCom_BitStream::BitPos pos;
	stream->saveReadState(pos);
	EventType t;
	if (N != 0) {
		t = (EventType) (int) stream->getInt(N);
	} else {
		t = (EventType) (int) stream->getInt(1);
	}
	stream->restoreReadState(pos);
	return t;
}

}
