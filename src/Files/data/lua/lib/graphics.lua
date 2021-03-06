--[[
图形库
Graphics Lib
--]]

Graphics = {};

--[[function Graphics.DrawText(args)
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
end]]--

function Graphics.DrawText(args)
    local text = args.text or "";
    local x = args.x or 0;
    local y = args.y or 0;
    local size = args.size or 24;
    local width = args.width or -1;
    local color = (type(args.color)=="table" and args.color) or nil;
    if color == nil then
        color = (type(args.colour)=="table" and args.colour) or {255,255,255};
    end
    local font = args.font or "";  --TODO:A backup font
    CDrawText(text,x,y,size,width,color[1],color[2],color[3],font);
end

function Graphics.DrawImage(args)
    local image = args.image or "resource/image/logoMineStrike.bmp"; --TODO:备用纹理
    local x = args.x or 0;
    local y = args.y or 0;
    local w = args.w or -1;
    local h = args.h or -1;
    local u = args.u or 0;
    local v = args.v or 0;
    local uw = args.uw or w;
    local vh = args.vh or h;
    CDrawImage(image,x,y,w,h,u,v,uw,vh);
end

function Graphics.SetWindowTitle(title)
    CWindowSetTitle(title);
end