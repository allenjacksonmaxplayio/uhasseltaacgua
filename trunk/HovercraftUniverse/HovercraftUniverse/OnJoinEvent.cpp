#include "OnJoinEvent.h"
#include "GameEventType.h"

namespace HovUni {


OnJoinEvent::OnJoinEvent( ZCom_ConnID connectionid ):
	GameEvent(onJoin), mConnectionId(connectionid)
{
}

OnJoinEvent::OnJoinEvent(void):
	GameEvent(onJoin)
{
}

OnJoinEvent::~OnJoinEvent(void)
{
}

void OnJoinEvent::write(ZCom_BitStream* stream) const
{
	stream->addInt(mConnectionId,sizeof(mConnectionId) * 8);
}

void OnJoinEvent::read(ZCom_BitStream* stream)
{
	mConnectionId = stream->getInt(sizeof(mConnectionId) * 8);
}

OnJoinEvent * OnJoinEvent::parse(ZCom_BitStream* stream)
{
	OnJoinEvent * result = new OnJoinEvent();
	result->deserialize( stream );
	return result;
}

}
