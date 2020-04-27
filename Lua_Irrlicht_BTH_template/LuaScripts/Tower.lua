local Vector3 = dofile("Lua_Irrlicht_BTH_template/LuaScripts/Vector3.lua")
local Gameobject = dofile("Lua_Irrlicht_BTH_template/LuaScripts/Gameobject.lua")
local Tower = {obj = Gameobject:new(), from = Vector3:new(), to = Vector3:new(), check = 1, waypoints = 0, 
startIndex = 1, endIndex = 0, dmg = 20, attackSpeed = 1.0}

function Tower:new(c)
    c = c or {}
    self.__index = self
    return setmetatable(c, self)
end

function Tower:update(deltatime)
    self.totalTime = self.totalTime + deltatime
    if self.totalTime > (1 / self.attackSpeed) then
        self.totalTime = 0
        --shoot 
        return true
    end
    return false
end


return Tower