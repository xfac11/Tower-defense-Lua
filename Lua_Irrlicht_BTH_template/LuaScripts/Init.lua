print("In init")
Key = dofile("LuaScripts/KeyboardKeys.lua")
Gameobject = dofile("LuaScripts/Gameobject.lua")
Grid = dofile("LuaScripts/Grid.lua")
Vector3 = dofile("LuaScripts/Vector3.lua")
Enemy = dofile("LuaScripts/Enemy.lua")
Bullet = dofile("LuaScripts/Bullet.lua")
BulletHandler = dofile("LuaScripts/BulletHandler.lua")
Button = dofile("LuaScripts/Button.lua")
C_setCamPos(20, 100, -20)
grid = Grid:new()
posX = -1
posY = -1
arg2 = false
isPressed = false
grid:create(10, 10)
C_setCamTarget(-20, 0, 0)
print("asdasd")

for x=1,grid.width do
    for y=1,grid.height do
        local node = Gameobject:new()
        node.model = "3DObjects/cube2.obj"
        node.drawType = 0
        node:addToDraw()
        node:setPosition(x * 13, 0, y * 13)
        grid:insert(node, x, y)
    end
end

print("sd")
print("done")
button = C_addToDraw(1, "3DObjects/cube2Select.tga")
objButton = Button:new()
objButton:addToDraw("3DObjects/cube2Select.tga")
objButton:setPosition(400,400)
objButton:setFunction(function ()
    local pos = Vector3:new(5, 0, 0)
    if COINS >= 10 then
        bulletHandler:fireBullet(math.random(1,2), pos, 20, 50)
        COINS = COINS - 5
    end
end)
text = C_addToDraw(200, 200, 300, 220, 2, "Coins:123")
COINS = 20
C_setText(text,tostring(COINS))
isPressed = false
isPressed2 = false
nrOfWP = 6 
waypoints = {}
waypoints[1] = Vector3:new(0, 1, 0)
waypoints[2] = Vector3:new(0, 1, 20)
waypoints[3] = Vector3:new(10, 1, 10)
waypoints[4] = Vector3:new(20, 1, 10)
waypoints[5] = Vector3:new(20, 1, 20)
waypoints[6] = Vector3:new(30 ,1, 20)
for k,v in pairs(waypoints) do 
    local node = Gameobject:new()
    node.model = "3DObjects/cube2.obj"
    node.drawType = 0
    node:addToDraw()
    node:setPosition(waypoints[k].x,waypoints[k].y,waypoints[k].z)
    node:setScale(0.2,0.2,0.2)
end

e1 = Enemy:new()
e1.obj.model = "3DObjects/robot.obj"
e1.obj.drawType = 0
e1.obj:addToDraw()
e1.obj:setPosition(0, 1, 0)
e1.waypoints = waypoints
e1.endIndex = 6
e1.from:insert(waypoints[1].x, waypoints[1].y, waypoints[1].z)
e1.to:insert(waypoints[2].x, waypoints[2].y, waypoints[2].z)

e2 = Enemy:new()
e2.obj.model = "3DObjects/robot.obj"
e2.obj.drawType = 0
e2.obj:addToDraw()
e2.obj:setPosition(0, 1, 0)
e2.waypoints = waypoints
e2.endIndex = 6
e2.from:insert(waypoints[1].x, waypoints[1].y, waypoints[1].z)
e2.to:insert(waypoints[2].x, waypoints[2].y, waypoints[2].z)
enemies = {e1, e2}
bulletHandler = BulletHandler:new()

