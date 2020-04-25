--Grid.lua

local Grid = {width = 0, height = 0, theGrid = {}}

function Grid:new(c)
    c = c or {}
    self.__index = self
    return setmetatable(c, self)
end

function Grid:create(width, height)
    self.width = width
    self.height = height

    for x=1,width do
        self.theGrid[x] = {}
        for y=1,height do
            table.insert(self.theGrid[x], 0)
        end
    end
end

function Grid:isValid(x, y)
    if x > self.width or x < 1 or y > self.height or y < 1 then
        return false
    end
    return true
end

function Grid:cell(x, y)
    if self:isValid(x, y) then
        return self.theGrid[x][y]
    end
end

function Grid:insert(value, x, y)
    if self:isValid(x, y) then
        self.theGrid[x][y] = value
    end
end

function Grid:print()
    local gridString = ""
    for y=1,self.width do
        for x=1,self.height do
            gridString = gridString .. self.theGrid[x][y] .. " "
        end
        gridString = gridString .. "\n"
    end
    print(gridString)
end

function Grid:create1d()
    local grid1d = {};
    local index = 1
    for x=1,self.width do
        for y=1,self.height do
            grid1d[tostring(index)] = self.theGrid[x][y]
            index = index + 1
        end
    end
    return grid1d
end

return Grid