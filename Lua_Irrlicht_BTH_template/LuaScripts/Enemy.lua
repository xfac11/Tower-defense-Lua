

local Vector3 = dofile("Lua_Irrlicht_BTH_template/LuaScripts/Vector3.lua")
local Gameobject = dofile("Lua_Irrlicht_BTH_template/LuaScripts/Gameobject.lua")
local Enemy = {obj = Gameobject:new(), from = Vector3:new(), to = Vector3:new(), check = 1, waypoints = 0, 
startIndex = 1, endIndex = 0, hp = 100}

function Enemy:new(c)
    c = c or {}
    self.__index = self
    return setmetatable(c, self)
end

function Enemy:update(deltatime)
    if self.hp > 0 then
        -- body
    
        local toNext = self.to:sub(self.from)
        toNext = toNext:normalize()

        local toPlayer = self.to:sub(self.obj.position)
        local lengthTo = toPlayer:length()

        if lengthTo < 0.1 then
            self.check = self.check + 1--one for every enemy
            self.obj:setPosition(self.to.x, self.to.y, self.to.z)
            self.from = self.waypoints[self.check]--one for every enemy
            self.to = self.waypoints[self.check + 1]--one for every enemy
        end

        self.obj:move(10 * toNext.x * deltatime, 10 * toNext.y * deltatime, 10 * toNext.z * deltatime)
    end
    
end

function Enemy:takeDmg(dmg)
    self.hp = self.hp - dmg
    if self.hp < 0 then
        self.hp = 0
    end
end

return Enemy



