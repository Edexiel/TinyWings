#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"

#include "Map.hpp"
#include "Player.hpp"

using namespace Tinywings;

void drawaxis()
{
    DrawCircle(0.f, 0.f, 10.f, WHITE);
    DrawCircle(0.f, GetScreenHeight(), 10.f, BLUE);
    DrawCircle(GetScreenWidth(), 0.f, 10.f, RED);
}

int main()
{
    Vector2 screenSize{1280, 720};

    // SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow((int)screenSize.x, (int)screenSize.y, "TinyWings");
    SetTargetFPS(0);

    RenderTexture2D mapTexture = LoadRenderTexture((int)screenSize.x, (int)screenSize.y);
    Shader          shaderMap  = LoadShader(nullptr, TextFormat("../../../assets/shader/map.fs", GLSL_VERSION));

    int mapLoc        = GetShaderLocation(shaderMap, "u_map");
    int precisionLoc  = GetShaderLocation(shaderMap, "u_precision");
    int resolutionLoc = GetShaderLocation(shaderMap, "u_resolution");
    int offsetLoc     = GetShaderLocation(shaderMap, "u_offset");

    float precision = 4.f;

    Player player{{screenSize.x / 2.f, screenSize.y / 3.f}, 0.25};

    Camera2D camera{0};
    camera.target   = {0, 0};
    camera.offset   = Vector2{0, 0};
    camera.rotation = 0.0f;
    camera.zoom     = 1.f;

    Map map{precision, &camera};

    SetupRLImGui(true);

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        float deltaTime = GetFrameTime();

        player.Update(deltaTime);

        BeginDrawing();

        ClearBackground(SKYBLUE);
        {
            // BeginTextureMode(mapTexture2);

            BeginMode2D(camera);

            BeginShaderMode(shaderMap);
            map.CreateBuffer();

            SetShaderValueV(shaderMap, mapLoc, map._allPoints.data(), SHADER_UNIFORM_FLOAT, NB_POINTS);
            SetShaderValue(shaderMap, precisionLoc, &precision, SHADER_UNIFORM_FLOAT);
            SetShaderValue(shaderMap, resolutionLoc, &screenSize, SHADER_UNIFORM_VEC2);
            SetShaderValue(shaderMap, offsetLoc, &map.offset, SHADER_UNIFORM_VEC2);

            DrawTextureRec(mapTexture.texture,
                           Rectangle{0, 0, (float)mapTexture.texture.width, (float)mapTexture.texture.height},
                           Vector2{0, 0}, WHITE);
            EndShaderMode();

            // drawaxis();

            EndMode2D();

            // EndTextureMode();
            //            DrawTextureRec(mapTexture2.texture,
            //                           (Rectangle){
            //                                   0,
            //                                   0,
            //                                   (float)mapTexture2.texture.width,
            //                                   (float)mapTexture2.texture.height},
            //                           Vector2 {0,screenSize.y},
            //                           WHITE);

            player.Draw();
            map.DrawDebug();
            // drawaxis();
        }

        // Draw UI
        {
            DrawText("Score :", 10, screenSize.y - 50, 50, RAYWHITE);
            DrawFPS(10, 10);
        }
        // draw imGUI
        {
            BeginRLImGui();
            ImGui::Begin("TinyWings");
            ImGui::DragFloat("Zoom", &camera.zoom, 0.01f, 0.1f, 1.f);
            // ImGui::DragFloat("Player Position", &player._position);
            ImGui::DragFloat("Player.x", &player._position.x);
            ImGui::DragFloat("Player.y", &player._position.y);
            ImGui::DragFloat("Precision", &precision, 0.1f);
            ImGui::DragFloat2("Offset", &map.offset.x);
            ImGui::End();
            EndRLImGui();
        }
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