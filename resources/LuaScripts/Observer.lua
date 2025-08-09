local Observer = {name = "Unnamed Observer", theFunction = function(data) print(tostring(data)) end}

function Observer:new(name, aFunction)
    local c =  {}
    setmetatable(c, self)
    self.__index = self

    c.name = name or "Unamed Observer"
    c.theFunction = aFunction or function(data) print(tostring(name)) end

    return c
end

function Observer:update(data)
    C_print("name called")
    self.theFunction(data)
end

function Observer:setUpdateFunction(aFunction)
    self.theFunction = aFunction
end

return Observer