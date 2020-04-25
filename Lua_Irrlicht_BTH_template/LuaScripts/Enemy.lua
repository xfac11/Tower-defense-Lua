local Character = require 'Character'
local x = 1
local Enemy = Character:new()

function Enemy:getType()
    return self.type
end

return Enemy



