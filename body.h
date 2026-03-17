#pragma once 

#include "drawables.h"
#include "vec.h"

class body : public Drawable{
  public: 
   long mass; 
   double radius;
   vec position;
   double spin;

   body (long mass, double spin, double radius, vec position) : mass(mass) , spin(spin) , radius(radius) , position(position){}
};
