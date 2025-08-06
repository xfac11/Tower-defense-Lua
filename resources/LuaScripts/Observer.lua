local Observer = {}
Observer.__index = Observer

function Observer.new(name, aFunction)
    local self = setmetatable({}, Observer)
    self.name = name or "Unnamed Observer"
    self.theFunction = aFunction or function(data)
        print(self.name .. " received some data: " .. tostring(data))
    end
    return self
end

function Observer:update(data)
    self.theFunction(data)
end

function Observer:setUpdateFunction(aFunction)
    self.theFunction = aFunction
end