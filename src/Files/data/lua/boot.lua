--[[
ǿϮ���
Mine��Strike Project~
Powered by ��Ů�������ֲ�~
Wrote by Emmalubally(a.k.a szszss)~
Started at 2013-9-11
--]]

--[[
�������ļ�
Bootstrap

�������ļ����ڼ�鲢��������Lua�ű��ļ����������.
The bootstrap is used to load&run other lua script file.
--]]

function main()
    package.path = './data/lua/?.lua;' .. package.path;
    print("Hello, world!\n");
    require("game");
    require("graphics");
    --tick();
    return 0;
end
