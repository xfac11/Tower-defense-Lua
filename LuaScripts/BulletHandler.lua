local Vector3 = dofile("LuaScripts/Vector3.lua")
local Gameobject = dofile("LuaScripts/Gameobject.lua")
local Bullet = dofile("LuaScripts/Bullet.lua")
local BulletHandler = {bullets = {}, nrOfBullets = 0}
--[[
    speed: How fast the bullet travels
    dmg: How much damage the bullet does
    enemyID: Which enemy to follow. Index into the table
--]]

function BulletHandler:new()
    c = c or {}
    self.__index = self
    return setmetatable(c, self)
end

function BulletHandler:fireBullet(enemyID, pos, dmg, speed)
    self.nrOfBullets = self.nrOfBullets + 1
    self.bullets[self.nrOfBullets] = Bullet:new(self.nrOfBullets, enemyID, dmg, speed)
    self.bullets[self.nrOfBullets].obj = Gameobject:new()
    self.bullets[self.nrOfBullets].obj:addToDraw()
    self.bullets[self.nrOfBullets]:setPosition(pos.x, pos.y, pos.z)
    self.bullets[self.nrOfBullets]:setScale(0.3, 0.1, 0.3)
    C_setTexture(self.bullets[self.nrOfBullets].obj.typePtr, 0, "3DObjects/waypoint.tga")

end

function BulletHandler:updateBullets(deltaTime)
    
    for i=1,self.nrOfBullets do
        if enemies[self.bullets[i].enemyID] == nil then 
            --remove bullet
            self.bullets[i].obj:removeFromDraw()
            local temp = self.bullets[self.nrOfBullets]
            self.bullets[self.nrOfBullets] = self.bullets[i]
            self.bullets[i] = temp
            self.bullets[self.nrOfBullets] = nil
            self.nrOfBullets = self.nrOfBullets - 1
            break;
        end
        local vec = enemies[self.bullets[i].enemyID].obj.position:sub(self.bullets[i].obj.position)
        local vecNor = vec:normalize()
        self.bullets[i].obj:move(vecNor.x * self.bullets[i].speed * deltaTime, vecNor.y * self.bullets[i].speed * deltaTime, vecNor.z * self.bullets[i].speed * deltaTime)
    end
    self:collision()
end

function BulletHandler:collision()
    for i=1,self.nrOfBullets do
        local toEnemy = enemies[self.bullets[i].enemyID].obj.position:sub(self.bullets[i].obj.position)
        local lengthTo = toEnemy:length()

        if lengthTo < 0.2 then
            enemies[self.bullets[i].enemyID]:takeDmg(self.bullets[i].dmg)
            --remove bullet
            self.bullets[i].obj:removeFromDraw()
            local temp = self.bullets[self.nrOfBullets]
            self.bullets[self.nrOfBullets] = self.bullets[i]
            self.bullets[i] = temp
            self.bullets[self.nrOfBullets] = nil
            self.nrOfBullets = self.nrOfBullets - 1
        end
    end
end
return BulletHandler