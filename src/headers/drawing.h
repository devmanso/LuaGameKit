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
    // float startposx = luaL_checknumber(L, 1);
    // float startposy = luaL_checknumber(L, 2);
    // float endposx = luaL_checknumber(L, 3);
    // float endposy = luaL_checknumber(L, 4);
    Vector2 startvector = luaTableToVector2(L, 1);
    Vector2 endvector = luaTableToVector2(L, 2);
    // Vector2 startvector;
    // startvector.x = startposx;
    // startvector.y = startposy;
    // Vector2 endvector;
    // endvector.x = endposx;
    // endvector.y = endposy;
    float hue = luaL_checknumber(L, 3);
    float saturation = luaL_checknumber(L, 4);
    float value = luaL_checknumber(L, 5);
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

// static int lua_drawlinestrip(lua_State *L) {
//     int hexValue = luaL_checkinteger(L, 1);

//     int numPoints = lua_gettop(L) - 1;
//     if (numPoints % 2 != 0) {
//         return luaL_error(L, "Incorrect number of arguments for DrawLineStrip. Must provide an even number of points.");
//     }

//     int numVertices = numPoints / 2;
//     Vector2 *vertices = malloc(sizeof(Vector2) * numVertices);

//     for (int i = 0; i < numPoints; i += 2) {
//         float x = luaL_checknumber(L, i + 2);
//         float y = luaL_checknumber(L, i + 3);
//         vertices[i / 2] = (Vector2){x, y};
//     }

//     DrawLineStrip(vertices, numVertices, GetColor(hexValue));

//     free(vertices);
//     return 0;
// }


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

static int luaDrawCircleV(lua_State *L) {
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
    Vector2 center = {centerx, centery};
    DrawCircleV(center, radius, color);
    return 0;
}

static int luaDrawCircleLines(lua_State *L) {
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
    DrawCircleLines(centerx, centery, radius, color);
    return 0;
}

static int luaDrawEllipse(lua_State *L) {
    int centerx = luaL_checkinteger(L, 1);
    int centery = luaL_checkinteger(L, 2);
    float radiush = luaL_checknumber(L, 3);
    float radiusv = luaL_checknumber(L, 4);
    float hue = luaL_checknumber(L, 5);
    float saturation = luaL_checknumber(L, 6);
    float value = luaL_checknumber(L, 7);
    Color color = ColorFromHSV(
            hue,
            saturation,
            value);
    DrawEllipse(centerx, centery, radiush, radiusv, color);
    return 0;
}

static int luaDrawEllipseLines(lua_State *L) {
    int centerx = luaL_checkinteger(L, 1);
    int centery = luaL_checkinteger(L, 2);
    float radiush = luaL_checknumber(L, 3);
    float radiusv = luaL_checknumber(L, 4);
    float hue = luaL_checknumber(L, 5);
    float saturation = luaL_checknumber(L, 6);
    float value = luaL_checknumber(L, 7);
    Color color = ColorFromHSV(
            hue,
            saturation,
            value);
    DrawEllipseLines(centerx, centery, radiush, radiusv, color);
    return 0;
}

static int luaDrawRing(lua_State *L) {
    int centerx = luaL_checkinteger(L, 1);
    int centery = luaL_checkinteger(L, 2);
    float innerRadius = luaL_checknumber(L, 3);
    float outerRadius = luaL_checknumber(L, 4);
    float startAngle = luaL_checknumber(L, 5);
    float endAngle = luaL_checknumber(L, 6);
    int segments = luaL_checkinteger(L, 7);
    float hue = luaL_checknumber(L, 8);
    float saturation = luaL_checknumber(L, 9);
    float value = luaL_checknumber(L, 10);
    Color color = ColorFromHSV(
            hue,
            saturation,
            value);
    Vector2 center = {centerx, centery};
    DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
    return 0;
}

static int luaDrawRingLines(lua_State *L) {
    int centerx = luaL_checkinteger(L, 1);
    int centery = luaL_checkinteger(L, 2);
    float innerRadius = luaL_checknumber(L, 3);
    float outerRadius = luaL_checknumber(L, 4);
    float startAngle = luaL_checknumber(L, 5);
    float endAngle = luaL_checknumber(L, 6);
    int segments = luaL_checkinteger(L, 7);
    float hue = luaL_checknumber(L, 8);
    float saturation = luaL_checknumber(L, 9);
    float value = luaL_checknumber(L, 10);
    Color color = ColorFromHSV(
            hue,
            saturation,
            value);
    Vector2 center = {centerx, centery};
    DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
    return 0;
}

static int luaDrawRectangle(lua_State *L) {
    int posx = luaL_checkinteger(L, 1);
    int posy = luaL_checkinteger(L, 2);
    int width = luaL_checkinteger(L, 3);
    int height = luaL_checkinteger(L, 4);
    float hue = luaL_checknumber(L, 5);
    float saturation = luaL_checknumber(L, 6);
    float value = luaL_checknumber(L, 7);
    Color color = ColorFromHSV(
            hue,
            saturation,
            value);
    DrawRectangle(posx, posy, width, height, color);
    return 0;
}

static int luaDrawRectangleLines(lua_State *L) {
    int posx = luaL_checkinteger(L, 1);
    int posy = luaL_checkinteger(L, 2);
    int width = luaL_checkinteger(L, 3);
    int height = luaL_checkinteger(L, 4);
    float hue = luaL_checknumber(L, 5);
    float saturation = luaL_checknumber(L, 6);
    float value = luaL_checknumber(L, 7);
    Color color = ColorFromHSV(
            hue,
            saturation,
            value);
    DrawRectangleLines(posx, posy, width, height, color);
    return 0;
}

static int luaDrawTriangle(lua_State *L) {
    int topVertx = luaL_checkinteger(L, 1);
    int topVerty = luaL_checkinteger(L, 2);
    Vector2 topVert = {topVertx, topVerty};
    int leftVertx = luaL_checkinteger(L, 3);
    int leftVerty = luaL_checkinteger(L, 4);
    Vector2 leftVert = {leftVertx, leftVerty};
    int rightVertx = luaL_checkinteger(L, 5);
    int rightVerty = luaL_checkinteger(L, 6);
    Vector2 rightVert = {rightVertx, rightVerty};
    float hue = luaL_checknumber(L, 7);
    float saturation = luaL_checknumber(L, 8);
    float value = luaL_checknumber(L, 9);
    Color color = ColorFromHSV(
            hue,
            saturation,
            value);
    DrawTriangle(topVert, leftVert, rightVert, color);
    return 0;
}

static int luaDrawTriangleLines(lua_State *L) {
    int topVertx = luaL_checkinteger(L, 1);
    int topVerty = luaL_checkinteger(L, 2);
    Vector2 topVert = {topVertx, topVerty};
    int leftVertx = luaL_checkinteger(L, 3);
    int leftVerty = luaL_checkinteger(L, 4);
    Vector2 leftVert = {leftVertx, leftVerty};
    int rightVertx = luaL_checkinteger(L, 5);
    int rightVerty = luaL_checkinteger(L, 6);
    Vector2 rightVert = {rightVertx, rightVerty};
    float hue = luaL_checknumber(L, 7);
    float saturation = luaL_checknumber(L, 8);
    float value = luaL_checknumber(L, 9);
    Color color = ColorFromHSV(
            hue,
            saturation,
            value);
    DrawTriangleLines(topVert, leftVert, rightVert, color);
    return 0;
}

static int luaDrawPoly(lua_State *L) {
    int centerx = luaL_checkinteger(L, 1);
    int centery = luaL_checkinteger(L, 2);
    Vector2 center = {centerx, centery};
    int sides = luaL_checkinteger(L, 3);
    float radius = luaL_checknumber(L, 4);
    float rotation = luaL_checknumber(L, 5);
    float hue = luaL_checknumber(L, 6);
    float saturation = luaL_checknumber(L, 7);
    float value = luaL_checknumber(L, 8);
    Color color = ColorFromHSV(
            hue,
            saturation,
            value);
    DrawPoly(center, sides, radius, rotation, color);
    return 0;
}

static int luaDrawPolyLines(lua_State *L) {
    int centerx = luaL_checkinteger(L, 1);
    int centery = luaL_checkinteger(L, 2);
    Vector2 center = {centerx, centery};
    int sides = luaL_checkinteger(L, 3);
    float radius = luaL_checknumber(L, 4);
    float rotation = luaL_checknumber(L, 5);
    float hue = luaL_checknumber(L, 6);
    float saturation = luaL_checknumber(L, 7);
    float value = luaL_checknumber(L, 8);
    Color color = ColorFromHSV(
            hue,
            saturation,
            value);
    DrawPolyLines(center, sides, radius, rotation, color);
    return 0;
}

// collision check functions

static int luaCheckCollisionCircles(lua_State *L) {
    Vector2 center1 = luaTableToVector2(L, 1);
    float radius1 = luaL_checknumber(L, 2);
    Vector2 center2 = luaTableToVector2(L, 3);
    float radius2 = luaL_checknumber(L, 4);
    bool isColliding = CheckCollisionCircles(center1, radius1, center2, radius2);
    lua_pushboolean(L, isColliding);
    return 1;
}

static int luaCheckCollisionRecs(lua_State *L) {
    // extract the two rects as Lua tables
    Rectangle rec1 = luaTableToRectangle(L, 1);
    Rectangle rec2 = luaTableToRectangle(L, 2);
    bool isColliding = CheckCollisionRecs(rec1, rec2);
    lua_pushboolean(L, isColliding);
    return 1;
}

static int luaCheckCollisionCircleRec(lua_State *L) {
    Vector2 center = luaTableToVector2(L, 1);
    float radius = luaL_checknumber(L, 2);
    Rectangle rect = luaTableToRectangle(L, 3);
    bool isColliding = CheckCollisionCircleRec(center, radius, rect);
    lua_pushboolean(L, isColliding);
    return 1;
}

static int luaCheckCollisionPointRec(lua_State *L) {
    Vector2 point = luaTableToVector2(L, 1);
    Rectangle rect = luaTableToRectangle(L, 2);
    bool isColliding = CheckCollisionPointRec(point, rect);
    lua_pushboolean(L, isColliding);
    return 1;
}

static int luaCheckCollisionPointCircle(lua_State *L) {
    Vector2 point = luaTableToVector2(L, 1);
    Vector2 center = luaTableToVector2(L, 2);
    float radius = luaL_checknumber(L, 3);
    bool isColliding = CheckCollisionPointCircle(point, center, radius);
    lua_pushboolean(L, isColliding);
    return 1;
}

static int luaCheckCollisionPointTriangle(lua_State *L) {
    Vector2 point = luaTableToVector2(L, 1);
    Vector2 triVert1 = luaTableToVector2(L, 2);
    Vector2 triVert2 = luaTableToVector2(L, 3);
    Vector2 triVert3 = luaTableToVector2(L, 4);
    bool isColliding = CheckCollisionPointTriangle(point, triVert1, triVert2, triVert3);
    lua_pushboolean(L, isColliding);
    return 1;
}

void registerDrawingBindings(lua_State *L) {
    lua_register(L, "DrawPixel", luaDrawPixel);
    lua_register(L, "DrawPixelV", luaDrawPixelV);
    lua_register(L, "DrawLine", luaDrawLine);
    lua_register(L, "DrawLineV", luaDrawLineV);
    lua_register(L, "DrawLineEx", luaDrawLineEx);
    lua_register(L, "DrawLineBezier", luaDrawLineBezier);
    lua_register(L, "DrawLineBezierQuad", luaDrawLineBezierQuad);
    lua_register(L, "DrawLineBezierCubic", luaDrawLineBezierCubic);
    lua_register(L, "DrawCircle", luaDrawCircle);
    lua_register(L, "DrawCircleSector", luaDrawCircleSector);
    lua_register(L, "DrawCircleSectorLines", luaDrawCircleSectorLines);
    lua_register(L, "DrawCircleGradient", luaDrawCircleGradient);
    lua_register(L, "DrawCircleV", luaDrawCircleV);
    lua_register(L, "DrawCircleLines", luaDrawCircleLines);
    lua_register(L, "DrawEllipse", luaDrawEllipse);
    lua_register(L, "DrawEllipseLines", luaDrawEllipseLines);
    lua_register(L, "DrawRing", luaDrawRing );
    lua_register(L, "DrawRingLines", luaDrawRingLines);
    lua_register(L, "DrawRectangle", luaDrawRectangle );
    lua_register(L, "DrawRectangleLines", luaDrawRectangleLines );
    lua_register(L, "DrawTriangle", luaDrawTriangle );
    lua_register(L, "DrawTriangleLines", luaDrawTriangleLines);
    lua_register(L, "DrawPoly", luaDrawPoly);
    lua_register(L, "DrawPolyLines", luaDrawPolyLines);
    lua_register(L, "CheckCollisionCircles", luaCheckCollisionCircles);
    lua_register(L, "CheckCollisionRecs", luaCheckCollisionRecs);
    lua_register(L, "CheckCollisionCircleRec", luaCheckCollisionCircleRec);
    lua_register(L, "CheckCollisionPointRec", luaCheckCollisionPointRec);
    lua_register(L, "CheckCollisionPointCircle", luaCheckCollisionPointCircle);
    lua_register(L, "CheckCollisionPointTriangle", luaCheckCollisionPointTriangle);
}