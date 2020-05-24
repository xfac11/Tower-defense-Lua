--Grid.lua

local Button = {theFunction = function () print("Press Button") end, buttonPtr = nil, isPressed = false}

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
            C_setTexture(self.buttonPtr, 1, "3DObjects/cube2.tga")
            print("select")
            self.isPressed = true
        elseif self.isPressed and C_isButtonPressed(self.buttonPtr) == false then
            print("deselct")
            C_setTexture(self.buttonPtr, 1, "3DObjects/cube2Select.tga")
            self.isPressed = false
        end
    end
end
function Button:addToDraw(texture)
    self.buttonPtr = C_addToDraw(1, texture)
end
function Button:setPosition(x, y)
    C_setUIPos(self.buttonPtr, x, y)
end

return Button