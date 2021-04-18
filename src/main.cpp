#include "raylib.h"
#include "Player.hpp"
#include "Map.hpp"
int main()
{
    Vector2 screenSize{1024, 720};


    //SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow((int) screenSize.x, (int) screenSize.y, "TinyWings");
    SetTargetFPS(0);


    Player player{{screenSize.x / 2, screenSize.y / 2.5f}, 0.25};
    Camera2D camera{0};
    camera.target = player.GetPosition();
    camera.offset = {screenSize.x / 2.0f - (screenSize.x / 5.f), screenSize.y / 2.0f - (screenSize.y / 5.f)};
    camera.rotation = 0.0f;
    camera.zoom = 1.f;

    Map map{};
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float deltaTime = GetFrameTime();

        // Update
        //----------------------------------------------------------------------------------
        player.Update(deltaTime);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(SKYBLUE);

        {
            DrawText("Score :",10,screenSize.y-50,50,RED);
            BeginMode2D(camera);
            //draw game
            player.Draw();
            map.DrawDebug();
            EndMode2D();
        }

        DrawFPS(10, 20);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}