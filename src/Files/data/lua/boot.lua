--[[
强袭矿坑
Mine♂Strike Project~
Powered by 少女神隐俱乐部~
Wrote by Emmalubally(a.k.a szszss)~
Started at 2013-9-11
--]]

--[[
启动器文件
Bootstrap

启动器文件用于检查并引导其他Lua脚本文件载入和运行.
The bootstrap is used to load&run other lua script file.
--]]

function main()
    package.path = './data/lua/?.lua;./data/lua/lib/?.lua;' .. package.path;
    print("Hello, world!\n");
    require("graphics");
    require("input");
    require("util");
    require("game");
    initGame();
    return 0;
end
