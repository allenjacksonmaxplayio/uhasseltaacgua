#include "PowerupSpawn.h"

namespace HovUni {

PowerupSpawn::PowerupSpawn( TiXmlElement * data)
{
	//We are loading a CheckPoint!
	assert(strcmp(data->Value(),"PowerupSpawn") == 0);	
}

PowerupSpawn::~PowerupSpawn(void)
{
}

}
