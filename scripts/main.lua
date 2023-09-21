InitWindow(850, 800, "LuaGameKit -- Demo")
SetTargetFPS(9999)
circlesDrawn = 0
while not WindowShouldClose() do 
    BeginDrawing()
    
    DrawCircle(math.random(1, 850), math.random(1, 800), 10, 
    {h = math.random(1, 360),s = math.random(1, 100),v = math.random(1, 100)})
    circlesDrawn = circlesDrawn + 1
    circleText = "circles drawn: " ..tostring(circlesDrawn)
    DrawText(circleText, 10, 10, 40, {h=311, s=57, v=51})
    DrawFPS(750, 10)
    --ClearBackground({h=0,s=0,v=0})
    EndDrawing()
end

CloseWindow()