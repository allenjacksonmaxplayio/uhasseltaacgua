#include "Start.h"

namespace HovUni {

Start::Start( TiXmlElement * data )
{
	//We are loading a Start!
	if(strcmp(data->Value(),"Start") != 0){
		throw ParseException();
	}
}

Start::~Start(void)
{
}

}
