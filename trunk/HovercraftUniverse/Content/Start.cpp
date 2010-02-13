#include "Start.h"

namespace HovUni {

Start::Start( TiXmlElement * data )
{
	//We are loading a Start!
	assert(strcmp(data->Value(),"Start") == 0);	
}

Start::~Start(void)
{
}

}
