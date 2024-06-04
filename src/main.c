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

// check for a engine_config.txt file, if the file reads "true" on the first line
// then call getchar() which opens a terminal for logging and errors
// if anything other than "true" or "false" is written, assume false
// if the file does not exist, create one with "false" written on the first line
void checkEngineConfig() {
    FILE *configFile;
    char firstLine[10];

    // Try to open the file for reading
    configFile = fopen("engine_config.txt", "r");

    if (configFile) {
        // Read the first line of the file
        if (fgets(firstLine, sizeof(firstLine), configFile) != NULL) {
            // Remove newline character if present
            firstLine[strcspn(firstLine, "\n")] = 0;
            fclose(configFile);

            // Check if the first line reads "true"
            if (strcmp(firstLine, "true") == 0) {
                printf("Debug mode is set to true, terminal window will only close on keypress...\n");
                getchar(); // waits for a character input from the user
            } else {
                printf("Goodbye!\n");
            }
        } else {
            fclose(configFile);
            printf("Error reading from engine_config.txt file.\n");
        }
    } else {
        // File does not exist, create it with "false" on the first line
        configFile = fopen("engine_config.txt", "w");
        if (configFile) {
            fprintf(configFile, "false\n");
            fclose(configFile);
        } else {
            printf("Error creating engine_config.txt file.\n");
        }
    }
}


int main() {
    createLuaVM();
    checkEngineConfig();
    return 0;
}
