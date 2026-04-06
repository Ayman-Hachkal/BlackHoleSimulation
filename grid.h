#pragma once

#include "body.h"
#include "constants.h"
#include "vec.h"
#include <algorithm>
#include <iostream>
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

struct row {
  std::vector<point> points;
};

class Grid : public Drawable {
  public: 
  std::vector<row> rows;
  std::vector<body> bodies;
  int lowerRange {-100};
  int upperRange { 100}; 
  double worldscale;
  int renderDistance;
  Camera cam;

  Grid(double worldscale, const Camera &cam) : worldscale(worldscale) {
    this->cam =  cam;
    renderDistance = 100;
    for (int x = lowerRange; x <= upperRange; x++) {
      row r;
      for (int z = lowerRange; z <= upperRange; z++) {
        point p;
        p.pos = vec(x, 0, z); 
        p.worldPos = p.pos * worldscale;
        p.offset = vec(0, 0, 0);
        r.points.push_back(p);
      }
      rows.push_back(r);
    }
  }

  void add_body(body &b) {
  }

  void calculateOffsets(const body &b) {
    for (row &r : rows) {
      for (point &p : r.points) {
        vec distance = p.worldPos - ((b.position) * worldscale);
        double g = (constants::G * b.mass) / (dot(distance, distance));
        p.offset = vec(0, -(distance * g).euclidiannorm()/10, 0);
      }
    }
    std::cout << "Offset caculated " << std::endl;
  }

  void draw() {
    for (int x = 0; x < renderDistance; x++) {
      for (int z = 0; z < renderDistance; z++) {
          // Make Point
          point p;
          p.pos = vec(x, 0, z); 
          p.worldPos = p.pos * worldscale;
          p.offset = vec(0, 0, 0);
    }

    for (int rowIndex = 0; rowIndex < rows.size() - 1; rowIndex++) {
      row &r = rows[rowIndex];
      row &nextr = rows[rowIndex + 1];
      for (int pointIndex = 0; pointIndex < r.points.size() - 1; pointIndex++) {
        point &p = r.points[pointIndex];
        point &samerowp = r.points[pointIndex + 1];
        point &nextrowp = nextr.points[pointIndex];
        Vector3 worldPoint = Vector3({
            static_cast<float>(p.pos.x()), 
            static_cast<float>(p.pos.y() + p.offset.y()), 
            static_cast<float>(p.pos.z())
            });
        Vector3 sameRowWorldPoint = Vector3({
            static_cast<float>(samerowp.pos.x()),
            static_cast<float>(samerowp.pos.y() + samerowp.offset.y()),
            static_cast<float>(samerowp.pos.z())
            }); Vector3 nextRowWorldPoint = Vector3({
            static_cast<float>(nextrowp.pos.x()),
            static_cast<float>(nextrowp.pos.y()+ nextrowp.offset.y()),
            static_cast<float>(nextrowp.pos.z()),
            });
        //draw lines 
        DrawLine3D(worldPoint, sameRowWorldPoint, RED);
        DrawLine3D(worldPoint, nextRowWorldPoint, RED);
        //draw points 
        DrawPoint3D(worldPoint, WHITE);
      }
    }
  }
};


// Don't make grid at start, instead make it when needed, 
// To do that we can genearte on everyloop, based on a ("Render Distance") more efficinet,
// can generate lower quality grid if out of distance
