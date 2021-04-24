#include "raylib.h"
#include "Player.hpp"
#include "Map.hpp"
#include <cstdio>


using namespace Tinywings;

int main()
{
    Vector2 screenSize{1024, 720};


    //SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow((int) screenSize.x, (int) screenSize.y, "TinyWings");
    SetTargetFPS(0);

    RenderTexture2D mapTexture = LoadRenderTexture(screenSize.x, screenSize.y);
    Shader shaderMap = LoadShader(nullptr, TextFormat("../assets/shader/map.fs", GLSL_VERSION));

    int mapLoc = GetShaderLocation(shaderMap, "u_map");
    int steppingLoc = GetShaderLocation(shaderMap, "u_stepping");

    const int stepping = 1;

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
            BeginShaderMode(shaderMap);
            map.CreateBuffer();
//            for (int i = 0; i < 100; ++i) {
//                printf("%f ",map._allPoints[i]);
//            }
            //ClearBackground(BLANK);
            SetShaderValueV(shaderMap,mapLoc,map._allPoints.data(),UNIFORM_FLOAT,100);
            SetShaderValue(shaderMap,steppingLoc,&stepping,UNIFORM_INT);
            DrawTextureRec(mapTexture.texture,
                           (Rectangle) {0, 0, (float) mapTexture.texture.width, (float) -mapTexture.texture.height},
                           (Vector2) {0, 0}, BLANK);
            EndShaderMode();


            BeginMode2D(camera);
            //draw game
            player.Draw();
            EndMode2D();

        }
        // Draw UI
        {
            DrawText("Score :", 10, screenSize.y - 50, 50, RED);
            DrawFPS(10, 20);
        }


        EndDrawing();

        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(shaderMap);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}