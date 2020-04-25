print("sadasd")
Gameobject = require 'LuaScripts/Gameobject'
Vector3 = require 'LuaScripts/Vector3'
Grid = require 'LuaScripts/Grid'

TYPE_MESH, TYPE_BUTTON, TYPE_TEXT = 0, 1, 2
grid = Grid:new()
grid:create(10, 10)
print("asda")
grid:insert(3,2,5)
grid:print()
saw = addToDraw(0, "test")
function initialize()
	player = Gameobject:New()
	player.drawType =
	enemies = {}
	nrOfEnemies = 0
end

function addEnemy(position, type, nToAdd)
	for i=0,nToAdd do
		enemies[nrOfEnemies] = Gameobject.New()
		nrOfEnemies = nrOfEnemies + 1
	end
end

function show()
	print(player.position.x)
end

function update(x, z)
	local vec = Vector3:New()
	vec.x = x*0.01
	vec.z = z
	vec.y = 0
	player.position = player.position + vec
	--player.position.z = player.position.z + (z * 0.01)
	print(player.position.x)
	return player.position.x, player.position.z
end


function loadGrid(fileName)
	stage, width, height = loadStage(fileName)
	
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
	saveStage(stageGrid, height, width, fileName)
end
saveGrid(grid, grid.height, grid.width, "Stages/stage1.lvl")
grid2 = loadGrid("Stages/stage1.lvl")
grid2:print()
saveGrid(grid2, grid2.height, grid2.width, "Stages/stage1.lvl")
grid3 = loadGrid("Stages/stage1.lvl")
print("Grid 3: \n")
grid3:print()
