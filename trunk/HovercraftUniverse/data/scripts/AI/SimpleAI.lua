--[[
--	Simple AI test
--	@author Dirk Delahaye
--]]
AI_NAME = "Simple AI";

--[[
	Values and functions received from game:

	/** Start an action (press a button) */
	void startAction(ControllerActionType action);

	/** Stop an action (release a button) */
	void stopAction(ControllerActionType action);


]]
-----------------------------
-- Control enum Constants
-- TODO control via enum
-----------------------------
ACCELERATE	=	1;
BRAKE		=	2;
TURNLEFT	=	3;
TURNRIGHT	=	4;
-----------------------------


-----------------------------
-- STATE Constants
-----------------------------
ST_IDLE 	=	0;
ST_MOVING 	=	1;
-----------------------------
mCurrentState = 0;
mPosition = 0
mInitialPosition = 0
--HovercraftAIController game


--Current button state
mACCELERATE	=	false;
mBRAKE		=	false;
mTURNLEFT	=	false;
mTURNRIGHT	=	false;

function registerController(controllerObj)
	game = controllerObj;
end

function println(msg)
	game:luaLog(AI_NAME .. " :: " .. msg);
end

function setPosition(pos)
	if (mPosition == 0) then
		mInitialPosition = pos;
	end
	mPosition = pos;
end

threshold = 300;

--[[
--	Main function
--	All very hardcoded and just for testing purposes!
--]]
function decide()
	--println("Position: " .. mPosition.x .. ", " .. mPosition.y .. ", " .. mPosition.z);
	if (mCurrentState == ST_IDLE) then
		game:startAction(ACCELERATE);
		mACCELERATE = true;
		mCurrentState = ST_MOVING;
	elseif (mCurrentState == ST_MOVING) then
		distance = mPosition:distance(mInitialPosition);
		--println("Current distance from starting point = " .. distance);
		if (distance > threshold) then
			if (mACCELERATE) then
				--stop
				game:stopAction(ACCELERATE);
				mACCELERATE = false;
				game:stopAction(TURNLEFT);
				mTURNLEFT = false;
				--start
				game:startAction(BRAKE);
				mBRAKE = true;
				game:startAction(TURNRIGHT);
				mTURNRIGHT = true;
			elseif (mBRAKE) then
				--stop
				game:stopAction(BRAKE);
				mBRAKE = false;
				game:stopAction(TURNRIGHT);
				mTURNRIGHT = false;
				--start
				game:startAction(ACCELERATE);
				mACCELERATE = true;
				game:startAction(TURNLEFT);
				mTURNLEFT = true;
			end
		end
	end


	return 0;
end
