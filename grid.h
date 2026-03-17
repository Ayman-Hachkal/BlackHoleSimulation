#pragma once

#include "body.h"
#include "constants.h"
#include "vec.h"
#include <iostream>
#include <ostream>
#include <vector>
#include "drawables.h"
#include "raylib.h"


struct point {
  vec pos;
  vec offset;
};

struct row {
  std::vector<point> points;
};

class Grid : public Drawable {
  public: 
  std::vector<row> rows;
  int lowerRange {-100};
  int upperRange { 100}; 

  Grid() {
    for (int x = lowerRange; x <= upperRange; x++) {
      row r;
      for (int z = lowerRange; z <= upperRange; z++) {
        point p;
        p.pos = vec(x, 0, z); 
        p.offset = vec(0, 0, 0);
        r.points.push_back(p);
      }
      rows.push_back(r);
    }
  }

  void calculateOffsets(const body &b) {
    for (row &r : rows) {
      for (point &p : r.points) {
        vec distance = p.pos - b.position;
        double g = (constants::G * b.mass) / (dot(distance, distance));
        p.offset = distance * g;
      }
    }
    std::cout << "Offset caculated " << std::endl;
  }

  void draw() override {
    for (int rowIndex = 0; rowIndex < rows.size() - 1; rowIndex++) {
      row &r = rows[rowIndex];
      row &nextr = rows[rowIndex + 1];
      for (int pointIndex = 0; pointIndex < r.points.size() - 1; pointIndex++) {
        point &p = r.points[pointIndex];
        point &samerowp = r.points[pointIndex + 1];
        point &nextrowp = nextr.points[pointIndex];
        //draw lines 
        DrawLine3D(toVector3(p.pos + p.offset), toVector3(samerowp.pos + samerowp.offset), RED);
        DrawLine3D(toVector3(p.pos + p.offset), toVector3(nextrowp.pos + nextrowp.offset), RED);
        //draw points 
        DrawPoint3D(toVector3(p.pos + p.offset), WHITE);
      }
    }
  }
};
