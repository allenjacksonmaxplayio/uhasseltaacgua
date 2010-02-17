#include "Finish.h"

namespace HovUni {

Finish::Finish( TiXmlElement * data ) throw (ParseException)
{
	//We are loading a Finish!
	if(strcmp(data->Value(),"Finish") != 0){
		throw ParseException();
	}	
}

Finish::~Finish(void)
{
}

}
