-- local input = require("scripts/input")

-- InitWindow(850, 800, "CirclePlayground")
-- SetTargetFPS(9999)
-- circlesDrawn = 0
-- circlePositions = {}
-- while not WindowShouldClose() do 
--     BeginDrawing()
--     ClearBackground({h=0,s=0,v=0})

    
--     table.insert(circlePositions, {
--         x = math.random(1, 850),
--         y = math.random(1, 850)
--     })
--     circlesDrawn = circlesDrawn +1
    

--     for i, circle in ipairs(circlePositions) do
--         DrawCircle(circle.x, circle.y,20, 
--         {h = math.random(1, 360), s = math.random(1, 100), v = math.random(1, 100)})
--     end

--     -- DrawCircle(math.random(1, 850), math.random(1, 800), 10, 
--     -- {h = math.random(1, 360),s = math.random(1, 100),v = math.random(1, 100)})
--     circleText = "circles drawn: " ..tostring(circlesDrawn)
--     DrawText(circleText, 10, 10, 40, {h=0, s=0, v=0})
--     DrawFPS(750, 10)
--     EndDrawing()
-- end

-- CloseWindow()

local input = require("scripts/input")

InitWindow(850, 800, "CirclePlayground")
SetTargetFPS(9999)
circlesDrawn = 0
circleBatch = {}

while not WindowShouldClose() do 
    BeginDrawing()
    
    -- if IsMouseButtonPressed(input.mouse.left) then
    --     ClearBackground({ h = 0, s = 0, v = 0 })
    --     print("cleared")
    -- end
    -- Add a new circle to the batch
    table.insert(circleBatch, {
        x = math.random(1, 850),
        y = math.random(1, 850),
        radius = 20,
        color = { h = math.random(1, 360), s = math.random(1, 100), v = math.random(1, 100) }
    })
    circlesDrawn = circlesDrawn + 1

    -- Draw all circles in the batch
    for _, circle in ipairs(circleBatch) do
        DrawCircle(circle.x, circle.y, circle.radius, 
        circle.color)
    end

    circleText = "circles drawn: " .. tostring(circlesDrawn)
    DrawText(circleText, 10, 10, 40, { h = 0, s = 0, v = 0 })
    DrawFPS(750, 10)
    EndDrawing()
end

CloseWindow()
