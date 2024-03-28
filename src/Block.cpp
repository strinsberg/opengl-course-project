#include "../include/Block.h"
#include "../include/GameObject.h"
#include "../include/LookAt.h"
#include "../include/Road.h"
#include "../include/Building.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cstdlib>
using namespace std;


Block::Block(float x, float y, float z, float w)
    : GameObject(x,y,z), w(w) {
  float road_w = 5;
  float road_l = w - 10;

  // Create all the roads we need
  objects.push_back(new Road(x, y, z-road_w, road_l, road_w, 0));
  objects.push_back(new Road((x+w)-road_w, y, z-road_w, road_l, road_w, 0));
  objects.push_back(new Road(x+road_w, y, (z-w)+road_w, road_l, road_w, 1));
  objects.push_back(new Road(x+road_w, y, z, road_l, road_w, 1));

  // Create all the intersections
  objects.push_back(new Intersection(x, y, z, road_w));
  objects.push_back(new Intersection((x+w)-road_w, y, z, road_w));
  objects.push_back(new Intersection(x, y, (z-w)+road_w, road_w));
  objects.push_back(new Intersection((x+w)-road_w, y, (z-w)+road_w, road_w));

  // Create one building of a random type
  objects.push_back(new Building(x+10, 0, z-10, rand() % 3));

  // Randomly decide to build up to 2 more random buildings
  int build = rand() % 3 + 1;
  if (build > 1)
    objects.push_back(new Building(x+30, 0, z-10, rand() % 3));

  if (build > 2)
    objects.push_back(new Building(x+22, 0, z-30, rand() % 3));
}


Block::~Block() {
  for (auto& obj : objects)
    delete obj;
}


void Block::display(const LookAt& look) {
  glLoadIdentity();
  gluLookAt(look.ex, look.ey, look.ez,
            look.cx, look.cy, look.cz,
            look.ux, look.uy, look.uz);

  // Draw the surface of the block
  glBegin(GL_QUADS);
    glColor4f(0, 0.4, 0, 1);

    glTexCoord2f(1, 0); glVertex3f(x, y-0.01, z);
    glTexCoord2f(1, 1); glVertex3f(x, y-0.01, z-w);
    glTexCoord2f(0, 1); glVertex3f(x+w, y-0.01, z-w);
    glTexCoord2f(0, 0); glVertex3f(x+w, y-0.01, z);
  glEnd();

  // Draw all the roads and buildings
  for (auto& obj : objects)
    obj->display(look);
}


void Block::update() {
  for (auto& obj : objects)
    obj->update();
}
