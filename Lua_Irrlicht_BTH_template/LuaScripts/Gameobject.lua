--Gameobject.lua
--Model is the name of the texture and mesh. example: tree.tga, tree.obj

--Drawindex is given when added to irrlicht in c++. 
--This index will be used for updating pos,rot,texture,model etc in c++
--Must be used for rendered objects
-- -1 means no object in irrlicht is added to be rendered for this gameobject
local Vector3 = dofile("Lua_Irrlicht_BTH_template/LuaScripts/Vector3.lua")
local Gameobject = {position = Vector3:new(), rotation = Vector3:new(), model = "", drawType = -1, typePtr = 0 }

function Gameobject:new(c)
    c = c or {}
    self.__index = self
    return setmetatable(c, self)
end

function Gameobject:addToDraw()
    
    self.typePtr = C_addToDraw(0, self.model)
    print("added to draw")
end

function Gameobject:removeFromDraw()
    
    self.typePtr = C_removeFromDraw(0, self.typePtr)
    print("removed from draw")
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
    C_setRotationC(self.typePtr, self.rotation.x, self.rotation.y, self.rotation.z)
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
    C_setRotationC(self.typePtr, self.rotation.x, self.rotation.y, self.rotation.z)
end

function Gameobject:setScale(x, y, z)
    C_setScale(self.typePtr, x, y, z)
end

return Gameobject