#ifndef GAME_H
#define GAME_H

#include "./GameObject.h"
#include "./LookAt.h"
#include "./Hummer.h"
#include <vector>


// Class to represent the game. It holds all game objects and keeps
// track of the camera coordinates as well as the hummer.
class Game {
 public:
  Game();
  ~Game();

  // Creates blocks and hummer
  void build();

  // Set up look_at position at the current camera position relative to the
  // hummer. Deals with changes in direction and camera changes.
  void update_view();

  // True if the hummer has strayed too far of the grid
  bool out_of_bounds();

  // True if the hummer is roughly in the center of an intersection
  bool can_turn();

  std::vector<GameObject*> objects;  // All the objects in the game
  LookAt look_at;                    // Values for the glLookAt()
  Hummer* hummer;                    // The hummer
  bool pause;                        // If the game is paused
  int pos;                           // Which of 11 Camera positions we are in

 private:
  // Set the eye position of look_at to x,y,z
  void look_eye(float x, float y, float z);

  // Set the position to look at for look_at to x,y,z
  void look_center(float x, float y, float z);
};

#endif
