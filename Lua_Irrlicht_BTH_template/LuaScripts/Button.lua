--Grid.lua

local Button = {theFunction = function () print("Press Button") end, buttonPtr = nil, isPressed = false, texture = "", x = 0, y = 0}

function Button:new(c)
    c = c or {}
    self.__index = self
    return setmetatable(c, self)
end
function Button:setFunction(aFunction)
    self.theFunction = aFunction
end
function Button:update()
    if self.buttonPtr ~= nil then
        if C_isButtonPressed(self.buttonPtr) and self.isPressed == false then
            self.theFunction()
            --C_setTexture(self.buttonPtr, 1, "3DObjects/button.tga")
            print("select")
            self.isPressed = true
        elseif self.isPressed and C_isButtonPressed(self.buttonPtr) == false then
            print("deselct")
            --C_setTexture(self.buttonPtr, 1, "3DObjects/button.tga")
            self.isPressed = false
        end
    end
end
function Button:addToDraw(texture)
    self.buttonPtr = C_addToDraw(1, texture)
    self.texture = texture
end
function Button:addToDrawT()
    self.buttonPtr = C_addToDraw(1, self.texture)
    self:setPosition(self.x, self.y)
end
function Button:setPosition(x, y)
    C_setUIPos(self.buttonPtr, x, y)
    self.x = x
    self.y = y 
end
function Button:removeFromDraw()
    C_removeFromDraw(1, self.buttonPtr)
    self.buttonPtr = nil
end
return Button