--[[
--	Pathfinding AI
--	@author Dirk Delahaye, 23/03/2010
--
-- TODO:
-- (24/03/2010): Implement "arrival" behaviour.
-- (24/03/2010): flatten function: project against a plane in the orientation of our entity, instead of just projcting against (X, Z)
--]]
AI_NAME = "PathAI"; --Not too long, this appears in every logline
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
PATH_PROBELENGTH = 1;
PATH_RADIUS = 5;
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

--[[
-- Sets the path.
-- @param path A table of Entity objects.
-- @return void
--]]
function setPath(path)
	mPath = path;
end

function toString(v)
	return "(" .. v.x .. ", " .. v.y .. ", " .. v.z .. ")";
end

--[[
--	Main function
--	Preliminary, pseudostateless AI
--]]
function decide()
	local position = mEntity:getPosition();--Vector3
	local velocity = mEntity:getVelocity();
	position.y = 0;
	velocity.y = 0;
	--println("Position: " .. toString(position));
	--println("Velocity: " .. toString(velocity));


	--############################### PATH FINDING
	local probe = position + (velocity * PATH_PROBELENGTH);
	--println("Probe: " .. toString(probe));
	--LUA TABLES START AT INDEX 1
	local distanceToPath = math.huge; --math.huge = +infinity
	local pathIndex = 0;
	for key,value in pairs(mPath) do
		if (key ~= 1) then
			--they are Entities.
			local p0 = mPath[key-1]:getPosition();
			local p1 = mPath[key]:getPosition();
			p0.y = 0;
			p1.y = 0;
			local project = project(probe, p0, p1);
			if (position:distance(project) < distanceToPath) then
				distanceToPath = position:distance(project);
				pathIndex = key;
			end
		end
	end

	local p0 = mPath[pathIndex-1]:getPosition();
	local p1 = mPath[pathIndex]:getPosition();
	p0.y = 0;
	p1.y = 0;
	local project = project(probe, p0, p1);
	distanceToPath = probe:distance(project);
	--println("Closest pathline lies between " .. toString(p0) .. " and " .. toString(p1));
	--println("projected point ".. toString(project) .." at " .. distanceToPath .. " units distance from probe.");
	--println("Closest pathline is segment[" .. (pathIndex-1) .. "->" .. pathIndex .. ", at " .. distanceToPath .. " units distance from PROBE.");
	local targetPosition;
	local distanceThreshold = 2;
	if (distanceToPath > PATH_RADIUS) then
		--Probe is too far away, steer towards path.
		targetPosition = (p1 - project); --project: predicted position on the path, p1 = endpoint of closest pathline
	else
		--No corrective steering required.
		--println("No corrective steering required.");
		game:setAction(TURNRIGHT, false);
		game:setAction(TURNLEFT, false);
		if (position:distance(p1) > distanceThreshold) then
			game:setAction(ACCELERATE, true);
		else
			game:setAction(ACCELERATE, false);
		end
		return 0;
	end

	--################################## END PATH FINDING

	--println("Target: " .. toString(targetPosition));
	targetOrientation = targetPosition - position;
	targetOrientation:normalise();
	local myOrientation = mEntity:getOrientation();
	local side = myOrientation:crossProduct(mEntity:getUpVector());
	side = side:dotProduct(targetOrientation);



	epsilon = 0.01; --epsilon for avoiding steering oscillations
	if (position:distance(targetPosition) > distanceThreshold) then
		game:setAction(ACCELERATE, true);
		if (side > epsilon) then
			--println("Turning Right");
			game:setAction(TURNLEFT, false);
			game:setAction(TURNRIGHT, true);
		elseif (side < -epsilon) then
			--println("Turning Left");
			game:setAction(TURNRIGHT, false);
			game:setAction(TURNLEFT, true);
		else
			--println("Going Straight");
			game:setAction(TURNRIGHT, false);
			game:setAction(TURNLEFT, false);
		end
	else
		game:setAction(ACCELERATE, false);
		game:setAction(TURNRIGHT, false);
		game:setAction(TURNLEFT, false);
	end

	return 0;
end
