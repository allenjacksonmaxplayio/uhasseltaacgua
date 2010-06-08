#ifndef _RESOLUTION_H
#define _RESOLUTION_H

#include "IResolution.h"

namespace HovUni {
	/**
	 * Class that represents a basic resolution. the resolution can either contain fixed
	 * values (in number of pixels) or relative values (in percentages [0 - 100]).
	 *
	 * @author Nickman
	 */
	class Resolution : public IResolution {
		private:
			/** The width */
			int mWidth;

			/** The height */
			int mHeight;

			/** Mark the width as relative */
			bool mRelativeWidth;

			/** Mark the height as relative */
			bool mRelativeHeight;

		public:
			Resolution(int width, int height, bool relWidth = false, bool relHeight = false) 
				: mWidth(width), mHeight(height), mRelativeWidth(relWidth), mRelativeHeight(relHeight) {
			}

			virtual inline bool isWidthRelative() { return mRelativeWidth; }

			virtual inline int getWidth() { return mWidth; }

			virtual inline bool isHeightRelative() { return mRelativeHeight; }
			
			virtual inline int getHeight() { return mHeight; }
	};
}

#endif //_RESOLUTION_H