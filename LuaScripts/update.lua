--Key = dofile("Lua_Irrlicht_BTH_template/LuaScripts/KeyboardKeys.lua")
function EditMode()
    -- body
    local deltatime = C_getDeltaTime()

    local x, y, z = C_getMousePos3D(0, -9, 0)--parameter is a position where the plane is. can be one nodes pos
    x = x - 7--offset from 0,0,0
    z = z - 7
    
    
    x = x / 13--size per node in world space
    z = z / 13

    x = x + 1--lua start at 1
    z = z + 1
    
    x = math.floor( x )--removes the decimal  ex: 3.8 ==> 3
    z = math.floor( z )

    local posX = x--stores the cellindex
    local posY = z
    if gridObj:isValid(posX, posY) then
        selectObj:setPosition(posX * 13, -9, posY * 13)
    end

    if C_isKeyPressed(Key.MOUSE_LEFT) and isPressed == false then
        if MODE_C then
            AddCube(posX, posY)
        elseif MODE_WP then
            AddWaypoint(posX, posY)
        end
        isPressed = true
    elseif isPressed and C_isKeyPressed(Key.MOUSE_LEFT) == false then
        isPressed = false
    end


end

function GameMode()

    local deltatime = C_getDeltaTime()

    local x, y, z = C_getMousePos3D(0, -9, 0)--parameter is a position where the plane is. can be one nodes pos
    C_print(x)
    x = x - 7--offset from 0,0,0
    z = z - 7
    
    
    x = x / 13--size per node in world space
    z = z / 13

    x = x + 1--lua start at 1
    z = z + 1
    C_setText(coinsText,"$"..tostring(COINS))

    


    x = math.floor( x )--removes the decimal  ex: 3.8 ==> 3
    z = math.floor( z )

    local posX = x--stores the cellindex
    local posY = z
    if gridObj:isValid(posX, posY) then
        selectObj:setPosition(posX * 13, -9, posY * 13)
    end
    C_setText(hpText,"HP:" .. tostring(PLAYER_HP))

    local towerHere = false
    if C_isKeyPressed(Key.MOUSE_LEFT) and isPressed == false then
        if grid:isValid(posX, posY) and grid:cell(posX, posY) == 1 then--if insied the grid and is a cube
            for k,v in pairs(towers) do
                if v.x == posX and v.y == posY then--if there is already a tower here
                    towerHere = true
                    break
                end
            end 
            if towerHere == false and COINS >= 10 then
                local testTower = Tower:new()
                testTower.model = "Assets/3DObjects/BetterCubeUV.obj"
                testTower.drawType = 0
                testTower.obj:addToDraw()
                testTower.obj:setPosition(posX * 13, -6, posY * 13)
                testTower.obj:setScale(2, 1.5, 2)
                testTower.x = posX
                testTower.y = posY
                C_setTexture(testTower.obj.typePtr, 0, "Assets/3DObjects/buttonStart.tga")
                table.insert(towers, testTower)
                COINS = COINS - 10
            end
        end
        isPressed = true
    elseif isPressed and C_isKeyPressed(Key.MOUSE_LEFT) == false then
        isPressed = false
    end
    updateQueue(deltatime)
    updateEnemies(deltatime)
    for k,v in pairs(enemies) do
        v:update(deltatime)
    end
    for k,v in pairs(towers) do
        v:update(deltatime)
    end
    bulletHandler:updateBullets(deltatime)

end
function Update()
    for k,v in pairs(UI.buttons) do
        v:update()
    end
    if STATE == STATE_EDIT then
        C_setText(MODETEXT,"EDIT MODE")
        EditMode()
    elseif STATE == STATE_GAME then
        C_setText(MODETEXT,"GAME MODE")
        GameMode()
    end
end


function AddCube(x, y)
    if grid:cell(x, y) ~= 1 then--There is not a cube here so put cube
        grid:insert(1, x, y)
        local node = Gameobject:new()
        node.model = "Assets/3DObjects/BetterCubeUV.obj"
        node.drawType = 0
        if gridObj:insert(node, x, y) then 
            gridObj:cell(x, y):addToDraw()
            gridObj:cell(x, y):setPosition(x * 13, cubeBase, y * 13)
            gridObj:cell(x, y):setScale(cubeScale.x,cubeScale.y,cubeScale.z)
        end
    elseif grid:cell(x, y) ~= 0 then--there is a cube here so put none
        grid:insert(0, x, y)
        --remove cube from gridObj and draw
        gridObj:cell(x, y):removeFromDraw()
        gridObj:insert(nil, x, y)
    end
end

function AddWaypoint(x, y)
    if grid:cell(x, y) == 0 then--There is not a cube here so put waypoint
        local value = nrOfWP + 10 --ex order: 0 + 10 = 10 first WP. To get index (value - 10) + 1
        nrOfWP = nrOfWP + 1
        waypoints[nrOfWP] = Vector3:new(x * 13, 0, y * 13)
        grid:insert(value, x, y)
        local node = Gameobject:new()
        node.model = "Assets/3DObjects/BetterCubeUV.obj"
        node.drawType = 0
        if gridObj:insert(node, x, y) then 
            gridObj:cell(x, y):addToDraw()
            gridObj:cell(x, y):setPosition(x * 13, 0, y * 13)
            gridObj:cell(x, y):setScale(wayPointScale.x, wayPointScale.y, wayPointScale.z)
            C_setTexture(gridObj:cell(x, y).typePtr, 0, "Assets/3DObjects/waypoint.tga")
        end
    end       
end

function RemoveLastPlacedWaypoint()
    waypoints.remove(nrOfWP)
    nrOfWP = nrOfWP - 1
    
end