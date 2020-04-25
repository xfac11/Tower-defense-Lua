Key = dofile("Lua_Irrlicht_BTH_template/LuaScripts/KeyboardKeys.lua")
Gameobject = dofile("Lua_Irrlicht_BTH_template/LuaScripts/Gameobject.lua")
Grid = dofile("Lua_Irrlicht_BTH_template/LuaScripts/Grid.lua")
grid = Grid:new()
posX = -1
posY = -1
grid:create(5, 5)
print("asdasd")

for x=1,grid.width do
    for y=1,grid.height do
        grid:insert(C_addToDraw(0, "3DObjects/cube2.obj"), x, y)
        C_setPosition(grid:cell(x, y), (x * 13), 0,  (y * 13))
    end
end
print("sd")
print("done")
--[[
player = Gameobject:new()
player.model = "3DObjects/robot.obj"
player.drawType = 0
player:addToDraw()
player:setPosition(0, 0, 0)
--]]

