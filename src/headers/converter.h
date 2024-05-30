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

static int luaTextureToTable(lua_State *L, Texture2D texture) {
    
    lua_newtable(L);

    lua_pushstring(L, "id");
    lua_pushinteger(L, texture.id); 
    lua_settable(L, -3);

    lua_pushstring(L, "width");
    lua_pushinteger(L, texture.width);
    lua_settable(L, -3);

    lua_pushstring(L, "height");
    lua_pushinteger(L, texture.height);
    lua_settable(L, -3);

    lua_pushstring(L, "mipmaps");
    lua_pushinteger(L, texture.mipmaps);
    lua_settable(L, -3);

    lua_pushstring(L, "format");
    lua_pushinteger(L, texture.format);
    lua_settable(L, -3);
    return 1;
}

static int luaRectangleToTable(lua_State *L, Rectangle rect) {
    lua_newtable(L);

    lua_pushstring(L, "x");
    lua_pushnumber(L, rect.x);
    lua_settable(L, -3);

    lua_pushstring(L, "y");
    lua_pushnumber(L, rect.y);
    lua_settable(L, -3);

    lua_pushstring(L, "width");
    lua_pushnumber(L, rect.width);
    lua_settable(L, -3);

    lua_pushstring(L, "height");
    lua_pushnumber(L, rect.height);
    lua_settable(L, -3);

    return 1;
}

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

Vector3 luaTableToVector3(lua_State *L, int tableIndex) {
    Vector3 vec3;

    lua_pushstring(L, "x");
    lua_gettable(L, tableIndex);
    vec3.x = luaL_checknumber(L, -1);

    lua_pushstring(L, "y");
    lua_gettable(L, tableIndex);
    vec3.y = luaL_checknumber(L, -1);

    lua_pushstring(L, "z");
    lua_gettable(L, tableIndex);
    vec3.z = luaL_checknumber(L, -1);

    lua_pop(L, 3);

    return vec3;
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

// idk if this works lmao
static Camera* luaTableToCamera(lua_State* L, int index) {
    //Camera camera;
    Camera* camera = (Camera*)malloc(sizeof(Camera));

    lua_pushstring(L, "position");
    lua_gettable(L, index);
    camera->position = (Vector3){0.0f, 0.0f, 0.0f};
    if (lua_istable(L, -1)) {
        lua_pushstring(L, "x");
        lua_gettable(L, -2);
        camera->position.x = luaL_checknumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "y");
        lua_gettable(L, -2);
        camera->position.y = luaL_checknumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "z");
        lua_gettable(L, -2);
        camera->position.z = luaL_checknumber(L, -1);
        lua_pop(L, 1);
    }
    lua_pop(L, 1);

    lua_pushstring(L, "target");
    lua_gettable(L, index);
    camera->target = (Vector3){0.0f, 0.0f, 0.0f};
    if (lua_istable(L, -1)) {
        lua_pushstring(L, "x");
        lua_gettable(L, -2);
        camera->target.x = luaL_checknumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "y");
        lua_gettable(L, -2);
        camera->target.y = luaL_checknumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "z");
        lua_gettable(L, -2);
        camera->target.z = luaL_checknumber(L, -1);
        lua_pop(L, 1);
    }
    lua_pop(L, 1);

    lua_pushstring(L, "up");
    lua_gettable(L, index);
    camera->up = (Vector3){0.0f, 1.0f, 0.0f};
    if (lua_istable(L, -1)) {
        lua_pushstring(L, "x");
        lua_gettable(L, -2);
        camera->up.x = luaL_checknumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "y");
        lua_gettable(L, -2);
        camera->up.y = luaL_checknumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "z");
        lua_gettable(L, -2);
        camera->up.z = luaL_checknumber(L, -1);
        lua_pop(L, 1);
    }
    lua_pop(L, 1);

    lua_pushstring(L, "fovy");
    lua_gettable(L, index);
    camera->fovy = luaL_checknumber(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "projection");
    lua_gettable(L, index);
    camera->projection = luaL_checkinteger(L, -1);
    lua_pop(L, 1);

    return camera;
}

#endif