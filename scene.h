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
    std::vector<std::shared_ptr<Drawable>>drawables;
    double worldscale = 1e6;
    std::shared_ptr<Grid>grid;

    Scene(const Camera &cam) {
      grid = std::make_shared<Grid>(Grid(worldscale, cam));
      drawables.push_back(grid);
      std::cout << "scene grid: " <<  grid << std::endl;
      drawables.push_back(std::make_shared<BlackHole>(BlackHole(8.2e36, 0.62, grid)));
    }

    void Draw() {
      for (std::shared_ptr<Drawable> d : drawables) {
        d->draw();
      }
    }
};
