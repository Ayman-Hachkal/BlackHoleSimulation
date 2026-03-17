#include "raylib.h"
#include "blackhole.h"
#include "scene.h"

int main(void) {
  const int screenWidth = 800; 
  const int screenHeight = 450;

  Scene blackholeScene = {Scene()};
  Camera camera = { { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

  InitWindow(screenWidth, screenHeight, "BlackHole Simulation");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    //Update
    UpdateCamera(&camera, CAMERA_FREE);
    //Draw
    //---------------------------------------------------
    BeginDrawing();
      ClearBackground(BLACK);
      BeginMode3D(camera);
        blackholeScene.Draw();
      EndMode3D();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
