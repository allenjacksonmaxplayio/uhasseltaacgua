#include "Start.h"

namespace HovUni {

Start::Start( TiXmlElement * data )
{
	//We are loading a Start!
	assert(strcmp(data->GetText(),"Start") == 0);	
}

Start::~Start(void)
{
}

}
