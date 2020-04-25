--Key = dofile("Lua_Irrlicht_BTH_template/LuaScripts/KeyboardKeys.lua")
arg = C_isKeyPressed(Key.MOUSE_LEFT)
if arg then
   
    local x, y, z = C_getMousePos3D(0, 0, 0)
    C_setPosition(grid:cell(3, 2), x, y, z)

    
    --[[--]]
end


arg2 = C_isKeyPressed(Key.MOUSE_RIGHT)
if arg2 then
   
    local x, y, z = C_getMousePos3D(0, 0, 0)
    C_setPosition(grid:cell(3, 2), x, y, z)

    
    --[[--]]
end