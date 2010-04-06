--[[
--	Pathfinding AI
--	@author Dirk Delahaye, 23/03/2010
--
-- TODO:
-- (24/03/2010): Implement "arrival" behaviour.
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




-----------------------------
-- Pathfinding Constants
-----------------------------
PATH_PROBELENGTH = 1;
EPSILON = 0.01; -- for avoiding steering oscillations
-----------------------------





function registerController(controllerObj)
	game = controllerObj;
end

function println(msg)
	--game:luaLog(AI_NAME .. " :: " .. msg);
end

function setEntity(entity)
	mEntity = entity;
end

function toString(v)
	return "(" .. v.x .. ", " .. v.y .. ", " .. v.z .. ")";
end

--[[
-- Sets the path.
-- @param path A table of Entity objects.
-- @return void
--]]
function setPath(path)
	mPath = path;
	mPathSize = table.getn(mPath);
end


--[[
--	Main function
--	Preliminary, pseudostateless AI
--]]
function decide()
	local position = mEntity:getPosition();--Vector3
	local velocity = mEntity:getVelocity();
	--println("Position: " .. toString(position));
	--println("Velocity: " .. toString(velocity));

	--############################### COLLISION AVOIDANCE
	--if (mEntity:isInCollisionState()) then
	if (false) then
		local speed = mEntity:getSpeed();
		--println("Collision Avoidance! Braking and turning right! Speed is " .. speed);
		if (speed < 0) then
			--...
		else
			--Positive speed
			game:setAction(ACCELERATE, false);
			game:setAction(BRAKE, true);
			game:setAction(TURNLEFT, false);
			game:setAction(TURNRIGHT, true);
		end
		return 0;
	end
	--############################### END COLLISION AVOIDANCE


	--############################### PATH FINDING
	game:setAction(BRAKE, false);
	local probe = position + (velocity * PATH_PROBELENGTH);
	--println("Probe: " .. toString(probe));
	local distanceToPath = math.huge; --math.huge = +infinity
	local pathIndex = 0;
	for key,value in pairs(mPath) do
		if (key ~= 1) then
			local p0Vector4 = mPath[key-1];
			local p1Vector4 = mPath[key];

			local p0 = Vector3(p0Vector4.x, p0Vector4.y, p0Vector4.z);
			local p1 = Vector3(p1Vector4.x, p1Vector4.y, p1Vector4.z);

			println("Path[" .. key .. "]:" .. "p0V4=" .. toString(p0Vector4) .. "p1V4=" .. toString(p1Vector4) .. "p0=" .. toString(p0) .. "p1=" .. toString(p1) );

			local project = project(probe, p0, p1);
			if (position:distance(project) < distanceToPath) then
				distanceToPath = position:distance(project);
				pathIndex = key;
			end
		end
	end
	local p0Vector4 = mPath[pathIndex-1];
	local p1Vector4 = mPath[pathIndex];

	local p0 = Vector3(p0Vector4.x, p0Vector4.y, p0Vector4.z);
	local p1 = Vector3(p1Vector4.x, p1Vector4.y, p1Vector4.z);
	local project = project(probe, p0, p1);
	distanceToPath = probe:distance(project);
	println("At path " .. (pathIndex-1) .. " of " .. mPathSize);
	--println("Closest pathline lies between " .. toString(p0) .. " and " .. toString(p1));
	--println("projected point ".. toString(project) .." at " .. distanceToPath .. " units distance from probe.");
	--println("Closest pathline is segment[" .. (pathIndex-1) .. "->" .. pathIndex .. ", at " .. distanceToPath .. " units distance from PROBE.");
	local targetPosition;
	local distanceThreshold = 2;

	local lastV4 = mPath[mPathSize];
	local finish = Vector3(lastV4.x, lastV4.y, lastV4.z);


	if (distanceToPath > p0Vector4.w) then
		--Probe is too far away, steer towards path.
		--targetPosition = (p1 - project); --project: predicted position on the path, p1 = endpoint of closest pathline
		println("Steering towards path!");
		targetPosition = project;
	else
		--No corrective steering required.
		println("No corrective steering required.");
		game:setAction(TURNRIGHT, false);
		game:setAction(TURNLEFT, false);
		if (position:distance(finish) > distanceThreshold) then
			game:setAction(ACCELERATE, true);
		else
			game:setAction(ACCELERATE, false);
		end
		return 0;
	end










	println("Corrective steering required. Target: " .. toString(targetPosition));
	targetOrientation = targetPosition - position;
	targetOrientation:normalise();
	local myOrientation = mEntity:getOrientation();
	local side = myOrientation:crossProduct(mEntity:getUpVector());
	side = side:dotProduct(targetOrientation);

	if (position:distance(finish) > distanceThreshold) then --Arrival behaviour
		game:setAction(ACCELERATE, true);
		if (side > EPSILON) then
			--println("Turning Right");
			game:setAction(TURNLEFT, false);
			game:setAction(TURNRIGHT, true);
		elseif (side < -EPSILON) then
			--println("Turning Left");
			game:setAction(TURNRIGHT, false);
			game:setAction(TURNLEFT, true);
		else
			--println("Going Straight");
			game:setAction(TURNRIGHT, false);
			game:setAction(TURNLEFT, false);
		end
	else
		--todo arrival behaviour
		game:setAction(ACCELERATE, false);
		game:setAction(TURNRIGHT, false);
		game:setAction(TURNLEFT, false);
	end

	return 0;
end
