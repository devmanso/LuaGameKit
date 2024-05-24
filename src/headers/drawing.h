#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lua.h"
#include "lauxlib.h"
#include "luaconf.h"
#include "lualib.h"

#include "raylib.h"
#include "converter.h"

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
    Vector2 vector = luaTableToVector2(L, 1);
    Color color = luaTableToHSVColor(L, 2);
    DrawPixelV(vector, color);
    return 0;
}

static int luaDrawLine(lua_State* L) {
    int startposx = luaL_checkinteger(L, 1);
    int startposy = luaL_checkinteger(L, 2);
    int endposx = luaL_checkinteger(L, 3);
    int endposy = luaL_checkinteger(L, 4);
    Color color = luaTableToHSVColor(L, 5);
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
    Color color = luaTableToHSVColor(L, 3);
    DrawLineV(startvector, endvector, color);
    return 0;
}

static int luaDrawLineEx(lua_State* L) {
    Vector2 startvector = luaTableToVector2(L, 1);
    Vector2 endvector = luaTableToVector2(L, 2);
    float thickness = luaL_checknumber(L, 3);
    Color color = luaTableToHSVColor(L, 4);
    DrawLineEx(startvector, endvector, thickness, color);
    return 0;
}

static int luaDrawLineBezier(lua_State* L) {
    Vector2 startvector = luaTableToVector2(L, 1);
    Vector2 endvector = luaTableToVector2(L, 2);
    float thickness = luaL_checknumber(L, 3);
    Color color = luaTableToHSVColor(L, 4);
    DrawLineBezier(startvector, endvector, thickness, color);
    return 0;
}

static int luaDrawLineBezierQuad(lua_State* L) {
    Vector2 startvector = luaTableToVector2(L, 1);
    Vector2 endvector = luaTableToVector2(L, 2);
    Vector2 controlvector = luaTableToVector2(L, 3);
    float thickness = luaL_checknumber(L, 4);
    Color color = luaTableToHSVColor(L, 5);
    DrawLineBezierQuad(startvector, endvector, controlvector, thickness, color);
    return 0;
}


static int luaDrawLineBezierCubic(lua_State *L) {
    Vector2 startpos = luaTableToVector2(L, 1);
    Vector2 endpos = luaTableToVector2(L, 2);
    Vector2 startcontrol = luaTableToVector2(L, 3);
    Vector2 endcontrol = luaTableToVector2(L, 4);
    float thickness = luaL_checknumber(L, 5);
    Color color = luaTableToHSVColor(L, 6);
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

    Color color = luaTableToHSVColor(L, 4);
    DrawCircle(centerX, centerY, radius, color);

    return 0;
}

static int luaDrawCircleSector(lua_State *L) {
    Vector2 center = luaTableToVector2(L, 1);
    float radius = luaL_checknumber(L, 2);
    float startAngle = luaL_checknumber(L, 3);
    float endAngle = luaL_checknumber(L, 4);
    int segments = luaL_checkinteger(L, 5);
    Color color = luaTableToHSVColor(L, 6);
    DrawCircleSector(center, radius, startAngle, endAngle, segments, color);
    return 0;
}

static int luaDrawCircleSectorLines(lua_State *L) {
    Vector2 center = luaTableToVector2(L, 1);
    float radius = luaL_checknumber(L, 2);
    float startAngle = luaL_checknumber(L, 3);
    float endAngle = luaL_checknumber(L, 4);
    int segments = luaL_checkinteger(L, 5);
    Color color = luaTableToHSVColor(L, 6);
    DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, color);
    return 0;
}

static int luaDrawCircleGradient(lua_State *L) {
    int centerx = luaL_checkinteger(L, 1);
    int centery = luaL_checkinteger(L, 2);
    float radius = luaL_checknumber(L, 3);
    Color color = luaTableToHSVColor(L, 4);
    Color color2 = luaTableToHSVColor(L, 5);
    DrawCircleGradient(centerx, centery, radius, color, color2);
    return 0;
}

static int luaDrawCircleV(lua_State *L) {
    Vector2 center = luaTableToVector2(L, 1);
    float radius = luaL_checknumber(L, 2);
    Color color = luaTableToHSVColor(L, 3);
    DrawCircleV(center, radius, color);
    return 0;
}

static int luaDrawCircleLines(lua_State *L) {
    int centerx = luaL_checkinteger(L, 1);
    int centery = luaL_checkinteger(L, 2);
    float radius = luaL_checknumber(L, 3);
    Color color = luaTableToHSVColor(L, 4);
    DrawCircleLines(centerx, centery, radius, color);
    return 0;
}

static int luaDrawEllipse(lua_State *L) {
    int centerx = luaL_checkinteger(L, 1);
    int centery = luaL_checkinteger(L, 2);
    float radiush = luaL_checknumber(L, 3);
    float radiusv = luaL_checknumber(L, 4);
    Color color = luaTableToHSVColor(L, 5);
    DrawEllipse(centerx, centery, radiush, radiusv, color);
    return 0;
}

static int luaDrawEllipseLines(lua_State *L) {
    int centerx = luaL_checkinteger(L, 1);
    int centery = luaL_checkinteger(L, 2);
    float radiush = luaL_checknumber(L, 3);
    float radiusv = luaL_checknumber(L, 4);
    Color color = luaTableToHSVColor(L, 5);
    DrawEllipseLines(centerx, centery, radiush, radiusv, color);
    return 0;
}

static int luaDrawRing(lua_State *L) {
    Vector2 center = luaTableToVector2(L, 1);
    float innerRadius = luaL_checknumber(L, 2);
    float outerRadius = luaL_checknumber(L, 3);
    float startAngle = luaL_checknumber(L, 4);
    float endAngle = luaL_checknumber(L, 5);
    int segments = luaL_checkinteger(L, 6);
    Color color = luaTableToHSVColor(L, 7);
    DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
    return 0;
}

static int luaDrawRingLines(lua_State *L) {
    Vector2 center = luaTableToVector2(L, 1);
    float innerRadius = luaL_checknumber(L, 2);
    float outerRadius = luaL_checknumber(L, 3);
    float startAngle = luaL_checknumber(L, 4);
    float endAngle = luaL_checknumber(L, 5);
    int segments = luaL_checkinteger(L, 6);
    Color color = luaTableToHSVColor(L, 7);
    
    DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
    return 0;
}

static int luaDrawRectangle(lua_State *L) {
    int posx = luaL_checkinteger(L, 1);
    int posy = luaL_checkinteger(L, 2);
    int width = luaL_checkinteger(L, 3);
    int height = luaL_checkinteger(L, 4);
    Color color = luaTableToHSVColor(L, 5);
    DrawRectangle(posx, posy, width, height, color);
    return 0;
}

static int luaDrawRectangleLines(lua_State *L) {
    int posx = luaL_checkinteger(L, 1);
    int posy = luaL_checkinteger(L, 2);
    int width = luaL_checkinteger(L, 3);
    int height = luaL_checkinteger(L, 4);
    Color color = luaTableToHSVColor(L, 5);
    DrawRectangleLines(posx, posy, width, height, color);
    return 0;
}

static int luaDrawTriangle(lua_State *L) {
    Vector2 topVert = luaTableToVector2(L, 1);
    Vector2 leftVert = luaTableToVector2(L, 2);
    Vector2 rightVert = luaTableToVector2(L, 3);
    Color color = luaTableToHSVColor(L, 4);
    DrawTriangle(topVert, leftVert, rightVert, color);
    return 0;
}

static int luaDrawTriangleLines(lua_State *L) {
    Vector2 topVert = luaTableToVector2(L, 1);
    Vector2 leftVert = luaTableToVector2(L, 2);
    Vector2 rightVert = luaTableToVector2(L, 3);
    Color color = luaTableToHSVColor(L, 4);
    DrawTriangleLines(topVert, leftVert, rightVert, color);
    return 0;
}

static int luaDrawPoly(lua_State *L) {
    Vector2 center = luaTableToVector2(L, 1);
    int sides = luaL_checknumber(L, 2);
    float radius = luaL_checknumber(L, 3);
    float rotation = luaL_checknumber(L, 4);
    Color color = luaTableToHSVColor(L, 5);
    DrawPoly(center, sides, radius, rotation, color);
    return 0;
}

static int luaDrawPolyLines(lua_State *L) {
    Vector2 center = luaTableToVector2(L, 1);
    int sides = luaL_checknumber(L, 2);
    float radius = luaL_checknumber(L, 3);
    float rotation = luaL_checknumber(L, 4);
    Color color = luaTableToHSVColor(L, 5);
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

static int luaCheckCollisionPointPoly(lua_State *L) {
    Vector2 point = luaTableToVector2(L, 1);
    int pointCount = luaL_len(L, 2);
    Vector2 *points = malloc(sizeof(Vector2) * pointCount);
    for (int i = 0; i < pointCount; i++) {
        lua_rawgeti(L, 2, i + 1);
        points[i] = luaTableToVector2(L, -1);
        lua_pop(L, 1);
    }
    bool isColliding = CheckCollisionPointPoly(point, points, pointCount);
    free(points);
    lua_pushboolean(L, isColliding);
    return 1;
}

static int luaCheckCollisionLines(lua_State *L) {
    Vector2 startPos1 = luaTableToVector2(L, 1);
    Vector2 endPos1 = luaTableToVector2(L, 2);
    Vector2 startPos2 = luaTableToVector2(L, 3);
    Vector2 endPos2 = luaTableToVector2(L, 4);
    Vector2 collisionPoint;
    bool isColliding = CheckCollisionLines(startPos1, endPos1, startPos2, endPos2, &collisionPoint);
    if (isColliding) {
        // Push collisionPoint as a Lua table
        lua_newtable(L);
        lua_pushnumber(L, collisionPoint.x);
        lua_setfield(L, -2, "x");
        lua_pushnumber(L, collisionPoint.y);
        lua_setfield(L, -2, "y");
    } else {
        // Push nil if there's no collision
        lua_pushnil(L);
    }
    return 1;
}

static int luaCheckCollisionPointLine(lua_State *L) {
    Vector2 point = luaTableToVector2(L, 1);
    Vector2 p1 = luaTableToVector2(L, 2);
    Vector2 p2 = luaTableToVector2(L, 3);
    int threshold = lua_tointeger(L, 4);
    bool isColliding = CheckCollisionPointLine(point, p1, p2, threshold);
    lua_pushboolean(L, isColliding);
    return 1;
}

static int luaGetCollisionRec(lua_State *L) {
    Rectangle rec1 = luaTableToRectangle(L, 1);
    Rectangle rec2 = luaTableToRectangle(L, 2);
    Rectangle result = GetCollisionRec(rec1, rec2);
    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    lua_pushnumber(L, result.width);
    lua_setfield(L, -2, "width");
    lua_pushnumber(L, result.height);
    lua_setfield(L, -2, "height");
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
    lua_register(L, "CheckCollisionPointPoly", luaCheckCollisionPointPoly);
    lua_register(L, "CheckCollisionLines", luaCheckCollisionLines);
    lua_register(L, "CheckCollisionPointLine", luaCheckCollisionPointLine);
    lua_register(L, "GetCollisionRec", luaGetCollisionRec);
}