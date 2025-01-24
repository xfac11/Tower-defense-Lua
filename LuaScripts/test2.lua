Gameobject = dofile("Lua_Irrlicht_BTH_template/LuaScripts/Gameobject.lua")
Grid = dofile("Lua_Irrlicht_BTH_template/LuaScripts/Grid.lua")
grid = Grid:new()

grid:create(5, 5)
print("asdasd")

for x=1,grid.width do
    for y=1,grid.height do
        grid:insert(C_addToDraw(0, "3DObjects/cube2.obj"), x, y)
        C_setPosition(grid:cell(x, y), -10 + (x * 10), 0, -10 + (y * 10))
    end
end
print("sd")
--[[
Key = dofile("Lua_Irrlicht_BTH_template/LuaScripts/KeyboardKeys.lua")

Gameobject = dofile("Lua_Irrlicht_BTH_template/LuaScripts/Gameobject.lua")
print("aaa")


Vector3 = dofile("Vector3.lua")

vec1 = Vector3:new()
vec2 = Vector3:new()
vec1:insert(2, 5, 1)
vec2:insert(3, 1, 6)

dot = vec1:dot(vec2)



player = Gameobject:new()
player.model = "3DObjects/robot.obj"
player.drawType = 0
player:addToDraw()
player:setPosition(0, 40, 0)
print("set")--]]