--[[
游戏主脚本
Main Game Script
--]]

function RandomTitle()
    local moe = {"少女撸管中","不撸就不会死,你为何不明白!","带把少女不会怀孕","你的怀孕星在天上闪耀","洞穴中吹来的异样之风","NO MINE CRAFT",
      "绯の月,撸の夜","放过地球吧,绵月丰姬!","是小石不是小恋!","是小恋不是小石!"};
    return "MineStrike - "..moe[math.random(table.maxn(moe))];
end

function initGame()
    math.randomseed(os.time());
    Graphics.SetWindowTitle(RandomTitle());
    return 0;
end

function tick(tickTime)
    return 0;
end

function render(tickTime)
    --Graphics.DrawImage{};
    --Graphics.DrawText{text="This is a joke POWER DAZE "..tickTime.."\n"..Input.inputstream,x=10,y=10,size=24,width=600,font="msyh.ttf"};
    return 0;
end