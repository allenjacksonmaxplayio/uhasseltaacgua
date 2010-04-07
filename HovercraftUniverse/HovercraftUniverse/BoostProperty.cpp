#include "BoostProperty.h"

namespace HovUni {

EntityPropertyTag<BoostProperty,1> BoostProperty::tag;

BoostProperty::BoostProperty():
	EntityProperty(tag.getID()){
}

BoostProperty::BoostProperty(int id):
	EntityProperty(id)
{
}

BoostProperty::~BoostProperty(void)
{
}


void BoostProperty::write(ZCom_BitStream& bitstream) const{
	bitstream.addFloat(mBoost,4);
	bitstream.addFloat(mGain,4);
	bitstream.addFloat(mDirection[0],4);
	bitstream.addFloat(mDirection[1],4);
	bitstream.addFloat(mDirection[2],4);
}

void BoostProperty::read(ZCom_BitStream& bitstream) {
	mBoost = bitstream.getFloat(4);
	mGain = bitstream.getFloat(4);
	mDirection[0] = bitstream.getFloat(4);
	mDirection[1] = bitstream.getFloat(4);
	mDirection[2] = bitstream.getFloat(4);
}

}
