/********************************************************************************
 *
 * Learn using objects in raylib
 *
 * Obj from open3dmodel
 *
 ********************************************************************************/

#include "raylib.h"


int main(void)
{
    InitWindow(1280, 720, "Model loading");

    // Load model
    Model model = LoadModel("resources/duck.obj");
    // Load texture for the model
    Texture2D tex = LoadTexture("resources/bg.png");
    // Set some texture on the model
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex;

    Camera cam = {0};
    cam.position = (Vector3){10.0f, 10.0f, 10.0f};
    cam.target = (Vector3){0.0f, 0.0f, 0.0f};
    cam.up = (Vector3){0.0f, 1.0f, 0.0f};
    cam.fovy = 90.0f;
    cam.projection = CAMERA_PERSPECTIVE;

    Vector3 pos = {0.0f, 0.0f, 0.0f};
    BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);

    SetTargetFPS(60);


    while(!WindowShouldClose())
    {
        UpdateCamera(&cam, CAMERA_FREE);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(cam);
                DrawModel(model, pos, 1.0f, WHITE);
                DrawGrid(20, 10.0f);
                DrawBoundingBox(bounds, GREEN);
                DrawText("Loading obj file", 10, GetScreenHeight()-25, 25, DARKGRAY);
            EndMode3D();
        EndDrawing();

    }

    UnloadTexture(tex);
    UnloadModel(model);
    CloseWindow();
    return 0;
}
