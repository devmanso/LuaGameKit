#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lua.h"
#include "lauxlib.h"
#include "luaconf.h"
#include "lualib.h"

#include "raylib.h"
#include "converter.h"

static int luaGetFontDefault(lua_State *L) {
    Font font = GetFontDefault();

    // Create a Lua table to hold font properties
    lua_newtable(L);

    // Set baseSize property
    lua_pushstring(L, "baseSize");
    lua_pushinteger(L, font.baseSize);
    lua_settable(L, -3);

    // Set glyphCount property
    lua_pushstring(L, "glyphCount");
    lua_pushinteger(L, font.glyphCount);
    lua_settable(L, -3);

    // Set glyphPadding property
    lua_pushstring(L, "glyphPadding");
    lua_pushinteger(L, font.glyphPadding);
    lua_settable(L, -3);

    // Set texture property (You might need to handle Texture2D type accordingly)
    // Assuming texture is not userdata and can be represented as a string or number
    lua_pushstring(L, "texture");
    luaTextureToTable(L, font.texture);
    lua_settable(L, -3);

    lua_pushstring(L, "recs");
    luaRectangleToTable(L, *font.recs);
    lua_settable(L, -3);

    return 1;
}


static int luaDrawFPS(lua_State *L) {
    float x = luaL_checknumber(L, 1);
    float y = luaL_checknumber(L, 2);
    DrawFPS(x,y);
    return 0;
}

static int luaDrawText(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    float x = luaL_checknumber(L, 2);
    float y = luaL_checknumber(L, 3);
    int fontsize = luaL_checkinteger(L, 4);
    Color color = luaTableToHSVColor(L, 5);
    DrawText(text, x, y, fontsize, color);
    return 0;
}

void registerTextBindings(lua_State *L) {
    lua_register(L, "DrawText", luaDrawText);
    lua_register(L, "DrawFPS", luaDrawFPS);
    lua_register(L, "GetFontDefault", luaGetFontDefault);
}