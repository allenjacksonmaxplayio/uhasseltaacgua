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
-- STATE Constants
-----------------------------
ST_IDLE 	=	0;
ST_MOVING 	=	1;
-----------------------------
mCurrentState = 0;

function registerController(controllerObj)
	game = controllerObj;
end

function println(msg)
	game:luaLog(AI_NAME .. " :: " .. msg);
end


function decide()
	--println("AI Deciding"); --too much output :p
	if (mCurrentState == ST_IDLE) then
		game:startAction(ACCELERATE);
		game:startAction(TURNLEFT);
		mCurrentState = ST_MOVING;
	end
	return 0;
end
