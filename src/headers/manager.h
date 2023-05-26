#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lua.h"
#include "lauxlib.h"
#include "luaconf.h"
#include "lualib.h"

#include "raylib.h"

#include "core.h"
#include "drawing.h"

const char* findScriptPath(const char* scriptDir, const char* scriptName) {
    // Get the current directory
    const char* currentDir = GetWorkingDirectory();
    if (currentDir == NULL) {
        printf("Failed to get the current directory\n");
        return NULL;
    }

    // Create the script path by appending "/scripts/main.lua" to the current directory
    //const char* scriptDir = "/scripts/";
    //const char* scriptName = "main.lua";
    char* scriptPath = (char*)malloc((strlen(currentDir) + strlen(scriptDir) + strlen(scriptName) + 1) * sizeof(char));
    if (scriptPath == NULL) {
        printf("Failed to allocate memory for script path\n");
        return NULL;
    }

    strcpy(scriptPath, currentDir);
    strcat(scriptPath, scriptDir);
    strcat(scriptPath, scriptName);

    return scriptPath;
}

int loadScript(const char filepath[], lua_State *L) {
    if(luaL_dofile(L, filepath) !=0 ) {
            printf("could not find or load script! \n");
            printf("error: %s\n", lua_tostring(L, -1));
            lua_pop(L, 1);
            return 1;
        } else {
            printf("script call success \n");
            return 0;
        }
    return 0;
}


int createLuaVM() {
    lua_State* L = luaL_newstate();
    //load lua standard library
    luaL_openlibs(L);
    registerCoreBindings(L);
    const char* scriptsDir = findScriptPath("/scripts/", "main.lua");
    loadScript(scriptsDir, L);
    lua_close(L);
    return 0;
}