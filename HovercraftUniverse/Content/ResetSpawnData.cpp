#include "ResetSpawnData.h"
#include <OgreStringConverter.h>

namespace HovUni {

ResetSpawnData::ResetSpawnData( TiXmlElement * data ) throw (ParseException)
{
	TiXmlNode * node;

	//We are loading a Finish!
	if(strcmp(data->Value(),"ResetSpawn") != 0){
		throw ParseException();
	}	
}

ResetSpawnData::~ResetSpawnData(void)
{
}

}
