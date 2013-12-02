--[[
面向对象编程库
Object-Oriented Programming Lib
--]]

Object = {};

Object.uuid=0;

function Object:new(object)
    object = object or {};
    setmetatable(object,self);
    self.__index = self;
    Object.uuid = Object.uuid+1;
    object.uuid = Object.uuid;
    return object;
end

function Object:getUUID()
    return self.uuid;
end

function Object:equals(object)
    return self:getUUID == object:getUUID;
end