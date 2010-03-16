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

threshold = 0.01; --epsilon for avoiding oscillations

--[[
--	Main function
--	Preliminary, pseudostateless AI
--]]
function decide()
	--Poll Position
	position = mEntity:getPosition();
	println("\nPosition: " .. position.x .. ", " .. position.y .. ", " .. position.z);
	targetPosition = Vector3(200.0, 40.0, 500.0);

	--Calculate orientation
	targetOrientation = targetPosition - position;
	targetOrientation = targetOrientation:normalisedCopy();
	println("targetOrientation: " .. targetOrientation.x .. ", " .. targetOrientation.y .. ", " .. targetOrientation.z);
	myOrientation = mEntity:getOrientation();
	println("myOrientation: " .. myOrientation.x .. ", " .. myOrientation.y .. ", " .. myOrientation.z);
	deltaOrientation = targetOrientation - myOrientation;
	println("deltaOrientation: " .. deltaOrientation.x .. ", " .. deltaOrientation.y .. ", " .. deltaOrientation.z);
	println("deltaOrientation length = " .. deltaOrientation:length());
	println("Distance to target = " .. position:distance(targetPosition));

	--deltaOrientation is the unit vector telling us which way to go, from our current direction.
	--note: working with coordinates (z, x)!!!!
	if (position:distance(targetPosition) > 20) then
		game:setAction(ACCELERATE, true);

		if (deltaOrientation:length() > 0.05) then
			--Check if the target is not "behind" us, ie. in quadrants III and IV
			if (deltaOrientation.x < -threshold) then
				println("###########Target is behind us");
				if (deltaOrientation.z > threshold) then
					println("###########Behind me, turning right");
					game:setAction(TURNLEFT, false);
					game:setAction(TURNRIGHT, true);
				elseif (deltaOrientation.z < -threshold) then
					println("###########Behind me, turning left");
					game:setAction(TURNRIGHT, false);
					game:setAction(TURNLEFT, true);
				else--if ((deltaOrientation.z < threshold) and (deltaOrientation.z > -threshold)) then --z == 0
					--FORCE right hand turn
					println("###########FORCING RIGHT HAND TURN");
					game:setAction(TURNLEFT, false);
					game:setAction(TURNRIGHT, true);
				end
			else
				println("###########Target is in front of us");
				if (deltaOrientation.z > threshold) then
					println("###########In front of me, turning right");
					game:setAction(TURNLEFT, false);
					game:setAction(TURNRIGHT, true);
				elseif (deltaOrientation.z < -threshold) then
					println("###########In front of me, turning left");
					game:setAction(TURNRIGHT, false);
					game:setAction(TURNLEFT, true);
				else --(deltaOrientation.z < threshold) and (deltaOrientation.z > -threshold) then --z == 0
					println("########### Z == 0, going straight on");
					game:setAction(TURNRIGHT, false);
					game:setAction(TURNLEFT, false);
				end
			end
		else
			println("###########length < threshold, cancel turn.");
			game:setAction(TURNLEFT, false);
			game:setAction(TURNRIGHT, false);
		end
	else
		game:setAction(ACCELERATE, false);
	end

	return 0;
end
