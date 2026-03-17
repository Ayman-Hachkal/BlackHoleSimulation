#pragma once 

#include "body.h"
#include "drawables.h"
#include "grid.h"
#include "vec.h"
#include "raylib.h"

class BlackHole : public body 
{
  public: 
    BlackHole(float mass, double spin, vec position, const Grid &assignedgrid) : body(mass, spin, 0, position), grid(assignedgrid){
      grid.calculateOffsets(*this);
    }
    BlackHole(float mass, double spin, const Grid &assignedgrid) : body(mass, spin, 0, vec(0, 0, 0)), grid(assignedgrid){
      grid.calculateOffsets(*this);
    }

    void draw() override {
      DrawSphereEx(toVector3(position), 2, 32, 32, RAYWHITE);
    }
  private:
    Grid grid;
};
