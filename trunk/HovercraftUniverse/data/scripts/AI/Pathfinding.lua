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
PATH_RADIUS = 80;
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

epsilon = 0.01; --epsilon for avoiding oscillations

function toString(v)
	return "(" .. v.x .. ", " .. v.y .. ", " .. v.z .. ")";
end

--[[
--	Main function
--	Preliminary, pseudostateless AI
--]]
function decide()
	--position = global because we want to retain this to calculate deltaPosition.
	if (position == nil) then
		position = mEntity:getPosition();
	end
	local velocity = mEntity:getPosition() - position; --TODO use mEntity:getVelocity() but not yet synchronized atm
	position = mEntity:getPosition();--Vector3
	println("Position: " .. toString(position));
	println("Velocity: " .. toString(velocity));
	

	--############################### PATH FINDING
	local probe = position + (velocity * PATH_PROBELENGTH);
	println("Probe: " .. toString(probe));
	-- TODO hardcoded path
	local path = {Vector3(-50, 0, 100), Vector3(0, 0, 50), Vector3(50, 0, 0)};
	--LUA TABLES START AT INDEX 1
	local distanceToPath = math.huge; --math.huge = +infinity
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
	distanceToPath = position:distance(project);
	println("Closest path lies between " .. toString(p0) .. " and " .. toString(p1) .. ",projected point ".. toString(project) .." at " .. distanceToPath .. " units distance from probe.");
	local targetPosition;
	if (distanceToPath > PATH_RADIUS) then
		--Seek the path
		println("Seeking " .. toString(project));
		targetPosition = project;
	else
		--No corrective steering required. Force this by setting target to the predicted position.
		println("No corrective steering required. Seeking " .. toString(probe));
		targetPosition = probe;
	end

	--################################## END PATH FINDING


	--println("");
	
	println("Target: " .. toString(targetPosition));
	--Calculate orientation
	targetOrientation = targetPosition - position;
	targetOrientation:normalise();
	--println("targetOrientation: " .. targetOrientation.x .. ", " .. targetOrientation.y .. ", " .. targetOrientation.z);
	local myOrientation = mEntity:getOrientation();
	--println("myOrientation: " .. myOrientation.x .. ", " .. myOrientation.y .. ", " .. myOrientation.z);
	local side = myOrientation:crossProduct(mEntity:getUpVector());
	side = side:dotProduct(targetOrientation);
	--println("side = " .. side);

	--deltaOrientation is the unit vector telling us which way to go, from our current direction.
	if (position:distance(targetPosition) > 20) then
		game:setAction(ACCELERATE, true);
		if (side > epsilon) then
			println("Turning Right");
			game:setAction(TURNLEFT, false);
			game:setAction(TURNRIGHT, true);
		elseif (side < -epsilon) then
			println("Turning Left");
			game:setAction(TURNRIGHT, false);
			game:setAction(TURNLEFT, true);
		else
			println("Going Straight");
			game:setAction(TURNRIGHT, false);
			game:setAction(TURNLEFT, false);
		end
	else
		game:setAction(ACCELERATE, false);
	end

	return 0;
end
