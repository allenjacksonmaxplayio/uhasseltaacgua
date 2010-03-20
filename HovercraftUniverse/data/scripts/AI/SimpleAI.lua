--[[
--	Simple AI test
--	@author Dirk Delahaye
--]]
AI_NAME = "Simple AI";

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
mEntity = 0
mInitialPosition = 0
--HovercraftAIController game

function registerController(controllerObj)
	game = controllerObj;
end

function println(msg)
	game:luaLog(AI_NAME .. " :: " .. msg);
end

function setEntity(entity)
	if (mEntity == 0) then
		mInitialPosition = entity:getPosition();
	end
	mEntity = entity;
end

function setTarget(entity)
	mTarget = entity;
end

epsilon = 0.01; --epsilon for avoiding oscillations

--[[
--	Main function
--	Preliminary, pseudostateless AI
--]]
function decide()
	--Poll Position
	position = mEntity:getPosition();
	--println("");
	println("Position: " .. position.x .. ", " .. position.y .. ", " .. position.z);
	targetPosition = mTarget:getPosition();
	println("Target: " .. targetPosition.x .. ", " .. targetPosition.y .. ", " .. targetPosition.z);
	--Calculate orientation
	targetOrientation = targetPosition - position;
	targetOrientation = targetOrientation:normalisedCopy();
	--println("targetOrientation: " .. targetOrientation.x .. ", " .. targetOrientation.y .. ", " .. targetOrientation.z);
	myOrientation = mEntity:getOrientation();
	--println("myOrientation: " .. myOrientation.x .. ", " .. myOrientation.y .. ", " .. myOrientation.z);
	side = myOrientation:crossProduct(mEntity:getUpVector());
	side = side:dotProduct(targetOrientation);
	--println("side = " .. side);

	--deltaOrientation is the unit vector telling us which way to go, from our current direction.
	--note: working with coordinates (z, x)!!!!
	if (position:distance(targetPosition) > 20) then
		game:setAction(ACCELERATE, true);
		if (side > epsilon) then
			game:setAction(TURNLEFT, false);
			game:setAction(TURNRIGHT, true);
		elseif (side < -epsilon) then
			game:setAction(TURNRIGHT, false);
			game:setAction(TURNLEFT, true);
		else
			game:setAction(TURNRIGHT, false);
			game:setAction(TURNLEFT, false);
		end
	else
		game:setAction(ACCELERATE, false);
	end

	return 0;
end
