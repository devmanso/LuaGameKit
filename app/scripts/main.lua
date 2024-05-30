local input = require("app/scripts/input") -- lua file

InitWindow(850, 800, "CirclePlayground")
SetTargetFPS(9999)
circlesDrawn = 0
circleBatch = {}
flickering = false
hideText = true
SetWindowIcon("app/scripts/random_icon.png")
while not WindowShouldClose() do
    local font = GetFontDefault()
    -- print("Base size: ", font.baseSize)
    -- print("Glyph count: ", font.glyphCount)
    -- print("Texture ID: ", font.texture.id)
    -- print("Texture width: ", font.texture.width)
    -- print("Texture height: ", font.texture.height)
    -- print("Texture mipmaps: ", font.texture.mipmaps)
    -- print("Texture format: ", font.texture.format)
    -- print("Recs stuff ", font.recs.x, font.recs.y, font.recs.width, font.recs.height)

    BeginDrawing()
    if IsMouseButtonPressed(input.mouse.right) then
        flickering = true
    elseif IsMouseButtonPressed(input.mouse.left) then
        flickering = false
    end

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
        if flickering == false then
            DrawCircle(circle.x, circle.y, circle.radius, 
            circle.color)
        elseif flickering == true then
            DrawCircle(circle.x, circle.y, circle.radius, 
            { h = math.random(1, 360), s = math.random(1, 100), v = math.random(1, 100) })
        end
    end
    
    circleText = "circles drawn: " .. tostring(circlesDrawn)
    if IsKeyDown(input.keyboard.s) then
        hideText = false
        if hideText == false then
            DrawText(circleText, 10, 10, 40, { h = 0, s = 0, v = 0 })
            fpsText = GetFPS()
            DrawText(tostring(fpsText), 750, 10, 40, { h = 0, s = 0, v = 0 })
        end
    end
    EndDrawing()
end

CloseWindow()