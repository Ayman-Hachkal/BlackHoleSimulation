#include "raylib.h"
#include "scene.h"

int main(void) {
  const int screenWidth = 1280; 
  const int screenHeight = 720;

  Camera camera = { { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

  Scene blackholeScene = {Scene()};

  InitWindow(screenWidth, screenHeight, "BlackHole Simulation");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    //Update
    if (IsWindowFocused() && IsCursorOnScreen()){
      UpdateCamera(&camera, CAMERA_FREE);
    }
    //
    //Draw
    //---------------------------------------------------
    BeginDrawing();
    
      ClearBackground(BLACK);
      const char* cameraPosition = TextFormat("Camera Position: (%.2f, %.2f, %.2f)", camera.position.x, camera.position.y, camera.position.z);
      DrawText(cameraPosition, 10, 10, 12, WHITE);
      const char* FPS = TextFormat("FPS: %i", GetFPS());
      DrawText(FPS, 10, 30, 12, WHITE);
      blackholeScene.Draw(camera);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
