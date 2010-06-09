#include "ScalingResolution.h"

namespace HovUni {

ScalingResolution::ScalingResolution(IResolution* minResolution, IResolution* minScreenResolution, IResolution* maxResolution, IResolution* maxScreenResolution) 
	: IResolution(), mMinResolution(minResolution), mMaxResolution(maxResolution), mMinScreenResolution(minScreenResolution), mMaxScreenResolution(maxScreenResolution) {

}

ScalingResolution::ScalingResolution(IResolution* resolution, IResolution* screenResolution) 
	: IResolution(), mMinResolution(resolution), mMaxResolution(0), mMinScreenResolution(screenResolution), mMaxScreenResolution(0) {

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

int ScalingResolution::calculateDimension(int minSize, int minScreen, bool relSize, int parentSize, int maxSize, int maxScreen) {
	//Some variables
	int result;
	float scale = 0;

	//Calculate the result
	if ((maxSize == -1) || (maxScreen == -1)) {
		//We are scaling around a single dimension
		scale = calculateScale(0, minScreen, parentSize, false);

		float tmpResult = minSize * scale;

		if (relSize) {
			//tmpResult now contains a percentage, calculate the real value
			result = (int) ((tmpResult / 100.0f) * parentSize);
		} else {
			result = (int) tmpResult;
		}
	} else {
		if (!mPreserverAspectRatio) {
			if (parentSize <= minScreen) {
				//We want the minimum size
				scale = 0.0f;
			} else if (parentSize >= maxScreen) {
				//We need to take the maximum size
				scale = 1.0f;
			} else {
				scale = calculateScale(minSize, maxSize, parentSize);
			}
		} else {
			scale = getARScale();
		}

		//Scale the result
		float tmpResult = scaleValue((float) minSize, (float) maxSize, scale);

		if (relSize) {
			//tmpResult now contains a percentage, calculate the real value
			result = (int) ((tmpResult / 100.0f) * parentSize);
		} else {
			result = (int) tmpResult;
		}
	}

	return result;
}

float ScalingResolution::calculateScale(int min, int max, int curr, bool normalize) {
	float scale = ((float)(curr - min) / (float)(max - min));

	if (normalize) {
		if (scale < 0.0f) scale = 0.0f;
		if (scale > 1.0f) scale = 1.0f;
	}

	return scale;
}

float ScalingResolution::scaleValue(float minValue, float maxValue, float scale) {
	return (minValue + scale * (maxValue - minValue));
}

float ScalingResolution::getARScale() {
	//Calculate a scale for both the width and height to preserve the aspect ratio
	float scaleX = calculateScale(mMinResolution->getWidth(), mMaxResolution->getWidth(), mParentResolution->getWidth());
	float scaleY = calculateScale(mMinResolution->getHeight(), mMaxResolution->getHeight(), mParentResolution->getHeight());
	//Return the smallest of both scales
	return (scaleX < scaleY) ? scaleX : scaleY;
}

}