#ifndef HUMMER_H
#define HUMMER_H

#include "./GameObject.h"
#include "./LookAt.h"
#include <vector>


// Class to represent the hummer
class Hummer : public GameObject {
 public:
  // x,y,z are the coordinates for the hummers left rear corner
  Hummer(float x, float y, float z);
  virtual ~Hummer();

  // Create all the structures necessary to display the hummer
  virtual void display(const LookAt&);

  // Update all necessary hummer components
  virtual void update();

  // Return the center of the hummer
  P3 center();

  // Move the hummer by the given amount in the direction it is facing
  void move(float amount);

  // Light up some idicators on the hummer
  void light_up(bool on);

  int dir;  // The direction of the hummer 0=N,1=E,2=S,3=W

 private:
  // Set look at and load identity
  void reset(const LookAt&);

  // Translate and move a part of the hummer to it's x,y,z position
  void translate();

  // Draw the main cube body and some accents
  void draw_body(const LookAt&);

  // Draw the rocket launchers
  void draw_launchers(const LookAt&);

  // Draw the cab and doors for the truck
  void draw_cab(const LookAt&);

  // Draw the wheels
  void draw_wheels(const LookAt&);

  // Draw antenna and all it's peices
  void draw_antenna(const LookAt&);

  // Draw all the accessories on the truck
  void draw_extras(const LookAt& look);

  // Draw indicators to light up when it is possible to turn
  void draw_indicators(const LookAt&);

  // Draw a filled in Circle
  void draw_circle(float r, float x, float y, float z);
};

#endif
