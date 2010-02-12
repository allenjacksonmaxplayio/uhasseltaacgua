#include "Finish.h"

namespace HovUni {

namespace Content {

Finish::Finish( TiXmlElement * data )
{
	//We are loading a Finish!
	assert(strcmp(data->GetText(),"Finish") == 0);	
}

Finish::~Finish(void)
{
}

}

}
