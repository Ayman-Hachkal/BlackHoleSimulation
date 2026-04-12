#pragma once

#include "body.h"
#include "constants.h"
#include "vec.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <memory>
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
    for (float x = -renderDistance; x < renderDistance; x++) {
      for (float z = -renderDistance; z < renderDistance; z++) {
        float xPos = x + cam.position.x;
        float zPos = z + cam.position.z;
        point p = point(
            vec(floor(xPos), 0, floor(zPos)),
            vec(0, 0, 0),
            vec(floor(xPos) * worldscale, 0, floor(zPos) * worldscale)
            );

        point pNext = point(
            vec(floor(xPos + 1), 0, floor(zPos)),
            vec(0, 0, 0),
            vec(floor(xPos + 1) * worldscale, 0, floor(zPos) * worldscale)
            );

        point pRow = point(
            vec(floor(xPos), 0, floor(zPos + 1)),
            vec(0, 0, 0),
            vec(floor(xPos) * worldscale, 0, floor(zPos + 1) * worldscale)
            );

        for (std::shared_ptr<body> b : worldBodies) {
          this->calculateOffsets(p, b);
          this->calculateOffsets(pNext, b);
          this->calculateOffsets(pRow, b);
        }
        Vector3 worldPoint = Vector3({
            static_cast<float>(p.pos.x()), 
            static_cast<float>(p.pos.y() + p.offset.y()), 
            static_cast<float>(p.pos.z())
            });
        Vector3 worldPointNext = Vector3({
            static_cast<float>(pNext.pos.x()), 
            static_cast<float>(pNext.pos.y() + pNext.offset.y()), 
            static_cast<float>(pNext.pos.z())
            });
        Vector3 worldPointRow = Vector3({
            static_cast<float>(pRow.pos.x()), 
            static_cast<float>(pRow.pos.y() + pRow.offset.y()), 
            static_cast<float>(pRow.pos.z())
            });

        //draw points 
        // fade away
        Color color;
        float max = std::max(abs(x), abs(z));
        double norm = 1.0f - ((max * max)/ (renderDistance * renderDistance));
        color = ColorFromNormalized(Vector4(norm, norm, norm, 1.0f));

        DrawPoint3D(worldPoint, color);
        DrawLine3D(worldPoint, worldPointNext, color);
        DrawLine3D(worldPoint, worldPointRow, color);
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
