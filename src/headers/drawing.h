#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lua.h"
#include "lauxlib.h"
#include "luaconf.h"
#include "lualib.h"

#include "raylib.h"

// shape drawing functions

static int luaDrawPixel(lua_State* L) {
    int posx = luaL_checkinteger(L, 1);
    int posy = luaL_checkinteger(L, 2);
    float hue = luaL_checknumber(L, 3);
    float saturation = luaL_checknumber(L, 4);
    float value = luaL_checknumber(L, 5);
    Color color = ColorFromHSV(
    hue, 
    saturation, 
    value);
    DrawPixel(posx, posy, color);
    return 0;
}

static int luaDrawPixelV(lua_State* L) {
    float vectorx = luaL_checknumber(L, 1);
    float vectory = luaL_checknumber(L, 2);
    float hue = luaL_checknumber(L, 3);
    float saturation = luaL_checknumber(L, 4);
    float value = luaL_checknumber(L, 5);
    Color color = ColorFromHSV(
    hue, 
    saturation, 
    value);
    Vector2 vector;
    vector.x = vectorx;
    vector.y = vectory;
    DrawPixelV(vector, color);
    return 0;
}

static int luaDrawLine(lua_State* L) {
    int startposx = luaL_checkinteger(L, 1);
    int startposy = luaL_checkinteger(L, 2);
    int endposx = luaL_checkinteger(L, 3);
    int endposy = luaL_checkinteger(L, 4);
    float hue = luaL_checknumber(L, 5);
    float saturation = luaL_checknumber(L, 6);
    float value = luaL_checknumber(L, 7);
    Color color = ColorFromHSV(
    hue, 
    saturation, 
    value);
    DrawLine(startposx, startposy, endposx, endposy, color);
    return 0;
}

static int luaDrawLineV(lua_State* L) {
    float startposx = luaL_checknumber(L, 1);
    float startposy = luaL_checknumber(L, 2);
    float endposx = luaL_checknumber(L, 3);
    float endposy = luaL_checknumber(L, 4);
    Vector2 startvector;
    startvector.x = startposx;
    startvector.y = startposy;
    Vector2 endvector;
    endvector.x = endposx;
    endvector.y = endposy;
    float hue = luaL_checknumber(L, 5);
    float saturation = luaL_checknumber(L, 6);
    float value = luaL_checknumber(L, 7);
    Color color = ColorFromHSV(
    hue, 
    saturation, 
    value);
    DrawLineV(startvector, endvector, color);
    return 0;
}

