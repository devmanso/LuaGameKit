#ifndef LUAFONT_H
#define LUAFONT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lua.h"
#include "lauxlib.h"
#include "luaconf.h"
#include "lualib.h"

#include "raylib.h"

// Define LuaFont as a userdata wrapper around Font
typedef struct {
    Font font;
} LuaFont;

// Font creation
static int luaNewFont(lua_State *L) {
    LuaFont *lf = (LuaFont *)lua_newuserdata(L, sizeof(LuaFont));
    luaL_getmetatable(L, "FontMeta");
    lua_setmetatable(L, -2);

    // Initialize the Font struct
    lf->font.baseSize = 0;
    lf->font.glyphCount = 0;
    lf->font.glyphPadding = 0;
    lf->font.texture.id = 0;
    lf->font.texture.width = 0;
    lf->font.texture.height = 0;
    lf->font.texture.mipmaps = 1;
    lf->font.texture.format = 0;
    lf->font.recs = NULL;
    lf->font.glyphs = NULL;

    return 1;
}

// Setters and getters for baseSize
static int luaGetBaseSize(lua_State *L) {
    LuaFont *lf = (LuaFont *)luaL_checkudata(L, 1, "FontMeta");
    lua_pushinteger(L, lf->font.baseSize);
    return 1;
}

static int luaSetBaseSize(lua_State *L) {
    LuaFont *lf = (LuaFont *)luaL_checkudata(L, 1, "FontMeta");
    int baseSize = luaL_checkinteger(L, 2);
    lf->font.baseSize = baseSize;
    return 0;
}

// Setters and getters for glyphCount
static int luaGetGlyphCount(lua_State *L) {
    LuaFont *lf = (LuaFont *)luaL_checkudata(L, 1, "FontMeta");
    lua_pushinteger(L, lf->font.glyphCount);
    return 1;
}

static int luaSetGlyphCount(lua_State *L) {
    LuaFont *lf = (LuaFont *)luaL_checkudata(L, 1, "FontMeta");
    int glyphCount = luaL_checkinteger(L, 2);
    lf->font.glyphCount = glyphCount;
    return 0;
}

// Setters and getters for glyphPadding
static int luaGetGlyphPadding(lua_State *L) {
    LuaFont *lf = (LuaFont *)luaL_checkudata(L, 1, "FontMeta");
    lua_pushinteger(L, lf->font.glyphPadding);
    return 1;
}

static int luaSetGlyphPadding(lua_State *L) {
    LuaFont *lf = (LuaFont *)luaL_checkudata(L, 1, "FontMeta");
    int glyphPadding = luaL_checkinteger(L, 2);
    lf->font.glyphPadding = glyphPadding;
    return 0;
}

// Setters and getters for texture
static int luaGetTexture(lua_State *L) {
    LuaFont *lf = (LuaFont *)luaL_checkudata(L, 1, "FontMeta");
    lua_newtable(L);
    lua_pushinteger(L, lf->font.texture.id);
    lua_setfield(L, -2, "id");
    lua_pushinteger(L, lf->font.texture.width);
    lua_setfield(L, -2, "width");
    lua_pushinteger(L, lf->font.texture.height);
    lua_setfield(L, -2, "height");
    lua_pushinteger(L, lf->font.texture.mipmaps);
    lua_setfield(L, -2, "mipmaps");
    lua_pushinteger(L, lf->font.texture.format);
    lua_setfield(L, -2, "format");
    return 1;
}

static int luaSetTexture(lua_State *L) {
    LuaFont *lf = (LuaFont *)luaL_checkudata(L, 1, "FontMeta");
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "id");
    lf->font.texture.id = luaL_checkinteger(L, -1);
    lua_getfield(L, 2, "width");
    lf->font.texture.width = luaL_checkinteger(L, -1);
    lua_getfield(L, 2, "height");
    lf->font.texture.height = luaL_checkinteger(L, -1);
    lua_getfield(L, 2, "mipmaps");
    lf->font.texture.mipmaps = luaL_checkinteger(L, -1);
    lua_getfield(L, 2, "format");
    lf->font.texture.format = luaL_checkinteger(L, -1);
    return 0;
}

// Setters and getters for glyphs
static int luaGetGlyphs(lua_State *L) {
    LuaFont *lf = (LuaFont *)luaL_checkudata(L, 1, "FontMeta");

    if (lf->font.glyphs == NULL) {
        lua_pushnil(L);
        return 1;
    }

    lua_newtable(L);
    for (int i = 0; i < lf->font.glyphCount; i++) {
        lua_newtable(L);
        lua_pushinteger(L, lf->font.glyphs[i].value);
        lua_setfield(L, -2, "value");
        lua_pushinteger(L, lf->font.glyphs[i].offsetX);
        lua_setfield(L, -2, "offsetX");
        lua_pushinteger(L, lf->font.glyphs[i].offsetY);
        lua_setfield(L, -2, "offsetY");
        lua_pushinteger(L, lf->font.glyphs[i].advanceX);
        lua_setfield(L, -2, "advanceX");
        lua_newtable(L);  // image table
        lua_pushlightuserdata(L, lf->font.glyphs[i].image.data);
        lua_setfield(L, -2, "data");
        lua_pushinteger(L, lf->font.glyphs[i].image.width);
        lua_setfield(L, -2, "width");
        lua_pushinteger(L, lf->font.glyphs[i].image.height);
        lua_setfield(L, -2, "height");
        lua_pushinteger(L, lf->font.glyphs[i].image.mipmaps);
        lua_setfield(L, -2, "mipmaps");
        lua_pushinteger(L, lf->font.glyphs[i].image.format);
        lua_setfield(L, -2, "format");
        lua_setfield(L, -2, "image");
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

static int luaSetGlyphs(lua_State *L) {
    LuaFont *lf = (LuaFont *)luaL_checkudata(L, 1, "FontMeta");
    luaL_checktype(L, 2, LUA_TTABLE);

    int glyphCount = luaL_len(L, 2);
    lf->font.glyphs = (GlyphInfo *)malloc(glyphCount * sizeof(GlyphInfo));
    lf->font.glyphCount = glyphCount;

    for (int i = 0; i < glyphCount; i++) {
        lua_rawgeti(L, 2, i + 1);

        lua_getfield(L, -1, "value");
        lf->font.glyphs[i].value = luaL_checkinteger(L, -1);

        lua_getfield(L, -1, "offsetX");
        lf->font.glyphs[i].offsetX = luaL_checkinteger(L, -1);

        lua_getfield(L, -1, "offsetY");
        lf->font.glyphs[i].offsetY = luaL_checkinteger(L, -1);

        lua_getfield(L, -1, "advanceX");
        lf->font.glyphs[i].advanceX = luaL_checkinteger(L, -1);

        lua_getfield(L, -1, "image");
        lua_getfield(L, -1, "data");
        lf->font.glyphs[i].image.data = lua_touserdata(L, -1);

        lua_getfield(L, -2, "width");
        lf->font.glyphs[i].image.width = luaL_checkinteger(L, -1);

        lua_getfield(L, -2, "height");
        lf->font.glyphs[i].image.height = luaL_checkinteger(L, -1);

        lua_getfield(L, -2, "mipmaps");
        lf->font.glyphs[i].image.mipmaps = luaL_checkinteger(L, -1);

        lua_getfield(L, -2, "format");
        lf->font.glyphs[i].image.format = luaL_checkinteger(L, -1);

        lua_pop(L, 9);  // Clean up the stack
    }

    return 0;
}

static const struct luaL_Reg font_methods[] = {
    {"new", luaNewFont},
    {"getBaseSize", luaGetBaseSize},
    {"setBaseSize", luaSetBaseSize},
    {"getGlyphCount", luaGetGlyphCount},
    {"setGlyphCount", luaSetGlyphCount},
    {"getGlyphPadding", luaGetGlyphPadding},
    {"setGlyphPadding", luaSetGlyphPadding},
    {"getTexture", luaGetTexture},
    {"setTexture", luaSetTexture},
    {"getGlyphs", luaGetGlyphs},
    {"setGlyphs", luaSetGlyphs},
    // TODO: more methods for rectangles?
    {NULL, NULL}
};

static const struct luaL_Reg font_meta[] = {
    {"__index", NULL},  // Use the __index method to redirect to methods
    {NULL, NULL}
};

static int lua_font_index(lua_State *L) {
    LuaFont *lf = (LuaFont *)luaL_checkudata(L, 1, "FontMeta");
    const char *field = luaL_checkstring(L, 2);

    if (strcmp(field, "baseSize") == 0) {
        lua_pushinteger(L, lf->font.baseSize);
        return 1;
    } else if (strcmp(field, "glyphCount") == 0) {
        lua_pushinteger(L, lf->font.glyphCount);
        return 1;
    } else if (strcmp(field, "glyphPadding") == 0) {
        lua_pushinteger(L, lf->font.glyphPadding);
        return 1;
    } else if (strcmp(field, "texture") == 0) {
        return luaGetTexture(L);
    } else if (strcmp(field, "glyphs") == 0) {
        return luaGetGlyphs(L);
    }
    
    lua_getmetatable(L, 1);
    lua_pushstring(L, field);
    lua_rawget(L, -2);

    return 1;
}

int luaopen_font(lua_State *L) {
    luaL_newmetatable(L, "FontMeta");

    lua_pushstring(L, "__index");
    lua_pushcfunction(L, lua_font_index);
    lua_settable(L, -3);

    luaL_newlib(L, font_methods);
    return 1;
}

#endif
