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
	local scalar = (p1-p0):dotProduct(point-p0)
	scalar = scalar / (p1-p0):length();
	return p0 + ((p1-p0) * scalar);
end
