#ifndef BUILDING_H
#define BUILDING_H

#include "./GameObject.h"
#include "./LookAt.h"


// Class for three different building types
class Building : public GameObject {
 public:
  // x,y,z are the south west bottom corner of the building if
  // it was square.
  // type is the type of building to draw 1,2,3
  Building(float x, float y, float z, int type);
  virtual ~Building();

  // Creates all the structures to display the building
  virtual void display(const LookAt&);

  // Updates any moving parts a building may have
  virtual void update();

  int type;  // The type of building 1=office, 2=tower, 3=sphere

 private:
  // Creates the office structures
  void display_office();

  // Creates the tower structures
  void display_tower();

  // Creates the sphere structures
  void display_sphere();
};

#endif
