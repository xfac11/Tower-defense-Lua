Key = dofile("LuaScripts/KeyboardKeys.lua")
Gameobject = dofile("LuaScripts/Gameobject.lua")
Grid = dofile("LuaScripts/Grid.lua")
Vector3 = dofile("LuaScripts/Vector3.lua")
Enemy = dofile("LuaScripts/Enemy.lua")
Bullet = dofile("LuaScripts/Bullet.lua")
BulletHandler = dofile("LuaScripts/BulletHandler.lua")
Button = dofile("LuaScripts/Button.lua")
Tower = dofile("LuaScripts/Tower.lua")
DrawType = {
    MESH = 0,
    BUTTON = 1,
    TEXT = 2,
	EDITBOX = 3,
	IMAGE = 4
}
MODE_C = true
MODE_WP = false
STATE = 0 
STATE_EDIT = 0
STATE_GAME = 1
UI = {buttons = {}, text = {}}
GAME_UI = {buttons = {}, text = {}}
EDIT_UI = {buttons = {}, text = {}}
MODETEXT = C_addToDraw(1200, 600, 1300, 700, DrawType.TEXT, "")
C_setFont(MODETEXT, DrawType.TEXT, "myfont.xml")
textBox = C_addToDraw(1000, 600, 1300, 700, DrawType.EDITBOX, "")
PLAYER_HP = 100
function loadGrid(fileName)
	stage, width, height = C_loadStage(fileName)
    local grid = Grid:new()
	grid:create(width, height)
	local index = 1
	for x=1,width do
        for y=1,height do
			grid:insert(math.tointeger(stage[tostring(index)]),x,y)
			index = index + 1
			
		end
	end 
	return grid
end

function saveGrid(grid, height, width, fileName)
	local stageGrid = grid:create1d()
	C_saveStage(stageGrid, height, width, fileName)
end





--Level editor
cubeBase = -10--y position
cubeScale = Vector3:new(6.6,0.5,6.6)
wayPointScale = Vector3:new(1,1,1)
posX = -1
posY = -1
gridObj = Grid:new()
grid = loadGrid("Stages/stage1.lvl")
gridObj:create(grid.width, grid.height)

nrOfWP = 0 
waypoints = {}

selectObj = Gameobject:new()
selectObj.model = "3DObjects/BetterCubeUV.obj"
selectObj.drawType = 0
selectObj:addToDraw()
selectObj:setScale(5, 0.2, 5)
C_setTexture(selectObj.typePtr, 0, "3DObjects/cube2Select.tga")


--Setup objects in world for editor or game
function loadInObjects()
    for x=1,grid.width do
        for y=1,grid.height do
            if grid:cell(x, y) == 1 then--place cube
                local node = Gameobject:new()
                node.model = "3DObjects/BetterCubeUV.obj"
                node.drawType = 0
                node:addToDraw()
                node:setPosition(x * 13, cubeBase, y * 13)
                node:setScale(cubeScale.x,cubeScale.y,cubeScale.z)
                gridObj:insert(node, x, y)
                
            elseif grid:cell(x, y) >= 10 then --place waypoint. Only for edit mode
                local index = (grid:cell(x, y) - 10) + 1
                waypoints[index] = Vector3:new(x * 13, -5, y * 13)
                nrOfWP = nrOfWP + 1
                local node = Gameobject:new()
                node.model = "3DObjects/BetterCubeUV.obj"
                node.drawType = 0
                node:addToDraw()
                node:setPosition(x * 13, -5, y * 13)
                node:setScale(wayPointScale.x, wayPointScale.y, wayPointScale.z)
                C_setTexture(node.typePtr, 0, "3DObjects/waypoint.tga")
                
                gridObj:insert(node, x, y)
            end
        end
    end
end
function removeGridObjects()
    for x=1,grid.width do
        for y=1,grid.height do
            if grid:cell(x,y) ~= 0 then
                gridObj:cell(x, y):removeFromDraw()
            end
        end
    end
    waypoints = {}
    nrOfWP = 0
end
loadInObjects()
--Camera
C_setCamTarget(6*13,0,6*13)
C_setCamPos(150, 80, 6*13)
--UI

panelPtr = nil
panelPtr = C_addToDraw(10, 10 ,DrawType.IMAGE, "3DObjects/cube2.tga")
--C_setUIPos(panel, 10, 10)


changeEM = Button:new()
changeEM:addToDraw("3DObjects/buttonWaypoint.tga")
changeEM:setPosition(0,400)
changeEM:setFunction(function ()
    if MODE_WP then
        MODE_WP = false
        MODE_C = true
    elseif MODE_C then
        MODE_C = false
        MODE_WP = true
    end
end)


objButton = Button:new()
objButton:addToDraw("3DObjects/buttonMode.tga")
objButton:setPosition(1080,0)



resetButton = Button:new()
resetButton:addToDraw("3DObjects/buttonReset.tga")
resetButton:setPosition(0,600)
resetButton:setFunction(function ()
    for x=1,grid.width do
        for y=1,grid.height do
            if grid:cell(x,y) ~= 0 then
                gridObj:cell(x, y):removeFromDraw()
            end
            grid:insert(1, x, y)
            local node = Gameobject:new()
                node.model = "3DObjects/BetterCubeUV.obj"
                node.drawType = 0
                node:addToDraw()
                node:setPosition(x * 13, cubeBase, y * 13)
                node:setScale(cubeScale.x,cubeScale.y,cubeScale.z)
                gridObj:insert(node, x, y)
        end
    end
    waypoints = {}
    nrOfWP = 0
end)

saveButton = Button:new()
saveButton:addToDraw("3DObjects/buttonSave.tga")
saveButton:setPosition(0,0)
saveButton:setFunction(function ()
    local text = C_getText(textBox)
    if text ~= "" then
        text = text .. ".lvl"
        saveGrid(grid, grid.height, grid.width, "Stages/"..text)
        C_setText(textBox,"")
    end
end)

loadButton = Button:new()
loadButton:addToDraw("3DObjects/buttonLoad.tga")
loadButton:setPosition(0,100)
loadButton:setFunction(function ()
    print("load")
    local text = C_getText(textBox)
    if text ~= "" then
        text = text .. ".lvl"
        removeGridObjects()
        grid = loadGrid("Stages/"..text)
        gridObj = Grid:new()
        gridObj:create(grid.width, grid.height)
        loadInObjects()
        C_setText(textBox,"")
    end
end)


UI.buttons["objButton"] = objButton
UI.buttons["ChangeMode"] = changeEM
UI.buttons["resetButton"] = resetButton
UI.buttons["saveButton"] = saveButton
UI.buttons["loadButton"] = loadButton


EDIT_UI.buttons["ChangeMode"] = changeEM
EDIT_UI.buttons["resetButton"] = resetButton
EDIT_UI.buttons["saveButton"] = saveButton
EDIT_UI.buttons["loadButton"] = loadButton
EDIT_UI.buttons["objButton"] = objButton

GAME_UI.buttons["objButton"] = objButton
COINS = 20

coinsText = C_addToDraw(120, 120, 150, 150, 2, "Coins:123")
UI.text["coinsText"] = coinsText
C_setText(coinsText,"$"..tostring(COINS))
isPressed = false
isPressed2 = false

hpText = C_addToDraw(120,160,160,200,DrawType.TEXT,"HP:")
C_setText(hpText,"HP:" .. tostring(PLAYER_HP))

--Game
towers = {}
enemies = {}--in the world updating and walking towards waypoints
nrOfEnemies = 0
enemyQueue = {}--waiting to go in the world( in table enemies)
enemiesInQueue = 0
queueTime = 1 
waveNr = 1
totalTime = 0
ground = Gameobject:new()
ground.model = "3DObjects/BetterCubeUV.obj"
ground.drawType = 0
ground:addToDraw()
ground:setPosition(5.5*13,-50, 5.5*13)
ground:setScale(200,0.1,200)
C_setTexture(ground.typePtr, 0, "3DObjects/ground.tga")

function nextWave()
    --Start the next wave
    if nrOfEnemies == 0 then     
        for i=1,waveNr*5 do
            local e = Enemy:new()
            e.obj.model = "3DObjects/robot.obj"
            e.obj.drawType = 0
            e.waypoints = waypoints
            e.endIndex = nrOfWP
            e.from:insert(waypoints[1].x, waypoints[1].y, waypoints[1].z)
            e.to:insert(waypoints[2].x, waypoints[2].y, waypoints[2].z)
            enemyQueue[i] = e
        end
        enemiesInQueue = waveNr * 5
        waveNr = waveNr + 1
    end
end
function updateQueue(deltaTime)
    if enemiesInQueue > 0 then
        totalTime = totalTime + deltaTime
        if totalTime >= queueTime then
            totalTime = 0
            local e = enemyQueue[enemiesInQueue]
            e.obj:addToDraw()
            
            e.obj:setPosition(waypoints[1].x, waypoints[1].y, waypoints[1].z)
            nrOfEnemies = nrOfEnemies + 1
            enemies[nrOfEnemies] = e
            enemyQueue[enemiesInQueue] = nil
            enemiesInQueue = enemiesInQueue - 1
        end
    end
end
function updateEnemies(deltaTime)
    local nrOfNil = 0
    
    for i=1,nrOfEnemies do
        if enemies[i] ~= nil then
            if enemies[i].check == enemies[i].endIndex  then
                enemies[i].obj:removeFromDraw()
                enemies[i] = nil
                PLAYER_HP = PLAYER_HP - 5
            elseif enemies[i].hp <= 0 then 
                enemies[i].obj:removeFromDraw()
                enemies[i] = nil
                COINS = COINS + 10
            end
        else
            nrOfNil = nrOfNil + 1
        end
    end
    if nrOfNil == nrOfEnemies then
        nrOfEnemies = 0
    end
end
startButton = Button:new()
startButton.texture = "3DObjects/buttonStart.tga"
startButton:setPosition(0,0)
startButton:setFunction(function ()
    --Start next wave
    nextWave()
end)
GAME_UI.buttons["startButton"] = startButton
bulletHandler = BulletHandler:new()

objButton:setFunction(function ()
    for k,v in pairs(UI.buttons) do
        v:removeFromDraw()
    end
    if STATE == STATE_EDIT then
        UI = GAME_UI
        STATE = STATE_GAME
    elseif STATE == STATE_GAME then
        UI = EDIT_UI
        STATE = STATE_EDIT
    end
    for k,v in pairs(UI.buttons) do
        v:addToDrawT()
    end
    for k,v in pairs(towers) do
        v.obj:removeFromDraw()
    end
    for k,v in pairs(enemies) do
        v.obj:removeFromDraw()
    end
    for k,v in pairs(bulletHandler.bullets) do
        v.obj:removeFromDraw()
    end
    bulletHandler.bullets = {}
    bulletHandler.nrOfBullets = 0
    towers = {}
    enemies = {}
    enemyQueue = {}
    nrOfEnemies = 0
    enemiesInQueue = 0
    queueTime = 1 
    waveNr = 1
    totalTime = 0
end)