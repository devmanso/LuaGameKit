#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lua.h"
#include "lauxlib.h"
#include "luaconf.h"
#include "lualib.h"

#include "raylib.h"

// Window functions

static int luaInitWindow(lua_State* L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    const char *title = luaL_checkstring(L, 3);
    InitWindow(width, height, title);
    return 0;
}

static int luaWindowShouldClose(lua_State* L) {
    lua_pushboolean(L, WindowShouldClose());
    return 1;
}

static int luaCloseWindow(lua_State* L) {
    CloseWindow();
    return 0;
}

static int luaIsWindowReady(lua_State *L) {
    lua_pushboolean(L, IsWindowReady());
    return 1;
}

static int luaIsWindowFullscreen(lua_State *L) {
    lua_pushboolean(L, IsWindowFullscreen());
    return 1;
}

static int luaIsWindowHidden(lua_State* L) {
    lua_pushboolean(L, IsWindowHidden());
    return 1;
}

static int luaIsWindowMinimized(lua_State *L) {
    lua_pushboolean(L, IsWindowMinimized());
    return 1;
}

static int luaIsWindowMaximized(lua_State* L) {
    lua_pushboolean(L, IsWindowMaximized());
    return 1;
}

static int luaIsWindowFocused(lua_State* L) {
    lua_pushboolean(L, IsWindowFocused());
    return 1;
}

static int luaIsWindowResized(lua_State* L) {
    lua_pushboolean(L, IsWindowResized());
    return 1;
}

static int luaIsWindowState(lua_State* L) {
    unsigned int flag = luaL_checkinteger(L, 1);
    bool windowState = IsWindowState(flag);
    lua_pushboolean(L, windowState);
    return 1;
}

static int luaSetWindowState(lua_State* L) {
    unsigned int flag = luaL_checkinteger(L, 1);
    SetWindowState(flag);
    return 0;
}

static int luaClearWindowState(lua_State* L) {
    unsigned int flag = luaL_checkinteger(L, 1);
    ClearWindowState(flag);
    return 0;
}

static int luaToggleFullscreen(lua_State* L) {
    ToggleFullscreen();
    return 0;
}

static int luaMaximizeWindow(lua_State* L) {
    MaximizeWindow();
    return 0;
}

static int luaMinimizeWindow(lua_State* L) {
    MinimizeWindow();
    return 0;
}

static int luaRestoreWindow(lua_State* L) {
    RestoreWindow();
    return 0;
}

static int luaSetWindowIcon(lua_State* L) {
    const char* filepath = luaL_checkstring(L, 1);
    Image icon = LoadImage(filepath);
    SetWindowIcon(icon);
    UnloadImage(icon);
    return 0;
}

static int luaSetWindowIcons(lua_State* L) {
    int count = lua_gettop(L);
    Image *images = (Image *)malloc(count * sizeof(Image));

    for (int i = 0; i < count; i++) {
        const char *filename = luaL_checkstring(L, i + 1);
        images[i] = LoadImage(filename);
    }

    SetWindowIcons(images, count);

    for (int i = 0; i < count; i++) {
        UnloadImage(images[i]);
    }

    free(images);

    return 0;
}

static int luaSetWindowTitle(lua_State* L) {
    const char* title = luaL_checkstring(L, 1);
    SetWindowTitle(title);
    return 0;
}

static int luaSetWindowPosition(lua_State* L) {
    unsigned int x = luaL_checkinteger(L, 1);
    unsigned int y = luaL_checkinteger(L, 2);
    SetWindowPosition(x, y);
    return 0;
}

static int luaSetWindowMonitor(lua_State* L) {
    int monitor = luaL_checkinteger(L, 1);
    SetWindowMonitor(monitor);
    return 0;
}

static int luaSetWindowMinSize(lua_State* L) {
    unsigned int width = luaL_checkinteger(L, 1);
    unsigned int height = luaL_checkinteger(L, 2);
    SetWindowMinSize(width, height);
    return 0;
}

static int luaSetWindowSize(lua_State* L) {
    unsigned int width = luaL_checkinteger(L, 1);
    unsigned int height = luaL_checkinteger(L, 2);
    SetWindowSize(width, height);
    return 0;
}

static int luaSetWindowOpacity(lua_State* L) {
    float opacity = luaL_checknumber(L, 1);
    SetWindowOpacity(opacity);
    return 0;
}

static int luaGetWindowHandle(lua_State* L) {
    lua_pushlightuserdata(L, GetWindowHandle());
    return 1;
}

static int luaGetScreenWidth(lua_State* L) {
    lua_pushinteger(L, GetScreenWidth());
    return 1;
}

static int luaGetScreenHeight(lua_State* L) {
    lua_pushinteger(L, GetScreenHeight());
    return 1;
}

static int luaGetRenderWidth(lua_State* L) {
    lua_pushinteger(L, GetRenderWidth());
    return 1;
}

static int luaGetRenderHeight(lua_State* L) {
    lua_pushinteger(L, GetRenderHeight());
    return 1;
}

static int luaGetMonitorCount(lua_State* L) {
    lua_pushinteger(L, GetMonitorCount());
    return 1;
}

static int luaGetCurrentMonitor(lua_State* L) {
    lua_pushinteger(L, GetCurrentMonitor());
    return 1;
}

static int luaGetMonitorPosition(lua_State* L) {
    int monitor = luaL_checkinteger(L, 1);
    Vector2 position = GetMonitorPosition(monitor);
    lua_pushinteger(L, position.x);
    lua_pushinteger(L, position.y);
    return 1;
}

static int luaGetMonitorWidth(lua_State* L) {
    int monitor = luaL_checkinteger(L, 1);
    lua_pushinteger(L, GetMonitorWidth(monitor));
    return 1;
}

static int luaGetMonitorHeight(lua_State* L) {
    int monitor = luaL_checkinteger(L, 1);
    lua_pushinteger(L, GetMonitorHeight(monitor));
    return 1;
}

static int luaGetMonitorPhysicalWidth(lua_State* L) {
    int monitor = luaL_checkinteger(L, 1);
    lua_pushinteger(L, GetMonitorPhysicalWidth(monitor));
    return 1;
}


static int luaGetMonitorPhysicalHeight(lua_State* L) {
    int monitor = luaL_checkinteger(L, 1);
    lua_pushinteger(L, GetMonitorPhysicalHeight(monitor));
    return 1;
}

static int luaGetMonitorRefreshRate(lua_State* L) {
    int monitor = luaL_checkinteger(L, 1);
    lua_pushinteger(L, GetMonitorRefreshRate(monitor));
    return 1;
}

static int luaGetWindowPosition(lua_State* L) {
    Vector2 windowPosition = GetWindowPosition();
    lua_pushinteger(L, windowPosition.x);
    lua_pushinteger(L, windowPosition.y);
    return 1;
}

static int luaGetWindowScaleDPI(lua_State* L) {
    Vector2 windowScaleDPI = GetWindowScaleDPI();
    lua_pushinteger(L, windowScaleDPI.x);
    lua_pushinteger(L, windowScaleDPI.y);
    return 1;
}

// Cursor functions

static int luaShowCursor(lua_State* L) {
    ShowCursor();
    return 0;
}

static int luaHideCursor(lua_State* L) {
    HideCursor();
    return 0;
}

static int luaIsCursorHidden(lua_State* L) {
    lua_pushboolean(L, IsCursorHidden());
    return 1;
}

static int luaEnableCursor(lua_State* L) {
    EnableCursor();
    return 0;
}

static int luaDisableCursor(lua_State* L) {
    DisableCursor();
    return 0;
}

static int luaIsCursorOnScreen(lua_State* L) {
    lua_pushboolean(L, IsCursorOnScreen());
    return 1;
}

// Drawing functions

static int luaClearBackground(lua_State* L) {
    float hue = luaL_checknumber(L, 1);
    float saturation = luaL_checknumber(L, 2);
    float value = luaL_checknumber(L, 3);
    Color color = ColorFromHSV(
    hue, 
    saturation, 
    value);
    ClearBackground(color);
    return 0;
}

static int luaBeginDrawing(lua_State* L) {
    BeginDrawing();
    return 0;
}

static int luaEndDrawing(lua_State* L) {
    EndDrawing();
    return 0;
}

static int luaBeginShaderMode(lua_State* L) {
    const char* vsFilename = luaL_checkstring(L, 1);
    const char* fsFilename = luaL_checkstring(L, 2);
    Shader shader = LoadShader(vsFilename, fsFilename);
    BeginShaderMode(shader);
    return 0;
}