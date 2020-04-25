--Key = dofile("Lua_Irrlicht_BTH_template/LuaScripts/KeyboardKeys.lua")
arg = C_isKeyPressed(Key.MOUSE_LEFT)

if arg then
   
    local x, y, z = C_getMousePos3D(0, 0, 0)

    x = x - 7--offset
    z = z - 7

    x = x / 13--size per node
    z = z / 13

    x = x + 1--lua start at 1
    z = z + 1
    
    x = math.floor( x )
    z = math.floor( z )

    posX = x
    posY = z

    
    --[[--]]
end


arg2 = C_isKeyPressed(Key.MOUSE_RIGHT)
if arg2 then
   
    local x, y, z = C_getMousePos3D(0, 0, 0)


    C_setPosition(grid:cell(posX, posY), x, y, z)

    
    --[[--]]
end