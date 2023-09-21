#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lua.h"
#include "lauxlib.h"
#include "luaconf.h"
#include "lualib.h"

#include "raylib.h"
#include "converter.h"

// testing stuff

static int luaDrawText(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    float x = luaL_checknumber(L, 2);
    float y = luaL_checknumber(L, 3);
    int fontsize = luaL_checkinteger(L, 4);
    Color color = luaTableToHSVColor(L, 5);
    DrawText(text, x, y, fontsize, color);
    return 0;
}

static int luaDrawFPS(lua_State *L) {
    float x = luaL_checknumber(L, 1);
    float y = luaL_checknumber(L, 2);
    DrawFPS(x,y);
    return 0;
}

void registerTextBindings(lua_State *L) {
    lua_register(L, "DrawText", luaDrawText);
    lua_register(L, "DrawFPS", luaDrawFPS);
}