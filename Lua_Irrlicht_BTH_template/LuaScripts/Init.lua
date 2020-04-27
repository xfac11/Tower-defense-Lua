Key = dofile("Lua_Irrlicht_BTH_template/LuaScripts/KeyboardKeys.lua")
Gameobject = dofile("Lua_Irrlicht_BTH_template/LuaScripts/Gameobject.lua")
Grid = dofile("Lua_Irrlicht_BTH_template/LuaScripts/Grid.lua")
Vector3 = dofile("Lua_Irrlicht_BTH_template/LuaScripts/Vector3.lua")
Enemy = dofile("Lua_Irrlicht_BTH_template/LuaScripts/Enemy.lua")
grid = Grid:new()
posX = -1
posY = -1
--[[
grid:create(10, 10)
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
--]]
print("sd")
print("done")
button = C_addToDraw(1, "3DObjects/cube2.tga")
isPressed = false


player = Gameobject:new()
player.model = "3DObjects/robot.obj"
player.drawType = 0
player:addToDraw()
player:setPosition(0, 1, 0)

p2 = Gameobject:new()
p2.model = "3DObjects/robot.obj"
p2.drawType = 0
p2:addToDraw()
p2:setPosition(10, 1, 0)

waypoints = {}
waypoints[1] = Vector3:new(0, 1, 0)
waypoints[2] = Vector3:new(10, 1, 0)
waypoints[3] = Vector3:new(10, 1, 10)
waypoints[4] = Vector3:new(20, 1, 10)
waypoints[5] = Vector3:new(20, 1, 20)
player:setPosition(waypoints[1].x, waypoints[1].y, waypoints[1].z)

e1 = Enemy:new()
e1.obj.model = "3DObjects/robot.obj"
e1.obj.drawType = 0
e1.obj:addToDraw()
e1.obj:setPosition(0, 1, 0)
e1.waypoints = waypoints
e1.endIndex = 4
e1.from:insert(waypoints[1].x, waypoints[1].y, waypoints[1].z)
e1.to:insert(waypoints[2].x, waypoints[2].y, waypoints[2].z)


