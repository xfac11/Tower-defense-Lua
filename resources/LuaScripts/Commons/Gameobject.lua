--Gameobject.lua
--Model is the name of the texture and mesh. example: tree.tga, tree.obj

--Drawindex is given when added to irrlicht in c++. 
--This index will be used for updating pos,rot,texture,model etc in c++
--Must be used for rendered objects
-- -1 means no object in irrlicht is added to be rendered for this gameobject
local Vector3 = require "Vector3"
local Gameobject = {position = Vector3:new(0, 0, 0), rotation = Vector3:new(0, 0, 0), model = "", drawType = -1, typePtr = 0 }

function Gameobject:new(c)
    c = c or {}
    self.__index = self
    setmetatable(c, self)
    c.position = Vector3:new(0, 0, 0)
    c.rotation = Vector3:new(0, 0, 0)
    c.model = "Assets/3DObjects/BetterCubeUV.obj"
    return c
end

function Gameobject:addToDraw()
    self.typePtr = C_addToDraw(0, self.model)
end

function Gameobject:removeFromDraw()
    self.typePtr = C_removeFromDraw(0, self.typePtr)
end

function Gameobject:move(x, y, z)
    self.position.x = self.position.x + x
    self.position.y = self.position.y + y
    self.position.z = self.position.z + z
    C_setPosition(self.typePtr, self.position.x, self.position.y, self.position.z)
end

function Gameobject:setPosition(x, y, z)
    self.position.x = x
    self.position.y = y
    self.position.z = z
    C_setPosition(self.typePtr, self.position.x, self.position.y, self.position.z)
end

function Gameobject:rotate(x, y, z)
    self.rotation.x = self.rotation.x + x
    self.rotation.y = self.rotation.y + y
    self.rotation.z = self.rotation.z + z
    for key,value in pairs(self.rotation) do
        if value > 360 then
            self.rotation[key] = self.rotation[key] - 360
        end
        if value < -360 then
            self.rotation[key] = self.rotation[key] + 360
        end
    end
    C_setRotation(self.typePtr, self.rotation.x, self.rotation.y, self.rotation.z)
end

function Gameobject:setRotation(x, y, z)
    self.rotation.x = x
    self.rotation.y = y
    self.rotation.z = z
    for key,value in pairs(self.rotation) do
        if value > 360 then
            self.rotation[key] = self.rotation[key] - 360
        end
        if value < -360 then
            self.rotation[key] = self.rotation[key] + 360
        end
    end
    C_setRotation(self.typePtr, self.rotation.x, self.rotation.y, self.rotation.z)
end

function Gameobject:setScale(x, y, z)
    C_setScale(self.typePtr, x, y, z)
end

return Gameobject