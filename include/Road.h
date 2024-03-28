#ifndef ROAD_H
#define ROAD_H

#include "./GameObject.h"
#include "./LookAt.h"


// Class to represent a straight peice of road
class Road : public GameObject {
 public:
  // x,y,z are the coords of the south west corner
  // w is the width
  // isAve if true the road is rotated to run E to W otherwise runs S to N
  Road(float x, float y, float z, float l, float w, bool isAve);
  virtual ~Road();

  // Creates structures necessary to display the road
  virtual void display(const LookAt&);

  // Does nothing
  virtual void update();

  float l, w;  // The length and width of the road
  bool ave;    // if the road is an avenue or not
};


// A square intersection with white squares in the corners to connect
// with roads. Has no yellow lines.
class Intersection : public GameObject {
 public:
  // x,y,z are the south west corner of the intersection
  // w is the width
  Intersection(float x, float y, float z, float w);
  virtual ~Intersection();

  // Creates all structures to display the intersection
  virtual void display(const LookAt&);

  // Does nothing
  virtual void update();

  float w;  // The width of the intersection
};

#endif
