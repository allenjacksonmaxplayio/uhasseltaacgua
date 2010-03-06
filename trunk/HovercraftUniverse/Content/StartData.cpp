#include "StartData.h"

namespace HovUni {

StartData::StartData( TiXmlElement * data )
{
	//We are loading a Start!
	if(strcmp(data->Value(),"Start") != 0){
		throw ParseException();
	}
}

StartData::~StartData(void)
{
}

}
