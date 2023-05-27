#include <math.h>
#include "raylib.h"

// Hexagon

void DrawHexagon(Vector2 origin, float sideLength, float thickness, Color color, float rotationAngle) {
    const int numSides = 6;
    const float angleIncrement = 2 * PI / numSides;

    for (int i = 0; i < numSides; i++) {
        float angle = i * angleIncrement + rotationAngle;
        float nextAngle = (i + 1) * angleIncrement + rotationAngle;

        Vector2 startPoint = {
            origin.x + sideLength * cosf(angle),
            origin.y + sideLength * sinf(angle)
        };

        Vector2 endPoint = {
            origin.x + sideLength * cosf(nextAngle),
            origin.y + sideLength * sinf(nextAngle)
        };

        DrawLineEx(startPoint, endPoint, thickness, color);
    }
}

void DrawHexagonFill(Vector2 origin, float sideLength, float thickness, Color outlineColor, Color fillColor, float rotationAngle) {
    const int numSides = 6;
    const float angleIncrement = 2 * PI / numSides;

    Vector2 vertices[numSides];
    for (int i = 0; i < numSides; i++) {
        float angle = i * angleIncrement + rotationAngle;
        vertices[i].x = origin.x + sideLength * cosf(angle);
        vertices[i].y = origin.y + sideLength * sinf(angle);
    }

    DrawPoly(origin, numSides, sideLength, 0, outlineColor);
    DrawPoly(origin, numSides, sideLength - thickness, 0, fillColor);
}

// Pentagon

void DrawPentagon(Vector2 origin, float sideLength, float thickness, Color color, float rotationAngle) {
    const int numSides = 5;
    const float angleIncrement = 2 * PI / numSides;

    for (int i = 0; i < numSides; i++) {
        float angle = i * angleIncrement + rotationAngle;
        float nextAngle = (i + 1) * angleIncrement + rotationAngle;

        Vector2 startPoint = {
            origin.x + sideLength * cosf(angle),
            origin.y + sideLength * sinf(angle)
        };

        Vector2 endPoint = {
            origin.x + sideLength * cosf(nextAngle),
            origin.y + sideLength * sinf(nextAngle)
        };

        DrawLineEx(startPoint, endPoint, thickness, color);
    }
}

void DrawPentagonFill(Vector2 origin, float sideLength, float thickness, Color outlineColor, Color fillColor, float rotationAngle) {
    const int numSides = 5;
    const float angleIncrement = 2 * PI / numSides;

    Vector2 vertices[numSides];
    for (int i = 0; i < numSides; i++) {
        float angle = i * angleIncrement + rotationAngle;
        vertices[i].x = origin.x + sideLength * cosf(angle);
        vertices[i].y = origin.y + sideLength * sinf(angle);
    }

    //DrawPoly(origin, numSides, sideLength, 0, outlineColor);
    DrawPoly(vertices[0], numSides, sideLength - thickness, rotationAngle, fillColor);
}

// Heptagon

void DrawHeptagon(Vector2 origin, float sideLength, float thickness, Color color, float rotationAngle) {
    const int numSides = 7;
    const float angleIncrement = 2 * PI / numSides;

    for (int i = 0; i < numSides; i++) {
        float angle = i * angleIncrement + rotationAngle;
        float nextAngle = (i + 1) * angleIncrement + rotationAngle;

        Vector2 startPoint = {
            origin.x + sideLength * cosf(angle),
            origin.y + sideLength * sinf(angle)
        };

        Vector2 endPoint = {
            origin.x + sideLength * cosf(nextAngle),
            origin.y + sideLength * sinf(nextAngle)
        };

        DrawLineEx(startPoint, endPoint, thickness, color);
    }
}

void DrawHeptagonFill(Vector2 origin, float sideLength, Color color, float rotationAngle) {
    const int numSides = 7;
    const float angleIncrement = 2 * PI / numSides;

    Vector2 vertices[numSides];

    for (int i = 0; i < numSides; i++) {
        float angle = i * angleIncrement + rotationAngle;
        vertices[i].x = origin.x + sideLength * cosf(angle);
        vertices[i].y = origin.y + sideLength * sinf(angle);
    }

    DrawPoly(origin, numSides, sideLength, rotationAngle, color);
}

// Octogon

void DrawOctagon(Vector2 origin, float sideLength, float thickness, Color color, float rotationAngle) {
    const int numSides = 8;
    const float angleIncrement = 2 * PI / numSides;

    for (int i = 0; i < numSides; i++) {
        float angle = i * angleIncrement + rotationAngle;
        float nextAngle = (i + 1) * angleIncrement + rotationAngle;

        Vector2 startPoint = {
            origin.x + sideLength * cosf(angle),
            origin.y + sideLength * sinf(angle)
        };

        Vector2 endPoint = {
            origin.x + sideLength * cosf(nextAngle),
            origin.y + sideLength * sinf(nextAngle)
        };

        DrawLineEx(startPoint, endPoint, thickness, color);
    }
}

void DrawOctagonFill(Vector2 origin, float sideLength, Color color, float rotationAngle) {
    const int numSides = 8;
    const float angleIncrement = 2 * PI / numSides;

    Vector2 vertices[numSides];

    for (int i = 0; i < numSides; i++) {
        float angle = i * angleIncrement + rotationAngle;
        vertices[i].x = origin.x + sideLength * cosf(angle);
        vertices[i].y = origin.y + sideLength * sinf(angle);
    }

    DrawPoly(origin, numSides, sideLength, rotationAngle, color);
}