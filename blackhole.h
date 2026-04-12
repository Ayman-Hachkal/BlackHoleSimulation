#pragma once 

#include "body.h"
#include "grid.h"
#include "vec.h"
#include "raylib.h"
#include <iostream>
#include <memory>

class BlackHole : public body 
{
  public: 
    BlackHole(float mass, double spin, vec position, const std::shared_ptr<Grid> &assignedgrid) : body(mass, spin, 0, position) {
      grid = assignedgrid;
    }
    BlackHole(float mass, double spin, const std::shared_ptr<Grid> &assignedgrid) : body(mass, spin, 0, vec(0, 0, 0)){
      grid = assignedgrid;
    }

    void draw() override {
      DrawSphereEx(toVector3(position), 2, 32, 32, RAYWHITE);
    }

    void move(const vec &new_position) {
      position = position + new_position;
    }

    void replacePosition(const vec& new_position) { 
      position = new_position;
    }
    
  private:
    std::shared_ptr<Grid> grid;
};
