#include "raylib.h"
#include <cstdio>
#include <SinusFunction.hpp>

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
    const int screenWidth   = 1920;
    const int screenHeight  = 1080;

    InitWindow(screenWidth, screenHeight, "TinyWings");

    SetTargetFPS(0);
    //--------------------------------------------------------------------------------------
    float x1 = 0;
    float x2 = screenWidth;
    float y1 = 0;
    float y2 = screenHeight;
    float precision = 1;
    unsigned int n = 9;
    std::vector<float> table = Tinywings::SinusFunction::Create(x1, x2,y1,y2,n,precision);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        //for (size_t i = 0; i + x1 < x2; i++)
        //{
        //    DrawLine(x1+i,table[i],x1+i+1, table[i + 1], BLACK);
        //}
        drawFunction(table,x1,precision);

        //DrawLine(0, 0, 1000, 1000, BLACK);
        //char* fps;
        //sprintf(fps,"FPS : %i",GetFPS());
        //DrawText(fps, 10, 10, 20,LIGHTGRAY);
        DrawFPS(10,20);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}