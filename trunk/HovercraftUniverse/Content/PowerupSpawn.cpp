#include "PowerupSpawn.h"

namespace HovUni {

PowerupSpawn::PowerupSpawn( TiXmlElement * data) throw (ParseException)
{
	//We are loading a CheckPoint!
	if(strcmp(data->Value(),"PowerupSpawn") != 0){
		throw ParseException();
	}
}

PowerupSpawn::~PowerupSpawn(void)
{
}

}
