// libc includes
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// external lib includes
#include "raylib.h"
#include "lua.h"
#include "lauxlib.h"
#include "luaconf.h"
#include "lualib.h"

// engine includes
#include "headers/manager.h"

int main() {
    createLuaVM();
    getchar();
    return 0;
}
