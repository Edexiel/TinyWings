#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"

#include "Map.hpp"
#include "Player.hpp"
#include <string>
#include <iostream>

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
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(0);

    RenderTexture2D mapTexture = LoadRenderTexture((int)screenSize.x, (int)screenSize.y);
    Shader          shaderMap  = LoadShader(nullptr, TextFormat("../assets/shader/map.fs", GLSL_VERSION));

    int mapLoc        = GetShaderLocation(shaderMap, "u_map");
    int precisionLoc  = GetShaderLocation(shaderMap, "u_precision");
    int resolutionLoc = GetShaderLocation(shaderMap, "u_resolution");
    int offsetLoc     = GetShaderLocation(shaderMap, "u_offset");

    float precision = 10.f;

    Player player{{screenSize.x / 3.5f, screenSize.y / 3.f}, 0.20};

    //    Camera2D camera{0};
    //    camera.target = {0, 0};
    //    camera.offset = Vector2{0, 0};
    //    camera.rotation = 0.0f;
    //    camera.zoom = 1.f;

    Map map{
        player,
        screenSize,
        precision,
    };

    SetupRLImGui(true);

    bool showdebug=false;
    int function_index=0;
    std::string functionName[4]{"Sinusoide","Polynomiale","Elliptique","Hyperbolique"};

    while (!WindowShouldClose())
    {
        screenSize.x = (float)GetScreenWidth();
        screenSize.y = (float)GetScreenHeight();

        float deltaTime = GetFrameTime();

        if(IsWindowResized())
        {
            UnloadRenderTexture(mapTexture);
            mapTexture = LoadRenderTexture((int)screenSize.x,(int)screenSize.y);
        }

        player.Update(deltaTime);
        map.Update(deltaTime);

        BeginDrawing();

        ClearBackground(SKYBLUE);
        {
            // BeginTextureMode(mapTexture2);

            //            BeginMode2D(camera);

            BeginShaderMode(shaderMap);
            map.CreateBuffer();

            SetShaderValueV(shaderMap, mapLoc, map._buffer.data(), SHADER_UNIFORM_FLOAT, NB_POINTS);
            SetShaderValue(shaderMap, precisionLoc, &map._precision, SHADER_UNIFORM_FLOAT);
            SetShaderValue(shaderMap, resolutionLoc, &screenSize, SHADER_UNIFORM_VEC2);
            SetShaderValue(shaderMap, offsetLoc, &map._offset, SHADER_UNIFORM_VEC2);

            DrawTextureRec(mapTexture.texture,
                           Rectangle{0, 0, (float)mapTexture.texture.width, (float)mapTexture.texture.height},
                           Vector2{0, 0}, WHITE);
            EndShaderMode();

            // drawaxis();

            //            EndMode2D();

            // EndTextureMode();
            //            DrawTextureRec(mapTexture2.texture,
            //                           (Rectangle){
            //                                   0,
            //                                   0,
            //                                   (float)mapTexture2.texture.width,
            //                                   (float)mapTexture2.texture.height},
            //                           Vector2 {0,screenSize.y},
            //                           WHITE);
            player._position.y = map.GetIPoint(player._position.x + (player._texture.width/2*player._scale)+ (map._offset.x - map._deletedSpace)) - (player._texture.height*player._scale);

            player.Draw();
        }

        // Draw UI
        {
            if(IsKeyPressed(KEY_F4))
                showdebug= !showdebug;

            if(IsKeyPressed(KEY_RIGHT))
            {
                function_index++;
            }
            if(IsKeyPressed(KEY_LEFT))
            {
                function_index--;
            }
            if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_LEFT))
            {
                function_index= function_index%4;
                if(function_index<0)
                    function_index=3;
                map._currentType = static_cast<F_TYPE>(function_index);
                std::cout<<function_index<<std::endl;

            }


            if(showdebug)
                map.DrawDebug();

            DrawText(FormatText("Score : %2i",(int)map._offset.x), 10, screenSize.y - 65, 50, RAYWHITE);
            DrawText("<          >", screenSize.x-250, screenSize.y - 75, 50, SKYBLUE);
            DrawText(functionName[function_index].c_str(), screenSize.x-200, screenSize.y - 65, 25, RAYWHITE);
            DrawFPS(10, 10);
            DrawText("F4: show debug",10,screenSize.y - 15,10,RAYWHITE);
        }
        // draw imGUI
        if(showdebug)
        {
            BeginRLImGui();
            ImGui::Begin("TinyWings");
            // ImGui::DragFloat("Zoom", &camera.zoom, 0.01f, 0.1f, 1.f);
            // ImGui::DragFloat("Player Position", &player._position);
            ImGui::DragFloat("Speed", &player._speed);
            ImGui::DragFloat("Precision", &precision);
            ImGui::DragFloat2("Offset", &map._offset.x);
            ImGui::DragFloat("Scale", &map._scale,0.1,0.f,10.f);
            ImGui::DragFloat("Player.x", &player._position.x);
            ImGui::DragFloat("Player.y", &player._position.y);
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