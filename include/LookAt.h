#ifndef LOOK_AT_H
#define LOOK_AT_H

#include <vector>
#include <string>


// Struct to hold some values for the window
struct Window {
  Window(int width, int height, std::string t) : w(width), h(height), title(t) {}

  int w, h, id;  // Window width, height, and id
  std::string title;
};


// A structure to hold the values for look at position
struct LookAt {
  float ex, ey, ez;  // Eye position
  float cx, cy, cz;  // Center position
  float ux, uy, uz;  // Up vector
};

// A three dimensional point helper
struct P3 {
  float x, y, z;
};

// Offsets for eye position of camera for all positions.
// If position is < 3 they are all the same so use [pos][0]
const std::vector<std::vector<P3>> le{
  {{0,0,0}},
  {{0,0,0}},
  {{0,0,0}},
  {{5,5,10}, {-10,5,5}, {-5,5,-10}, {10,5,-5}},
  {{5,5,-10}, {10,5,5}, {-5,5,10}, {-10,5,-5}},
  {{-5,5,-10}, {10,5,-5}, {5,5,10}, {-10,5,5}},
  {{-5,5,10}, {-10,5,-5}, {5,5,-10}, {10,5,5}},
  {{15,5,20}, {-20,5,15}, {-15,5,-20}, {20,5,-15}},
  {{15,5,-20}, {20,5,15}, {-15,5,20}, {-20,5,-15}},
  {{-15,5,-20}, {20,5,-15}, {15,5,20}, {-20,5,15}},
  {{-15,5,20}, {-20,5,-15}, {15,5,-20}, {20,5,15}},
};

// Offsets for where camera is looking for all positions and directions
// If position is 3+ they are all the same so just use [4][0];
const std::vector<std::vector<P3>> lc{
  {{0,-1,-10}, {10,-1,0}, {0,-1,10}, {-10,-1,0}},
  {{10,-1,0}, {0,-1,10}, {-10,-1,0}, {0,-1,-10}},
  {{-10,-1,0}, {0,-1,-10}, {10,-1,0}, {0,-1,10}},
  {{0,0,0}},
};
#endif
