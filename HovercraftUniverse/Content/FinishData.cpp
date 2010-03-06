#include "FinishData.h"

namespace HovUni {

FinishData::FinishData( TiXmlElement * data ) throw (ParseException)
{
	//We are loading a Finish!
	if(strcmp(data->Value(),"Finish") != 0){
		throw ParseException();
	}	
}

FinishData::~FinishData(void)
{
}

}
