#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lua.h"
#include "lauxlib.h"
#include "luaconf.h"
#include "lualib.h"

#include "raylib.h"

#include "../miniz.h"
#include "core.h"
#include "drawing.h"
#include "text.h"

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


int loadScriptFromMemory(const char* script, size_t script_size, lua_State* L) {
    if (luaL_loadbuffer(L, script, script_size, "main.lua") || lua_pcall(L, 0, 0, 0)) {
        printf("Error: %s\n", lua_tostring(L, -1));
        return -1;
    }
    return 0;
}


char* extractFileFromZip(const char* zip_file_path, const char* file_name, size_t* file_size) {
    // Read the zip file into memory
    mz_zip_archive zip_archive;
    memset(&zip_archive, 0, sizeof(zip_archive));

    // Initialize the zip archive
    if (!mz_zip_reader_init_file(&zip_archive, zip_file_path, 0)) {
        printf("mz_zip_reader_init_file() failed!\n");
        return NULL;
    }

    // Find the file index
    int file_index = mz_zip_reader_locate_file(&zip_archive, file_name, NULL, 0);
    if (file_index < 0) {
        printf("File '%s' not found in the zip archive!\n", file_name);
        mz_zip_reader_end(&zip_archive);
        return NULL;
    }

    // Get the file's information
    mz_zip_archive_file_stat file_stat;
    if (!mz_zip_reader_file_stat(&zip_archive, file_index, &file_stat)) {
        printf("mz_zip_reader_file_stat() failed!\n");
        mz_zip_reader_end(&zip_archive);
        return NULL;
    }

    // Allocate memory for the file
    char* file_data = (char*)malloc(file_stat.m_uncomp_size);
    if (!file_data) {
        printf("Memory allocation failed!\n");
        mz_zip_reader_end(&zip_archive);
        return NULL;
    }

    // Extract the file to memory
    if (!mz_zip_reader_extract_to_mem(&zip_archive, file_index, file_data, file_stat.m_uncomp_size, 0)) {
        printf("mz_zip_reader_extract_to_mem() failed!\n");
        free(file_data);
        mz_zip_reader_end(&zip_archive);
        return NULL;
    }

    // Clean up and return the file data
    *file_size = file_stat.m_uncomp_size;
    mz_zip_reader_end(&zip_archive);
    return file_data;
}

int createLuaVM() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    registerCoreBindings(L);
    registerDrawingBindings(L);
    registerTextBindings(L);

    // Extract main.lua from app.zip into memory
    size_t script_size;
    const char* zip_path = "app.zip";
    const char* file_name = "app/scripts/main.lua";
    char* script = extractFileFromZip(zip_path, file_name, &script_size);
    if (!script) {
        printf("Failed to load script from zip archive.\n");
        lua_close(L);
        return -1;
    }

    // Load and execute the script from memory
    if (loadScriptFromMemory(script, script_size, L) != 0) {
        free(script);
        lua_close(L);
        return -1;
    }

    // Clean up
    free(script);
    lua_close(L);
    return 0;
}

