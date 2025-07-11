local Gameobject = require "Gameobject"
local testObj = Gameobject:new()
testObj.model = "Assets/3DObjects/Bette.obj"
testObj.drawType = 0;
testObj:addToDraw()
C_setTexture(testObj.typePtr, 0, "Assets/3DObjects/cube2lect.tga")
