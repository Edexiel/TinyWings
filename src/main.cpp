

#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"

#include "Map.hpp"
#include "Player.hpp"

using namespace Tinywings;

int main()
{
    Vector2 screenSize{1024, 720};

    // SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow((int)screenSize.x, (int)screenSize.y, "TinyWings");
    SetTargetFPS(0);

    RenderTexture2D mapTexture = LoadRenderTexture(screenSize.x * 10, screenSize.y * 10);
    Shader          shaderMap  = LoadShader(nullptr, TextFormat("../assets/shader/map.fs", GLSL_VERSION));

    int mapLoc      = GetShaderLocation(shaderMap, "u_map");
    int steppingLoc = GetShaderLocation(shaderMap, "u_precision");

    float precision = 0.90f;

    Player player{{screenSize.x / 2.f, screenSize.y / 3.f}, 0.25};

    Camera2D camera{0};
    camera.target = {0, 0};
    camera.offset =
        Vector2{0, 0}; //{screenSize.x / 2.0f - (screenSize.x / 5.f), screenSize.y / 2.0f - (screenSize.y / 5.f)};
    camera.rotation = 0.0f;
    camera.zoom     = 1.f;

    Map map{precision};
    //--------------------------------------------------------------------------------------
    SetupRLImGui(true);
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
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
            SetShaderValueV(shaderMap, mapLoc, map._allPoints.data(), SHADER_UNIFORM_FLOAT, 1000);
            SetShaderValue(shaderMap, steppingLoc, &precision, SHADER_UNIFORM_INT);

            DrawTextureRec(mapTexture.texture,
                           (Rectangle){
                               0,
                               0,
                               (float)mapTexture.texture.width,
                               (float)mapTexture.texture.height},
                           Vector2 {0,0},
                           BLANK);
            EndShaderMode();

            map.DrawDebug();

            player.Draw();
            DrawCircle(0.f, 0.f, 10.f, WHITE);
            DrawCircle(0.f, screenSize.y, 10.f, BLUE);
            DrawCircle(screenSize.x, 0.f, 10.f, RED);

            EndMode2D();
        }

        // Draw UI
        {
            DrawText("Score :", 10, screenSize.y - 50, 50, RED);
            DrawFPS(10, 20);
        }
        BeginRLImGui();
        ImGui::DragFloat("Zoom", &camera.zoom, 0.01f, 0.1f, 1.f);
        //ImGui::DragFloat("Player Position", &player._position);
        ImGui::DragFloat("Player.x", &player._position.x);
        ImGui::DragFloat("Player.y", &player._position.y);
        EndRLImGui();

        EndDrawing();

        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    ShutdownRLImGui();
    UnloadShader(shaderMap);
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}