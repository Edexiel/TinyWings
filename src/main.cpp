

#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

#include "Player.hpp"
#include "Map.hpp"



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

    Player player{{screenSize.x / 2.f, screenSize.y / 3.f}, 0.25};

    Camera2D camera{0};
    camera.target = Vector2 {0,0};
    camera.offset = Vector2{0,0};//{screenSize.x / 2.0f - (screenSize.x / 5.f), screenSize.y / 2.0f - (screenSize.y / 5.f)};
    camera.rotation = 0.0f;
    camera.zoom = 1.f;

    Map map{};
    //--------------------------------------------------------------------------------------
    SetupRLImGui(true);
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


            BeginMode2D(camera);

            BeginShaderMode(shaderMap);
            map.CreateBuffer();
            SetShaderValueV(shaderMap,mapLoc,map._allPoints.data(),SHADER_UNIFORM_FLOAT,1000);
            SetShaderValue(shaderMap,steppingLoc,&stepping,SHADER_UNIFORM_INT);

            DrawTextureRec(mapTexture.texture,
                           (Rectangle) {0, 0, (float) mapTexture.texture.width, (float) mapTexture.texture.height},
                           GetScreenToWorld2D(Vector2 {0, (screenSize.y -(screenSize.y/1.f))},camera), BLANK);
            EndShaderMode();

            map.DrawDebug();
            //draw game

            player.Draw();
            DrawCircle(0.f, 0.f,10.f,WHITE);
            DrawCircle(0.f, screenSize.y,10.f,BLUE);
            DrawCircle(screenSize.x, 0.f,10.f,RED);
            EndMode2D();

        }

        // Draw UI
        {
            DrawText("Score :", 10, screenSize.y - 50, 50, RED);
            DrawFPS(10, 20);
        }
        BeginRLImGui();
        EndRLImGui();

        EndDrawing();

        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    ShutdownRLImGui();
    UnloadShader(shaderMap);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}