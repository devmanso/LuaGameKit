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

static int luaDrawLineEx(lua_State* L) {
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
    float thickness = luaL_checknumber(L, 5);
    float hue = luaL_checknumber(L, 6);
    float saturation = luaL_checknumber(L, 7);
    float value = luaL_checknumber(L, 8);
    Color color = ColorFromHSV(
    hue, 
    saturation, 
    value);
    DrawLineEx(startvector, endvector, thickness, color);
    return 0;
}

static int luaDrawLineBezier(lua_State* L) {
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
    float thickness = luaL_checknumber(L, 5);
    float hue = luaL_checknumber(L, 6);
    float saturation = luaL_checknumber(L, 7);
    float value = luaL_checknumber(L, 8);
    Color color = ColorFromHSV(
    hue, 
    saturation, 
    value);
    DrawLineBezier(startvector, endvector, thickness, color);
    return 0;
}

static int luaDrawLineBezierQuad(lua_State* L) {
    float startposx = luaL_checknumber(L, 1);
    float startposy = luaL_checknumber(L, 2);
    float endposx = luaL_checknumber(L, 3);
    float endposy = luaL_checknumber(L, 4);
    float controlx = luaL_checknumber(L, 5);
    float controly = luaL_checknumber(L, 6);
    Vector2 startvector;
    startvector.x = startposx;
    startvector.y = startposy;
    Vector2 endvector;
    endvector.x = endposx;
    endvector.y = endposy;
    Vector2 controlvector;
    controlvector.x = controlx;
    controlvector.y = controly;
    float thickness = luaL_checknumber(L, 7);
    float hue = luaL_checknumber(L, 8);
    float saturation = luaL_checknumber(L, 9);
    float value = luaL_checknumber(L, 10);
    Color color = ColorFromHSV(
    hue, 
    saturation, 
    value);
    DrawLineBezierQuad(startvector, endvector, controlvector, thickness, color);
    return 0;
}


static int luaDrawLineBezierCubic(lua_State *L) {
    float startposx = luaL_checknumber(L, 1);
    float startposy = luaL_checknumber(L, 2);
    float endposx = luaL_checknumber(L, 3);
    float endposy = luaL_checknumber(L, 4);
    float startcontrolx = luaL_checknumber(L, 5);
    float startcontroly = luaL_checknumber(L, 6);
    float endcontrolx = luaL_checknumber(L, 7);
    float endcontroly = luaL_checknumber(L, 8);
    Vector2 startpos = {startposx, startposy};
    Vector2 endpos = {endposx, endposy};
    Vector2 startcontrol = {startcontrolx, startcontroly};
    Vector2 endcontrol = {endcontrolx, endcontroly};
    float thickness = luaL_checknumber(L, 9);
    float hue = luaL_checknumber(L, 9);
    float saturation = luaL_checknumber(L, 10);
    float value = luaL_checknumber(L, 11);
    Color color = ColorFromHSV(
    hue, 
    saturation, 
    value);
    DrawLineBezierCubic(startpos, endpos, startcontrol, endcontrol, thickness, color);
    return 0;
}

static int lua_drawlinestrip(lua_State *L) {
    int hexValue = luaL_checkinteger(L, 1);

    int numPoints = lua_gettop(L) - 1;
    if (numPoints % 2 != 0) {
        return luaL_error(L, "Incorrect number of arguments for DrawLineStrip. Must provide an even number of points.");
    }

    int numVertices = numPoints / 2;
    Vector2 *vertices = malloc(sizeof(Vector2) * numVertices);

    for (int i = 0; i < numPoints; i += 2) {
        float x = luaL_checknumber(L, i + 2);
        float y = luaL_checknumber(L, i + 3);
        vertices[i / 2] = (Vector2){x, y};
    }

    DrawLineStrip(vertices, numVertices, GetColor(hexValue));

    free(vertices);
    return 0;
}


static int luaDrawCircle(lua_State *L) {
    int centerX = luaL_checkinteger(L, 1);
    int centerY = luaL_checkinteger(L, 2);
    float radius = luaL_checknumber(L, 3);

    float hue = luaL_checknumber(L, 4);
    float saturation = luaL_checknumber(L, 5);
    float value = luaL_checknumber(L, 6);
    Color color = ColorFromHSV(
    hue, 
    saturation, 
    value);

    DrawCircle(centerX, centerY, radius, color);

    return 0;
}

static int luaDrawCircleSector(lua_State *L) {
    float centerx = luaL_checknumber(L, 1);
    float centery = luaL_checknumber(L, 2);
    float radius = luaL_checknumber(L, 3);
    float startAngle = luaL_checknumber(L, 4);
    float endAngle = luaL_checknumber(L, 5);
    int segments = luaL_checkinteger(L, 6);
    float hue = luaL_checknumber(L, 7);
    float saturation = luaL_checknumber(L, 8);
    float value = luaL_checknumber(L, 9);
    Color color = ColorFromHSV(
    hue, 
    saturation, 
    value);
    Vector2 center = {centerx, centery};
    DrawCircleSector(center, radius, startAngle, endAngle, segments, color);
    return 0;
}

static int luaDrawCircleSectorLines(lua_State *L) {
    float centerx = luaL_checknumber(L, 1);
    float centery = luaL_checknumber(L, 2);
    float radius = luaL_checknumber(L, 3);
    float startAngle = luaL_checknumber(L, 4);
    float endAngle = luaL_checknumber(L, 5);
    int segments = luaL_checkinteger(L, 6);
    float hue = luaL_checknumber(L, 7);
    float saturation = luaL_checknumber(L, 8);
    float value = luaL_checknumber(L, 9);
    Color color = ColorFromHSV(
    hue, 
    saturation, 
    value);
    Vector2 center = {centerx, centery};
    DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, color);
    return 0;
}

static int luaDrawCircleGradient(lua_State *L) {
    int centerx = luaL_checkinteger(L, 1);
    int centery = luaL_checkinteger(L, 2);
    float radius = luaL_checknumber(L, 3);
    float hue = luaL_checknumber(L, 4);
    float saturation = luaL_checknumber(L, 5);
    float value = luaL_checknumber(L, 6);
    Color color = ColorFromHSV(
    hue, 
    saturation, 
    value);
    float hue2 = luaL_checknumber(L, 7);
    float saturation2 = luaL_checknumber(L, 8);
    float value2 = luaL_checknumber(L, 9);
    Color color2 = ColorFromHSV(
    hue2, 
    saturation2, 
    value2);
    DrawCircleGradient(centerx, centery, radius, color, color2);
    return 0;
}



