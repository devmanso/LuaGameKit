InitWindow(850, 450, "My Window")
SetTargetFPS(60)

while not WindowShouldClose() do 
    BeginDrawing()
    DrawLineV({x=500, y=300},{x=400, y=250}, 100, .5, .7)
    ClearBackground(292, 0.31, 0.86)

    EndDrawing()
end

CloseWindow()