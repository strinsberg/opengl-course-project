#include "../include/Game.h"
#include "../include/LookAt.h"
#include "../include/Building.h"
#include "../include/Road.h"
#include "../include/Block.h"
#include "../include/Hummer.h"
#include <cmath>
using namespace std;


Game::Game() : pause(false), pos(0) {
  // Initialize look at to a default value
  look_eye(0,0,0);
  look_center(0,0,-1);
  look_at.ux = 0.0f;
  look_at.uy = 1.0f;
  look_at.uz = 0.0f;
}


Game::~Game() {
  for (auto& obj : objects)
    delete obj;
}


void Game::build() {
  float width = 50;  // Width for the blocks

  // Create a 20 by 20 grid of Blocks
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      objects.push_back(new Block(i*(width-5), 0, -j*(width-5), width));
    }
  }

  // Create the hummer at the origin
  hummer = new Hummer(1.5, 0, 0);
  objects.push_back(hummer);
}


void Game::update_view() {
  P3 hc = hummer->center();
  int dir = hummer-> dir;

  // Find the offsets for the camera based on position and direction
  P3 cc = pos < 3 ? lc[pos][dir] : lc[3][0];
  P3 ee = pos < 3 ? le[pos][0] : le[pos][dir];

  // Set the eye and center position using the hummer center and the offsets
  look_center(hc.x + cc.x, hc.y + cc.y, hc.z + cc.z);
  look_eye(hc.x + ee.x, hc.y + ee.y, hc.z + ee.z);
}


bool Game::out_of_bounds() {
  return hummer->x > (20 * 45) + 5 or hummer->x < -5
      or hummer->z < -20 * 45 or hummer->z > 5;
}


bool Game::can_turn() {
  // Use a different axis depending on what direction we are facing
  if (hummer->dir % 2 == 0) {
    if ((int)abs(hummer->z - 4.2) % 45 == 1)
      return true;
  } else {
    if ((int)abs(hummer->x) % 45 == 1)
      return true;
  }
  return false;
}


void Game::look_center(float x, float y, float z) {
  look_at.cx = x;
  look_at.cy = y;
  look_at.cz = z;
}


void Game::look_eye(float x, float y, float z) {
  look_at.ex = x;
  look_at.ey = y;
  look_at.ez = z;
}
