#include "ScalingResolution.h"

namespace HovUni {

ScalingResolution::ScalingResolution(IResolution* minResolution, IResolution* minScreenResolution, IResolution* maxResolution, IResolution* maxScreenResolution) 
	: mMinResolution(minResolution), mMaxResolution(maxResolution), mMinScreenResolution(minScreenResolution), mMaxScreenResolution(maxScreenResolution) {

}

ScalingResolution::ScalingResolution(IResolution* resolution, IResolution* screenResolution) 
	: mMinResolution(resolution), mMaxResolution(0), mMinScreenResolution(screenResolution), mMaxScreenResolution(0) {

}

int ScalingResolution::getWidth() {
	//Is the parent resolution set?
	if (mParentResolution == 0) {
		THROW(NoParentResolutionException, "A scaled resolution can only be calculated if the parent resolution is set");
	}

	//Calculate the scaled width

	return 1;
}

int ScalingResolution::getHeight() {
	//Is the parent resolution set?
	if (mParentResolution == 0) {
		THROW(NoParentResolutionException, "A scaled resolution can only be calculated if the parent resolution is set");
	}

	//Calculate the scaled height

	return 1;
}

}