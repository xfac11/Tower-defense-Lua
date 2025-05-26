local Vector3 = dofile("LuaScripts/Vector3.lua")
local Gameobject = dofile("LuaScripts/Gameobject.lua")
local Tower = {obj = Gameobject:new(), dmg = 20, attackSpeed = 3, range = 40, target = -1, totalTime = 0, x = -1, y = -1}

function Tower:new(c)
    c = c or {}
    setmetatable(c, self)
    self.__index = self

    c.obj = Gameobject:new()
    return c
end

function Tower:update(deltatime)
    self.totalTime = self.totalTime + deltatime
    if self.totalTime > (1 / self.attackSpeed) then
        self.totalTime = 0
        if self.target~=-1 then 
            if enemies[self.target] == nil then
                self.target = -1
            else
                local toEnemy = enemies[self.target].obj.position:sub(self.obj.position)
                local lengthTo = toEnemy:length()
                if lengthTo > self.range then
                    self.target = -1 
                else
                    local bulletSpeed = 100
                    bulletHandler:fireBullet(self.target, self.obj.position, self.dmg, bulletSpeed)
                end
            end
        end
    end
    if self.target == -1 then 
        for i=1,nrOfEnemies do
            if enemies[i] ~= nil then
                local toEnemy = enemies[i].obj.position:sub(self.obj.position)
                local lengthTo = toEnemy:length()
                
                if lengthTo <= self.range then
                    self.target = i 
                    break
                end
            end
        end
    end
end


return Tower