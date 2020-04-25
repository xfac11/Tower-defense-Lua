print("begin")
local Enemy = require 'Enemy'

s = Enemy:new({pos = {2, 3, 4}, type = "LongRange"})

print(s:getType())
print(s:getX())
print("end")