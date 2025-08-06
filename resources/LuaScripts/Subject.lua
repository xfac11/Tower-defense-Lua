local Subject = {}
Subject.__index = Subject

function Subject.new()
    local self = setmetatable({}, Subject)
    self.observers = {}
    return self
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
        observer:update(data)
    end
end

return Subject