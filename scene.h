#pragma once

#include "grid.h"
#include <raylib.h>
#include <vector>
#include "drawables.h"
#include "blackhole.h"

class Scene { 
  public:
    std::vector<Drawable*> drawables;
    Grid grid;

    Scene() {
      grid = Grid();
      drawables.push_back(&grid);
      drawables.push_back(new BlackHole(8.2e36, 0.62, grid));
    }

    void Draw() {
      for (Drawable *d : drawables) {
        d->draw();
      }
    }
};
