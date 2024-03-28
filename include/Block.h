#ifndef BLOCK_H
#define BLOCK_H

#include "./GameObject.h"
#include "./LookAt.h"
#include <vector>


// Creates a city block with roads and intersections around it
// and a random number of buildings
class Block : public GameObject {
 public:
  // x,y,z are the coords of the south west corner
  // w is the width of the block
  Block(float x, float y, float z, float w);
  virtual ~Block();

  // Creates all the necessary structures to display a block
  // as well as displays all objects that are part of the block
  virtual void display(const LookAt&);

  // Updates all the objects of the block
  virtual void update();

  float w;                            // The width of the block
  std::vector<GameObject*> objects;   // The roads and buildings on the block
};

#endif
