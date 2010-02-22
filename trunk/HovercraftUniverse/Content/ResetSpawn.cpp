#include "ResetSpawn.h"
#include <OgreStringConverter.h>

namespace HovUni {

ResetSpawn::ResetSpawn( TiXmlElement * data ) throw (ParseException)
{
	TiXmlNode * node;

	//We are loading a Finish!
	if(strcmp(data->Value(),"ResetSpawn") != 0){
		throw ParseException();
	}	
}

ResetSpawn::~ResetSpawn(void)
{
}

}
