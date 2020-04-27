--Key = dofile("Lua_Irrlicht_BTH_template/LuaScripts/KeyboardKeys.lua")

local deltatime = C_getDeltaTime()
arg = C_isKeyPressed(Key.MOUSE_LEFT)

if arg then
   
    local x, y, z = C_getMousePos3D(0, 0, 0)--parameter is a position where the plane is. can be one nodes pos

    x = x - 7--offset from 0,0,0
    z = z - 7

    x = x / 13--size per node in world space
    z = z / 13

    x = x + 1--lua start at 1
    z = z + 1
    
    x = math.floor( x )--removes the decimal  ex: 3.8 ==> 3
    z = math.floor( z )

    posX = x--stores the cellindex
    posY = z

    
    --[[--]]
end


arg2 = C_isButtonPressed(button)

if arg2 and isPressed == false then

    print("pressed")
    e1:takeDmg(20)

    isPressed = true
    --[[--]]
elseif isPressed and arg2 == false then
    isPressed = false
end
e1:update(deltatime)

