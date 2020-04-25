--Character.lua
local Character = {}
function Character:new(c)
    c = c or {}
    self.__index = self
    return setmetatable(c, self)
end

function Character:move(x, y, z)
    self.pos[1] = self.pos[1] + x
    self.pos[2] = self.pos[2] + y
    self.pos[3] = self.pos[3] + z
end

function Character:getX()
    return self.pos[1]
end


return Character