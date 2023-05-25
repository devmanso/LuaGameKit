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

// Note: this might not work, because Lua doesn't have pointers
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
    lua_pushnumber(L, position.x);
    lua_pushnumber(L, position.y);
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
    lua_pushnumber(L, windowPosition.x);
    lua_pushnumber(L, windowPosition.y);
    return 1;
}

static int luaGetWindowScaleDPI(lua_State* L) {
    Vector2 windowScaleDPI = GetWindowScaleDPI();
    lua_pushnumber(L, windowScaleDPI.x);
    lua_pushnumber(L, windowScaleDPI.y);
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
//TODO: create more mode functions

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

static int luaEndShaderMode(lua_State* L) {
    EndShaderMode();
    return 0;
}

// shader management functions, not available in opengl 1.1
// could probably use some optimisation, but this is fine for now
//TODO: SetShader functions

static int luaLoadShader(lua_State* L) {
    const char* vsFilename = luaL_checkstring(L, 1);
    const char* fsFilename = luaL_checkstring(L, 2);
    LoadShader(vsFilename, fsFilename);
    return 0;
}

static int luaIsShaderReady(lua_State* L) {
    const char* vsFilename = luaL_checkstring(L, 1);
    const char* fsFilename = luaL_checkstring(L, 2);
    Shader shader = LoadShader(vsFilename, fsFilename);
    lua_pushboolean(L, IsShaderReady(shader));
    return 1;
}

static int luaGetShaderLocation(lua_State* L) {
    const char* vsFilename = luaL_checkstring(L, 1);
    const char* fsFilename = luaL_checkstring(L, 2);
    Shader shader = LoadShader(vsFilename, fsFilename);
    const char* uniformName = luaL_checkstring(L, 3);
    lua_pushinteger(L, GetShaderLocation(shader, uniformName));
    return 1;
}

static int luaGetShaderLocationAttrib(lua_State* L) {
    const char* vsFilename = luaL_checkstring(L, 1);
    const char* fsFilename = luaL_checkstring(L, 2);
    Shader shader = LoadShader(vsFilename, fsFilename);
    const char* attribName = luaL_checkstring(L, 3);
    lua_pushinteger(L, GetShaderLocationAttrib(shader, attribName));
    return 1;
}

static int luaUnloadShader(lua_State* L) {

    // It's 12 am and I'm losing my mind
    const char* vsFilename = luaL_checkstring(L, 1);
    const char* fsFilename = luaL_checkstring(L, 2);
    Shader shader = LoadShader(vsFilename, fsFilename);
    UnloadShader(shader);
    return 0;
}


// Timing functions

static int luaSetTargetFPS(lua_State* L) {
    unsigned int fps = luaL_checkinteger(L, 1);
    SetTargetFPS(fps);
    return 0;
}

static int luaGetFPS(lua_State* L) {
    lua_pushinteger(L, GetFPS());
    return 1;
}

static int luaDeltaTime(lua_State* L) {
    lua_pushnumber(L, GetFrameTime());
    return 1;
}

static int luaGetTime(lua_State* L) {
    lua_pushnumber(L, GetTime());
    return 1;
}

// Misc functions

static int luaTakeScreenshot(lua_State* L) {
    const char* filename = luaL_checkstring(L, 1);
    TakeScreenshot(filename);
    return 0;
}

static int luaOpenURL(lua_State* L) {
    const char* url = luaL_checkstring(L, 1);
    OpenURL(url);
    return 0;
}

// Lua already has an in-built IO library for file management, so I'm not writing bindings for Raylib's file management functions here

//TODO: Data compression/encoding functions

// Input functions

// Keyboard input
static int luaIsKeyPressed(lua_State* L) {
    int key = luaL_checkinteger(L, 1);
    lua_pushboolean(L, IsKeyPressed(key));
    return 1;
}

static int luaIsKeyDown(lua_State* L) {
    int key = luaL_checkinteger(L, 1);
    lua_pushboolean(L, IsKeyDown(key));
    return 1;
}

static int luaIsKeyReleased(lua_State* L) {
    int key = luaL_checkinteger(L, 1);
    lua_pushboolean(L, IsKeyReleased(key));
    return 1;
}

static int luaIsKeyUp(lua_State* L) {
    int key = luaL_checkinteger(L, 1);
    lua_pushboolean(L, IsKeyUp(key));
    return 1;
}

static int luaSetExitKey(lua_State* L) {
    int key = luaL_checkinteger(L, 1);
    SetExitKey(key);
    return 0;
}

static int luaGetKeyPressed(lua_State* L) {
    lua_pushinteger(L, GetKeyPressed());
    return 1;
}

static int luaGetCharPressed(lua_State* L) {
    lua_pushinteger(L, GetCharPressed());
    return 1;
}

// Gamepad input

static int luaIsGamepadAvailable(lua_State* L) {
    int gamepad = luaL_checkinteger(L, 1);
    lua_pushboolean(L, IsGamepadAvailable(gamepad));
    return 1;
}

static int luaGetGamepadName(lua_State* L) {
    int gamepad = luaL_checkinteger(L, 1);
    lua_pushstring(L, GetGamepadName(gamepad));
    return 1;
}

static int luaIsGamepadButtonPressed(lua_State* L) {
    int gamepad = luaL_checkinteger(L, 1);
    int button = luaL_checkinteger(L, 2);
    lua_pushboolean(L, IsGamepadButtonPressed(gamepad, button));
    return 1;
}

static int luaIsGamepadButtonDown(lua_State* L) {
    int gamepad = luaL_checkinteger(L, 1);
    int button = luaL_checkinteger(L, 2);
    lua_pushboolean(L, IsGamepadButtonDown(gamepad, button));
    return 1;
}

static int luaIsGamepadButtonReleased(lua_State* L) {
    int gamepad = luaL_checkinteger(L, 1);
    int button = luaL_checkinteger(L, 2);
    lua_pushboolean(L, IsGamepadButtonReleased(gamepad, button));
    return 1;
}

static int luaIsGamepadButtonUp(lua_State* L) {
    int gamepad = luaL_checkinteger(L, 1);
    int button = luaL_checkinteger(L, 2);
    lua_pushboolean(L, IsGamepadButtonUp(gamepad, button));
    return 1;
}

static int luaGetGamepadButtonPressed(lua_State* L) {
    lua_pushinteger(L, GetGamepadButtonPressed());
    return 1;
}

static int luaGetGamepadAxisCount(lua_State* L) {
    int gamepad = luaL_checkinteger(L, 1);
    lua_pushinteger(L, GetGamepadAxisCount(gamepad));
    return 1;
}

static int luaGetGamepadAxisMovement(lua_State* L) {
    int gamepad = luaL_checkinteger(L, 1);
    int axis = luaL_checkinteger(L, 2);
    lua_pushnumber(L, GetGamepadAxisMovement(gamepad, axis));
    return 1;
}

static int luaSetGamepadMappings(lua_State* L) {
    const char* mappings = luaL_checkstring(L, 1);
    lua_pushinteger(L, SetGamepadMappings(mappings));
    return 1;
}

// Mouse input

static int luaIsMouseButtonPressed(lua_State* L) {
    int button = luaL_checkinteger(L, 1);
    lua_pushboolean(L, IsMouseButtonPressed(button));
    return 1;
}

static int luaIsMouseButtonDown(lua_State* L) {
    int button = luaL_checkinteger(L, 1);
    lua_pushboolean(L, IsMouseButtonDown(button));
    return 1;
}

static int luaIsMouseButtonReleased(lua_State* L) {
    int button = luaL_checkinteger(L, 1);
    lua_pushboolean(L, IsMouseButtonReleased(button));
    return 1;
}

static int luaIsMouseButtonUp(lua_State* L) {
    int button = luaL_checkinteger(L, 1);
    lua_pushboolean(L, IsMouseButtonUp(button));
    return 1;
}

static int luaGetMouseX(lua_State* L) {
    lua_pushinteger(L, GetMouseX());
    return 1;
}

static int luaGetMouseY(lua_State* L) {
    lua_pushinteger(L, GetMouseY());
    return 1;
}

static int luaGetMousePosition(lua_State* L) {
    Vector2 mouseposition = GetMousePosition();
    lua_pushnumber(L, mouseposition.x);
    lua_pushnumber(L, mouseposition.y);
    return 1;    
}

static int luaSetMousePosition(lua_State* L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    SetMousePosition(x, y);
    return 0;
}

static int luaSetMouseOffset(lua_State* L) {
    int offsetX = luaL_checkinteger(L, 1);
    int offsetY = luaL_checkinteger(L, 2);
    SetMouseOffset(offsetX, offsetY);
    return 0;
}

static int luaSetMouseScale(lua_State* L) {
    float scaleX = luaL_checknumber(L, 1);
    float scaleY = luaL_checknumber(L, 2);
    SetMouseScale(scaleX, scaleY);
    return 0;
}

static int luaGetMouseWheelMove(lua_State* L) {
    lua_pushnumber(L, GetMouseWheelMove());
    return 0;
}

static int luaGetMouseWheelMoveV(lua_State* L) {
    Vector2 mouseWheelMove = GetMouseWheelMoveV();
    lua_pushnumber(L, mouseWheelMove.x);
    lua_pushnumber(L, mouseWheelMove.y);
    return 1;
}

static int luaSetMouseCursor(lua_State* L) {
    int cursor = luaL_checkinteger(L, 1);
    SetMouseCursor(cursor);
    return 0;
}

// TODO: Touch related functions

void registerCoreBindings(lua_State* L) {
    lua_register(L, "InitWindow", luaInitWindow);
    lua_register(L, "WindowShouldClose", luaWindowShouldClose);
    lua_register(L, "CloseWindow", luaCloseWindow);
    lua_register(L, "IsWindowReady", luaIsWindowReady);
    lua_register(L, "IsWindowFullscreen", luaIsWindowFullscreen);
    lua_register(L, "IsWindowHidden", luaIsWindowHidden);
    lua_register(L, "IsWindowMinimized", luaIsWindowMinimized);
    lua_register(L, "IsWindowMaximised", luaIsWindowMaximized);
    lua_register(L, "IsWindowFocused", luaIsWindowFocused);
    lua_register(L, "IsWindowResized", luaIsWindowResized);
    lua_register(L, "IsWindowState", luaIsWindowState);
    lua_register(L, "ClearWindowState", luaClearWindowState);
    lua_register(L, "ToggleFullscreen", luaToggleFullscreen);
    lua_register(L, "MaximizeWindow", luaMaximizeWindow);
    lua_register(L, "MinimizeWindow", luaMinimizeWindow);
    lua_register(L, "RestoreWindow", luaRestoreWindow);
    lua_register(L, "SetWindowIcon", luaSetWindowIcon);
    lua_register(L, "SetWindowIcons", luaSetWindowIcons);
    lua_register(L, "SetWindowTitle", luaSetWindowTitle);
    lua_register(L, "SetWindowPosition", luaSetWindowPosition);
    lua_register(L, "SetWindowMonitor", luaSetWindowMonitor);
    lua_register(L, "SetWindowMinSize", luaSetWindowMinSize);
    lua_register(L, "SetWindowSize", luaSetWindowSize);
    lua_register(L, "SetWindowOpacity", luaSetWindowOpacity);
    lua_register(L, "GetWindowHandle", luaGetWindowHandle);
    lua_register(L, "GetScreenWidth", luaGetScreenWidth);
    lua_register(L, "GetScreenHeight", luaGetScreenHeight);
    lua_register(L, "GetRenderWidth", luaGetRenderWidth);
    lua_register(L, "GetRenderHeight", luaGetRenderHeight);
    lua_register(L, "GetMonitorCount", luaGetMonitorCount);
    lua_register(L, "GetMonitorPosition", luaGetMonitorPosition);
    lua_register(L, "GetMonitorWidth", luaGetMonitorWidth);
    lua_register(L, "GetMonitorHeight", luaGetMonitorHeight);
    lua_register(L, "GetMonitorPhysicalWidth", luaGetMonitorPhysicalWidth);
    lua_register(L, "GetMonitorPhysicalHeight", luaGetMonitorPhysicalHeight);
    lua_register(L, "GetMonitorRefreshRate", luaGetMonitorRefreshRate);
    lua_register(L, "GetWindowPosition", luaGetWindowPosition);
    lua_register(L, "GetWindowScaleDPI", luaGetWindowScaleDPI);
    lua_register(L, "ShowCursor", luaShowCursor);
    lua_register(L, "HideCursor", luaHideCursor);
    lua_register(L, "IsCursorHidden", luaIsCursorHidden);
    lua_register(L, "EnableCursor", luaEnableCursor);
    lua_register(L, "DisableCursor", luaDisableCursor);
    lua_register(L, "IsCursorOnScreen", luaIsCursorOnScreen);
    lua_register(L, "ClearBackground", luaClearBackground);
    lua_register(L, "BeginDrawing", luaBeginDrawing);
    lua_register(L, "EndDrawing", luaEndDrawing);
    lua_register(L, "BeginShaderMode", luaBeginShaderMode);
    lua_register(L, "EndShaderMode", luaEndShaderMode);
    lua_register(L, "LoadShader", luaLoadShader);
    lua_register(L, "IsShaderReady", luaIsShaderReady);
    lua_register(L, "GetShaderLocation", luaGetShaderLocation);
    lua_register(L, "GetShaderLocationAttrib", luaGetShaderLocationAttrib);
    lua_register(L, "UnloadShader", luaUnloadShader);
    lua_register(L, "SetTargetFPS", luaSetTargetFPS);
    lua_register(L, "GetFPS", luaGetFPS);
    lua_register(L, "DeltaTime", luaDeltaTime);
    lua_register(L, "GetTime", luaGetTime);
    lua_register(L, "TakeScreenshot", luaTakeScreenshot);
    lua_register(L, "OpenURL", luaOpenURL);
    lua_register(L, "IsKeyPressed", luaIsKeyPressed);
    lua_register(L, "IsKeyDown", luaIsKeyDown);
    lua_register(L, "IsKeyReleased", luaIsKeyReleased);
    lua_register(L, "IsKeyUp", luaIsKeyUp);
    lua_register(L, "SetExitKey", luaSetExitKey);
    lua_register(L, "GetKeyPressed", luaGetKeyPressed);
    lua_register(L, "GetCharPressed", luaGetCharPressed);
    lua_register(L, "IsGamepadAvailable", luaIsGamepadAvailable);
    lua_register(L, "GetGamepadName", luaGetGamepadName);
    lua_register(L, "IsGamepadButtonPressed", luaIsGamepadButtonPressed);
    lua_register(L, "IsGamepadButtonDown", luaIsGamepadButtonDown);
    lua_register(L, "IsGamepadButtonReleased", luaIsGamepadButtonReleased);
    lua_register(L, "IsGamepadButtonUp", luaIsGamepadButtonUp);
    lua_register(L, "GetGamepadButtonPressed", luaGetGamepadButtonPressed);
    lua_register(L, "GetGamepadAxisCount", luaGetGamepadAxisCount);
    lua_register(L, "GetGamepadAxisMovement", luaGetGamepadAxisMovement);
    lua_register(L, "SetGamepadMappings", luaSetGamepadMappings);
    lua_register(L, "IsMouseButtonPressed", luaIsMouseButtonPressed);
    lua_register(L, "IsMouseButtonDown", luaIsMouseButtonDown);
    lua_register(L, "IsMouseButtonReleased", luaIsMouseButtonReleased);
    lua_register(L, "IsMouseButtonUp", luaIsMouseButtonUp);
    lua_register(L, "GetMouseX", luaGetMouseX);
    lua_register(L, "GetMouseY", luaGetMouseY);
    lua_register(L, "GetMousePosition", luaGetMousePosition);
    lua_register(L, "SetMousePosition", luaSetMousePosition);
    lua_register(L, "SetMouseOffset", luaSetMouseOffset);
    lua_register(L, "SetMouseScale", luaSetMouseScale);
    lua_register(L, "GetMouseWhellMove", luaGetMouseWheelMove);
    lua_register(L, "GetMouseWheelMoveV", luaGetMouseWheelMoveV);
    lua_register(L, "SetMouseCursor", luaSetMouseCursor);
}




