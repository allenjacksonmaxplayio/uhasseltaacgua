--[[
--	Simple AI test
--	@author Dirk Delahaye
--]]

dofile(BASE_PATH .. "Constants.lua");

-----------------------------
-- STATE Constants
-----------------------------
ST_IDLE 	=	0;
ST_MOVING 	=	1;
-----------------------------
mCurrentState = 0;

function registerController(controllerObj)
	mControllerObj = controllerObj;
end

function decide()
	if (mCurrentState == ST_IDLE) then
		mControllerObj.startAction(mControllerObj, ACCELERATE);
		mCurrentState = ST_MOVING;
	end
	return 1
end
