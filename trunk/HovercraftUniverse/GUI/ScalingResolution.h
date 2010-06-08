#ifndef _SCALINGRESOLUTION_H
#define _SCALINGRESOLUTION_H

#include "IResolution.h"

namespace HovUni {
	/**
	 * Class that represents a scaling resolution. This resolution will scale
	 * according to any parent resolution.
	 *
	 * @author Nickman
	 */
	class ScalingResolution : public IResolution {
		private:
			/** The minimum resolution we want */
			IResolution* mMinResolution;
			/** The maximum resolution we want */
			IResolution* mMaxResolution;

			/** The maximum screen resolution at which we want the minimum resolution */
			IResolution* mMinScreenResolution;
			/** The minimum screen resolution at which we want the maximum resolution */
			IResolution* mMaxScreenResolution;

		public:
			/**
			 * Constructor for a scaling resolution.
			 * 
			 * @param minResolution The minimum resolution we want to have.
			 * @param minScreenResolution The minimum resolution at which we want to start using the
			 *		minResolution values.
			 * @parem maxResolution The maximum resolution we want to have.
			 * @param maxScreenResolution The maximum resolution at which we want to start using the
			 *		maxResolution values.
			 */
			ScalingResolution(IResolution* minResolution, IResolution* minScreenResolution, IResolution* maxResolution, IResolution* maxScreenResolution);

			/**
			 * Constructor for a scaling resolution without a minimum and maximum resolution.
			 *
			 * @param resolution The resolution that the object should have at the given
			 *		screen resolution
			 * @param screenResolution The screen resolution that is linked to the given
			 *		resolution and will be used to scale the result.
			 */
			ScalingResolution(IResolution* resolution, IResolution* screenResolution);

			/**
			 * A scaling resolution is never relative so this function always returns false.
			 *
			 * @return False because scaling widths are never relative.
			 */
			virtual inline bool isWidthRelative() { return false; }

			/**
			 * Get the width of this resultion, scaled to the parent resolution.
			 * Make sure the parent resolution is set, otherwise this call will throw
			 * a NoParentResolutionException exception.
			 *
			 * @return The scaled width of this resolution
			 * @throws NoParentResolutionException will be thrown if the parent resolution
			 *		was not set.
			 */
			virtual int getWidth();

			/**
			 * A scaling resolution is never relative so this function always returns false.
			 *
			 * @return False because scaling heights are never relative.
			 */
			virtual inline bool isHeightRelative() { return false; }
			
			/**
			 * Get the height of this resultion, scaled to the parent resolution.
			 * Make sure the parent resolution is set, otherwise this call will throw
			 * a NoParentResolutionException exception.
			 *
			 * @return The scaled height of this resolution
			 * @throws NoParentResolutionException will be thrown if the parent resolution
			 *		was not set.
			 */
			virtual int getHeight();
	};
}

#endif //_SCALINGRESOLUTION_H