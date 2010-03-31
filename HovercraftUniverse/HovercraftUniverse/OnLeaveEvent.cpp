#include "OnLeaveEvent.h"
#include "GameEventType.h"

namespace HovUni {

OnLeaveEvent::OnLeaveEvent( ZCom_ConnID connectionid ):
	GameEvent(onLeave), mConnectionId(connectionid)
{
}

OnLeaveEvent::OnLeaveEvent(void):
	GameEvent(onLeave)
{
}

OnLeaveEvent::~OnLeaveEvent(void)
{
}

void OnLeaveEvent::write(ZCom_BitStream* stream) const
{
	stream->addInt(mConnectionId,sizeof(mConnectionId) * 8);
}

void OnLeaveEvent::read(ZCom_BitStream* stream)
{
	mConnectionId = stream->getInt(sizeof(mConnectionId) * 8);
}

OnLeaveEvent * OnLeaveEvent::parse(ZCom_BitStream* stream)
{
	OnLeaveEvent * result = new OnLeaveEvent();
	result->deserialize( stream );
	return result;
}

}
