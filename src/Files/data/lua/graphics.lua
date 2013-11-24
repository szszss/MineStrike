--[[
м╪пн©Б
Graphics
--]]

function DrawText(args)
    local text = (args.text~=nil and args.text) or "";  --type(args.text)!=nil?args.text:""
    local x = (type(args.x)=="number" and args.x) or 0;
    local y = (type(args.y)=="number" and args.y) or 0;
    local size = (type(args.size)=="number" and args.size) or 24;
    local width = (type(args.width)=="number" and args.width) or -1;
    local color = (type(args.color)=="table" and args.color) or nil;
    if color == nil then
        color = (type(args.colour)=="table" and args.colour) or {255,255,255};
    end
    local font = (type(args.font)=="string" and args.font) or "";  --TODO:A backup font
    CDrawText(text,x,y,size,width,color[1],color[2],color[3],font);
end