--Vector3.lua


local Vector3 = {x = 0, y = 0, z = 0}

function Vector3:new(x, y, z)
    c = {}
    self.__index = self
    
    setmetatable(c, self)

    c.x = x 
    c.y = y 
    c.z = z

    return c
end

function Vector3:insert(x, y, z)
    self.x = x
    self.y = y
    self.z = z
end

function Vector3:sub(rightVec)
    local vec = Vector3:new()

    vec.x = self.x - rightVec.x
    vec.y = self.y - rightVec.y
    vec.z = self.z - rightVec.z
    
    return vec
end

function Vector3:normalize()
    local length = math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)
    local vec = Vector3:new()
    vec.x = self.x / length
    vec.y = self.y / length
    vec.z = self.z / length
    return vec
end

function Vector3:length()
    local length = math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)
    return length
end

function Vector3:dot(rightVec)
    if getmetatable(rightVec) == self then
        print("NOT THE CLASS")
        return 0
    end
    local dotProd = (rightVec.x * self.x) + (rightVec.y * self.y) + (rightVec.z * self.z)
    return dotProd
end

return Vector3