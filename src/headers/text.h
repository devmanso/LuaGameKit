#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lua.h"
#include "lauxlib.h"
#include "luaconf.h"
#include "lualib.h"

#include "raylib.h"
#include "converter.h"
//#include "luafont.h"

// TODO: Implement Font functions
// this is difficult as a Font consists of:
// Texture2D, Rectangle, and GlyphInfo

// static int luaGetFontDefault(lua_State *L) {
//     Font font = GetFontDefault();
//     LuaFont *lf = (LuaFont *)lua_newuserdata(L, sizeof(LuaFont));
//     luaL_getmetatable(L, "FontMeta");
//     lua_setmetatable(L, -2);

//     // Initialize the Font struct
//     lf->font.baseSize = font.baseSize;
//     lf->font.glyphCount = font.glyphCount;
//     lf->font.glyphPadding = font.glyphPadding;
//     lf->font.texture = font.texture;
//     lf->font.recs = font.recs;
//     lf->font.glyphs = font.glyphs;

//     lua_pushinteger(L, lf->font.baseSize);
//     lua_pushinteger(L, lf->font.glyphCount);
//     lua_pushinteger(L, lf->font.glyphPadding);
//     lua_pushinteger(L, lf->font.texture.id);
//     lua_pushinteger(L, lf->font.texture.width);
//     lua_pushinteger(L, lf->font.texture.height);
//     lua_pushinteger(L, lf->font.texture.mipmaps);
//     lua_pushinteger(L, lf->font.texture.format);
//     lua_pushinteger(L, lf->font.recs);
//     lua_pushinteger(L, lf->font.glyphs);

//     return 1;
// }

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