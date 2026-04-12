#pragma once

#include "grid.h"
#include <iostream>
#include <memory>
#include <raylib.h>
#include <vector>
#include "drawables.h"
#include "blackhole.h"

class Scene { 
  public:
    double worldscale = 1e6;
    std::shared_ptr<Grid> grid;
    std::vector<std::shared_ptr<body>> worldBodies;

    Scene() {
      grid = std::make_shared<Grid>(Grid(worldscale));
      std::cout << "scene grid: " <<  grid << std::endl;
      worldBodies.push_back(std::make_shared<BlackHole>(BlackHole(8.2e36, 0.62, grid)));
    }

    void Draw(const Camera &cam) {
      if (IsKeyDown(KEY_UP)) {
        grid->renderDistanceIncrease();
      }

      if (IsKeyDown(KEY_DOWN)) {
        grid->renderDistanceDecrease();
      }
      BeginMode3D(cam);
      // Draw Grid
      grid->draw(worldBodies, cam);

      // Draw stats
      for (std::shared_ptr<body> b : worldBodies) {
        b->draw();
      }
      EndMode3D();

      DrawText(TextFormat("Render Distance: %i", grid->renderDistance), 10, 50, 12, WHITE);
    }
};
