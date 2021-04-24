#include "raylib.h"
#include <EllipticFunction.hpp>
#include <HyperbolicFunction.hpp>
#include <PolyFunction.hpp>
#include <SinusFunction.hpp>
#include <cstdio>

using namespace Tinywings;

void drawFunction(const std::vector<float>& table, float x1, float precision) noexcept
{
    for (float i = 0; i < table.size() - 1; i++)
    {
        DrawLine(x1 + i * precision, table[i], x1 + (i + 1.f) * precision, table[i + 1.f], BLACK);
    }
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth  = 1024;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "TinyWings");

    SetTargetFPS(0);
    //--------------------------------------------------------------------------------------
    float        x1        = 0;
    float        x2        = 300;
    float        y1        = 100;
    float        y2        = 700;
    float        precision = 1;
    unsigned int n         = 3;

    std::vector<float> table = SinusFunction::Create(x1, x2, y1, y2, n, precision);

    x1 = x2;
    x2 = 550;
    y1 = y2;
    y2 = 400;

    std::vector<float> table2 = PolyFunction::Create(x1, x2, y1, y2, precision);

    x1 = x2;
    x2 = 840;
    y1 = y2;
    y2 = 50;

    EllipticFunction ellipticFunc;

    std::vector<float> table3 = ellipticFunc.Create(x1, x2, y1, y2, precision);

    x1 = x2;
    x2 = 1024;
    y1 = y2;
    y2 = 710;

    HyperbolicFunction hyperFunc;

    std::vector<float> table4 = hyperFunc.Create(x1, x2, y1, y2, precision);

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        drawFunction(table, 0, precision);
        drawFunction(table2, 300, precision);
        drawFunction(table3, 550, precision);
        drawFunction(table4, 840, precision);

        // drawFunction(table4, x1, precision);

        DrawFPS(10, 20);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}