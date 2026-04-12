#pragma once

#include "body.h"
#include "constants.h"
#include "vec.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>
#include "drawables.h"
#include "raylib.h"

// Position will be a whole number vector
// Offset will be a double vector
// WorldPos will be a double

struct point {
  vec pos;
  vec offset;
  vec worldPos;
};

class Grid : public Drawable {
  public: 
  double worldscale;
  int renderDistance;

  Grid(double worldscale) : worldscale(worldscale) {
    renderDistance = 100;
  }

  void calculateOffsets(point &p, const std::shared_ptr<body> &b) {
      vec distance = p.worldPos - ((b->position) * worldscale);
      double g = (constants::G * b->mass) / (dot(distance, distance));
      p.offset = vec(0, -(distance * g).euclidiannorm()/10, 0);
  }
  void draw(){}

  void draw(const std::vector<std::shared_ptr<body>> &worldBodies, const Camera &cam) {
    for (int x = -renderDistance; x < renderDistance; x++) {
      for (int z = -renderDistance; z < renderDistance; z++) {
        float xPos = x + cam.position.x;
        float zPos = z + cam.position.z;
        point p = point(
            vec(floor(xPos), 0, floor(zPos)),
            vec(0, 0, 0),
            vec(floor(xPos) * worldscale, 0, floor(zPos) * worldscale)
            );
        for (std::shared_ptr<body> b : worldBodies) {
          this->calculateOffsets(p, b);
        }
        Vector3 worldPoint = Vector3({
            static_cast<float>(p.pos.x()), 
            static_cast<float>(p.pos.y() + p.offset.y()), 
            static_cast<float>(p.pos.z())
            });
        //draw points 
        //Gray scale if distance is over 80% of the render distance makes it smoother at end
        Color color;
        if (abs(x) > renderDistance * 0.8 || abs(z) > renderDistance * 0.8) {
          color = ColorFromNormalized(Vector4({float(renderDistance)/abs(x), (float(renderDistance)/abs(x) + float(renderDistance)/abs(z))/2.0f, float(renderDistance)/abs(z), 1.0f}));
        }
        else {
          color = WHITE;
        }
        DrawPoint3D(worldPoint, color);
      }
    }
  }

  void renderDistanceIncrease() {
    renderDistance++;
  }
  void renderDistanceDecrease() {
    renderDistance--;
  }
};


// Don't make grid at start, instead make it when needed, 
// To do that we can genearte on everyloop, based on a ("Render Distance") more efficinet,
// can generate lower quality grid if out of distance
