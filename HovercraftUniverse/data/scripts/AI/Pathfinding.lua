--[[
--	Pathfinding AI
--	@author Dirk Delahaye, 23/03/2010
--]]
AI_NAME = "Pathfinding AI";
dofile("scripts/AI/Utils.lua");

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




-----------------------------
-- Pathfinding Constants
-----------------------------
PATH_PROBELENGTH = 50;
PATH_RADIUS = 40;
-----------------------------





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

function toString(v)
	return "(" .. v.x .. ", " .. v.y .. ", " .. v.z .. ")";
end

--[[
--	Main function
--	Preliminary, pseudostateless AI
--]]
function decide()
	local position;
	if (position == nil) then
		position = mEntity:getPosition();
	end
	local velocity = mEntity:getPosition() - position;
	position = mEntity:getPosition();--Vector3


	--############################### PATH FINDING
	local probe = velocity * PATH_PROBELENGTH;
	-- TODO hardcoded path
	local path = {Vector3(-90, 0, -10), Vector3(0, 0, 0), Vector3(50, 0, 0)};
	--LUA TABLES START AT INDEX 1
	local distanceToPath = math.huge;
	local pathIndex = 0;
	for key,value in pairs(path) do
		if (key ~= 1) then
			local p0 = path[key-1];
			local p1 = path[key];
			local project = project(probe, p0, p1);
			if (position:distance(project) < distanceToPath) then
				distanceToPath = position:distance(project);
				pathIndex = key;
			end
		end
	end

	local p0 = path[pathIndex-1];
	local p1 = path[pathIndex];
	local project = project(probe, p0, p1);
	local distanceToPath = position:distance(project);
	println("Closest path lies between " .. toString(p0) .. " and " .. toString(p1) .. ", at " .. distanceToPath .. " units distance.");

	--################################## END PATH FINDING


	--println("");
	println("Position: " .. position.x .. ", " .. position.y .. ", " .. position.z);
	local targetPosition = mTarget:getPosition();
	println("Target: " .. targetPosition.x .. ", " .. targetPosition.y .. ", " .. targetPosition.z);
	--Calculate orientation
	targetOrientation = targetPosition - position;
	targetOrientation = targetOrientation:normalisedCopy();
	--println("targetOrientation: " .. targetOrientation.x .. ", " .. targetOrientation.y .. ", " .. targetOrientation.z);
	local myOrientation = mEntity:getOrientation();
	--println("myOrientation: " .. myOrientation.x .. ", " .. myOrientation.y .. ", " .. myOrientation.z);
	local side = myOrientation:crossProduct(mEntity:getUpVector());
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
