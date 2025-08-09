local Subject = {observers = {}}

function Subject:new()
    local c = {}
    setmetatable(c, self)
    self.__index = self

    c.observers = {}
    
    return c
end

function Subject:addObserver(observer)
    table.insert(self.observers, observer)
end

function Subject:removeObserver(observer)
    for i, obs in ipairs(self.observers) do
        if obs == observer then
            table.remove(self.observers, i)
            break
        end
    end
end

function Subject:notifyObservers(data)
    for _, observer in ipairs(self.observers) do
        C_print("Subjet updating observer")
        observer:update(data)
    end
end

return Subject