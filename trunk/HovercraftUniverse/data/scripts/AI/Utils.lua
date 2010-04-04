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
function project2(point, p0, p1)
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

--[[
-- Projects a point onto a line segment.
-- More efficient than project2.
-- @param	point	Vector3	The point
-- @param	p1		Vector3 The start of the line segment
-- @param	p2		Vector3 The end of the line segment
-- @return			Vector3	The point, colinear with and situated
							inside p1 and p2 (endpoints inclusive),
							with the closest distance to point.
--]]
function project(point, p1, p2)
	local diff = point-p1;
    local dir = p2-p1;
    local dot1 = diff:dotProduct(dir);
    if (dot1 <= 0) then
        return p1;
    end
    local dot2 = dir:dotProduct(dir);
    if (dot2 <= dot1) then
        return p2;
    end
    local t = dot1/dot2;
    return p1 + (dir * t);
end

--lerp functions
function normalize(value, minimum, maximum)
	return (value - minimum) / (maximum - minimum);
end

function interpolate(normValue, minimum, maximum)
	return minimum + (maximum - minimum) * normValue;
end

function map(value, min1, max1, min2, max2)
	return interpolate(normalize(value, min1, max1), min2, max2);
end

