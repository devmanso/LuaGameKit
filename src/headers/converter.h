#ifndef CONVERTER_H
#define CONVERTER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lua.h"
#include "lauxlib.h"
#include "luaconf.h"
#include "lualib.h"

#include "raylib.h"

Rectangle luaTableToRectangle(lua_State *L, int tableIndex) {
    Rectangle result;
    lua_pushstring(L, "x");
    lua_gettable(L, tableIndex);
    result.x = luaL_checknumber(L, -1);
    lua_pushstring(L, "y");
    lua_gettable(L, tableIndex);
    result.y = luaL_checknumber(L, -1);
    lua_pushstring(L, "width");
    lua_gettable(L, tableIndex);
    result.width = luaL_checknumber(L, -1);
    lua_pushstring(L, "height");
    lua_gettable(L, tableIndex);
    result.height = luaL_checknumber(L, -1);
    lua_pop(L, 4);
    return result;
}

Vector2 luaTableToVector2(lua_State *L, int tableIndex) {
    Vector2 vec2;
    lua_pushstring(L, "x");
    lua_gettable(L, tableIndex);
    vec2.x = luaL_checknumber(L, -1);
    lua_pushstring(L, "y");
    lua_gettable(L, tableIndex);
    vec2.y = luaL_checknumber(L, -1);
    lua_pop(L, 2);
    return vec2;
}

Color luaTableToHSVColor(lua_State *L, int tableIndex) {
    float hue, sat, val;
    lua_pushstring(L, "h");
    lua_gettable(L, tableIndex);
    hue = luaL_checknumber(L, -1);
    lua_pushstring(L, "s");
    lua_gettable(L, tableIndex);
    sat = luaL_checknumber(L, -1);
    lua_pushstring(L, "v");
    lua_gettable(L, tableIndex);
    val = luaL_checknumber(L, -1);
    Color color = ColorFromHSV(hue, sat, val);
    lua_pop(L, 3);
    return color;
}

#endif