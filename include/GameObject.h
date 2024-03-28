#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "./LookAt.h"


// Base class for Game objects defining the interface
// with display and update as well as all the common values
class GameObject {
 public:
  // x,y,z are the coordinates of a corner of the object
  // which is defined by the object itself
  GameObject(float x, float y, float z) : x(x), y(y), z(z),
      r(1.0f), g(1.0f), b(1.0f), a(1.0f),
      x_rot(1.0f), y_rot(1.0f), z_rot(1.0f),
      angle(0.0f), speed(0.0f) {}
  virtual ~GameObject() {}

  // Creates all the structures necessary to display the object
  // takes a LookAt object to allow all objects to be drawn in
  // relation to the same camera
  virtual void display(const LookAt&) {}

  // Allows an object to update any parts that need to be adjusted each frame
  virtual void update() {}

  float x, y, z;              // Object coords
  float r, g, b, a;           // Object colors if desired
  float x_rot, y_rot, z_rot;  // Axis the object is rotating on
  float angle, speed;         // Angle to rotate and speed of rotation
};

#endif
