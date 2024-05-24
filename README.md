# LuaGameKit

- A lua game frameWork that uses Raylib as it's backend
- WIP


## How to build this project using MinGW (Windows only)

- run this command below

```
gcc -o game src/main.c src/miniz.c -Iinclude -Llib -llua54 -lraylib -lopengl32 -lgdi32 -lwinmm
```

- run game.exe

## Can this be compiled on other platforms (MacOS/Linux)

- probably, but I've never tried the command listed in the guid above should work although you may need to include some other flags
- If your on MacOS try this command:

```
gcc -o game src/main.c -Iinclude -Llib -llua -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
```

- If your on Linux try this command:

```
gcc -o game src/main.c -Iinclude -Llib -llua -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

- I don't know if these commands will work on your Linux distro or Mac, if they do, please let me know.
- If you somehow figured out how to compile this on Linux/MacOS a different way please make an issue.

## Liscensed under the MIT Liscense

- see LISCENSE
