--[[
--	Utilities
--	@author Dirk Delahaye, 23/03/2010
--]]


--[[
--	Projects a point onto a line segment.
-- @param	point	Vector3	The point
-- @param	p0		Vector3 The start of the line segment
-- @param	p1		Vector3 The end of the line segment
-- @return			Vector3	The point, colinear with and situated inside p0 and p1, with the closest distance to point.
--]]
function project(point, p0, p1)
	--TODO Optimize (save the divide)
	local diff = point - p0;
	local dir = p1 - p0;
	local t = diff:dotProduct(dir) / dir:dotProduct(dir);
	if (t <= 0) then
		return p0;
	elseif (t >= 1) then
		return p1;
	else
		return p0 + (dir * t);
	end
end
