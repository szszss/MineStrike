--[[
输入处理系统
Input Lib
--]]

Input = {};

Input.inputstream = "";
Input.textInputActivated = false;

function Input.inputKeyDown(keycode)
    if keycode == 8 then
        local byte = string.byte(Input.inputstream,-1);
        if (byte>127 and byte<192) then  --对于多字节UTF8来说,每次删除必须也删除掉"continuing"
            while (byte>127 and byte<192) do
                Input.inputstream = string.sub(Input.inputstream,1,-2);
                byte = string.byte(Input.inputstream,-1);
            end
        end
        Input.inputstream=string.sub(Input.inputstream,1,-2);
    elseif keycode == 13 then
        Input.inputstream = Input.inputstream.."\n";
    end
    return 0;
end

function Input.inputText(text)
    if(Input.textInputActivated == false) then return 1 end;
    Input.inputstream=Input.inputstream..text;
    return 0;
end

function Input.enableTextInput()
    CEnableTextInput();
    Input.textInputActivated = true;
end

function Input.disableTextInput()
    CDisableTextInput();
    Input.textInputActivated = false;
    return Input.clearInputstream();
end

function Input.clearInputstream()
    local str = Input.inputstream;
    Input.inputstream = "";
    return str;
end