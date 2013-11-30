--[[
工具库
Util Lib
--]]

Util = {};

--[[function Util.wrapText(text,width,size)
    local width = (width~=-1 and width) or 600; --TODO:hehehe
    local length = math.floor(width / size);
    local i = 0;
    local start = 0;
    local str = "";
    for line in string.gmatch(text,"^[\n]") do
        if string.len(line)<=length then
            str=line;
        else
            while true do
                i = string.find(line,"[%S]",i+1);
                if i==nil then
                    
                end
                if i > (start+length) then
                    str = str..string.sub(line,start,start+length).."\n";
                    start = length+1;
                    i=start;
                else
                    str = str..string.sub(line,start,i);
                    start=i+1;
                end
            end
        end
    end
    --text = Util.wrap(text,length,0,0);
    --text = string.gsub(text,string.rep("[^\n]?",length).."[%s]?","%1\n");
    --text = string.gsub(text,"[^\n"..string.rep("+",length).."]","%1\n");
    --text = string.gsub(text,"[a+++++]","%1\n");
    return text;
end]]--