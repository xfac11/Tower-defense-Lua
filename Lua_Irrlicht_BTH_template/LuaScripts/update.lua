--Key = dofile("Lua_Irrlicht_BTH_template/LuaScripts/KeyboardKeys.lua")
function Update()
    -- body
    C_setText(text,"$"..tostring(COINS))
    local deltatime = C_getDeltaTime()

    arg = C_isKeyPressed(Key.MOUSE_RIGHT)

    if arg and isPressed2 == false then
       
        local x, y, z = C_getMousePos3D(0, 1, 0)--parameter is a position where the plane is. can be one nodes pos
    
        x = x - 7--offset from 0,0,0
        z = z - 7
        nrOfWP = nrOfWP + 1
        waypoints[nrOfWP] = Vector3:new(x, y, z)
        
        x = x / 13--size per node in world space
        z = z / 13
    
        x = x + 1--lua start at 1
        z = z + 1
        
        x = math.floor( x )--removes the decimal  ex: 3.8 ==> 3
        z = math.floor( z )
    
        posX = x--stores the cellindex
        posY = z

        grid:cell(posX, posY):removeFromDraw()
        grid:insert(0, posX, posY)

        isPressed2 = true
        --[[--]]
    elseif isPressed2 and arg == false then
        isPressed2 = false
    end
    
    objButton:update()
   
    bulletHandler:updateBullets(deltatime)
    for k,v in pairs(enemies) do
        v:update(deltatime)
    end

end



