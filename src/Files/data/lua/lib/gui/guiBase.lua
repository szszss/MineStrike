--[[
Gui基础类
GUI Control Prototype Class
--]]

GuiBase = Object:new();
GuiBase.posX = 0;
GuiBase.posY = 0;
GuiBase.hide = false;

function GuiBase:setPosition(x,y)
    self.posX=x;
    self.posY=y;
end

function GuiBase:update()
end

function GuiBase:shouldDraw()
    return not self.hide;
end

function GuiBase:draw()
end