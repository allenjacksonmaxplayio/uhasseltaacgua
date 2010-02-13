#include "Finish.h"

namespace HovUni {

Finish::Finish( TiXmlElement * data )
{
	//We are loading a Finish!
	assert(strcmp(data->Value(),"Finish") == 0);	
}

Finish::~Finish(void)
{
}

}
