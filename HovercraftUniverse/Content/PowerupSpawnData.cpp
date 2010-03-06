#include "PowerupSpawnData.h"

namespace HovUni {

PowerupSpawnData::PowerupSpawnData( TiXmlElement * data) throw (ParseException)
{
	//We are loading a CheckPoint!
	if(strcmp(data->Value(),"PowerupSpawn") != 0){
		throw ParseException();
	}
}

PowerupSpawnData::~PowerupSpawnData(void)
{
}

}
