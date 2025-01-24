local Vector3 = dofile("LuaScripts/Vector3.lua")
local Gameobject = dofile("LuaScripts/Gameobject.lua")
local Bullet = {obj = Gameobject:new(), speed = 1.0, dmg = 0, enemyID = 0, id = -1}
--[[
    speed: How fast the bullet travels
    dmg: How much damage the bullet does
    enemyID: Which enemy to follow. Index into the table
--]]

function Bullet:new(id, enemyID, dmg, speed)
    c = {}
    setmetatable(c, self)
    self.__index = self

    
    --c.obj = Gameobject:new()
    
    c.enemyID = enemyID
    c.dmg = dmg
    c.speed = speed
    c.id = id
    

    return c
end

function Bullet:setPosition(x, y, z)
    self.obj:setPosition(x,y,z)
end
function Bullet:addToDraw()
    self.obj:addToDraw()
end

function Bullet:setScale(x, y, z)
    self.obj:setScale(x,y,z)
end
return Bullet