local Vector3 = dofile("Lua_Irrlicht_BTH_template/LuaScripts/Vector3.lua")
local Gameobject = dofile("Lua_Irrlicht_BTH_template/LuaScripts/Gameobject.lua")
local Bullet = {obj = Gameobject:new(), speed = 1.0, dmg = 0, enemyID = 0, id = -1}
--[[
    speed: How fast the bullet travels
    dmg: How much damage the bullet does
    enemyID: Which enemy to follow. Index into the table
--]]

function Bullet:new(id, enemyID, dmg, speed)
    c = {}
    self.__index = self
    
    setmetatable(c, self)

    c.enemyID = enemyID

    c.dmg = dmg
    c.speed = speed
    c.id = id
    return c
end


return Bullet