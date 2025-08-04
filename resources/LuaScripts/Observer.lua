local Observer = {}
Observer.__index = Observer

function Observer.new(name)
    local self = setmetatable({}, Observer)
    self.name = name or "Unnamed Observer"
    return self
end

function Observer:update(data)
    print(self.name .. " received update: " .. tostring(data))
end