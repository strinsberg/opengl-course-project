#include "../include/Game.h"
#include "../include/LookAt.h"

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
#include <cmath>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

// Global variables
Window window(640, 480, "3710 Project - Hummer Assualt: This Time Its Personal!!!");
Game game;


// Updates and draws all the game objects to the screen
void display() {
  // Update game objects if necessary
  if (!game.pause) {
    for (auto& obj : game.objects)
      obj->update();
  } else {

  }
    cout<<"TEST1"<<endl;
  // Update games camera
  game.update_view();

  // If we can turn make some visual changes to hummer
  if (game.can_turn())
    game.hummer->light_up(1);
  else
    game.hummer->light_up(0);

cout<<"TEST2"<<endl;
  // Start Drawing all game objects
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  LookAt& look = game.look_at;
  glLoadIdentity();
  gluLookAt(look.ex, look.ey, look.ez,
            look.cx, look.cy, look.cz,
            look.ux, look.uy, look.uz);

    cout<<"TEST3"<<endl;
  // Draw a surface for outside the grid
  glColor4f(0.4,0.3,0,1);  // Brown like mud
  glBegin(GL_QUADS);
    glTexCoord2f(1, 0); glVertex3f(-100, -0.02, 100);
    glTexCoord2f(1, 1); glVertex3f(-100, -0.02, -1100);
    glTexCoord2f(0, 1); glVertex3f(1100, -0.02, -1100);
    glTexCoord2f(0, 0); glVertex3f(1100, -0.02, 100);
  glEnd();

    cout<<"TEST4"<<endl;
  // Draw the objects in the game
  for (auto& obj : game.objects) {
    if (abs(obj->x - game.look_at.ex) < 150
        and abs(obj->z - game.look_at.ez) < 150)
      obj->display(game.look_at);
    cout<<obj->x<<" "<<obj->y<<endl;
  }

    cout<<"TEST5"<<endl;

  glutSwapBuffers();

  // limit framerate, because my computer has a hard time keeping up
  //this_thread::sleep_for(chrono::milliseconds(20));
}


// Takes care of resizing the screen
void resize(int width, int height) {
   if (height == 0)
      height = 1;

   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);

   glMatrixMode(GL_MODELVIEW);
   window.w = width;
   window.h = height;
}


// Keyboard controls for movement and game functions
void myControlKeyboard(unsigned char key, int x, int y) {
  // When paused or on the boundary only allow relevant keys to be pressed
  if (key != 112 and game.pause)
    return;
  else if (key != 114 and game.out_of_bounds())
    return;

  switch(key) {
    case 97:  // A - Move forward
      game.hummer->move(0.5);
      break;
    case 122:  // Z - Move backward
      game.hummer->move(-0.5);
      break;
    case 113:  // Q - Turn left if possible
      if (game.can_turn()) {
        int dir = game.hummer->dir - 1;
        game.hummer->dir = dir < 0 ? 3 : dir;
      }
      break;
    case 119:  // W - Turn right if possible
      if (game.can_turn()) {
        int dir = game.hummer->dir + 1;
        game.hummer->dir = dir % 4;
      }
      break;
    case 112:  // P - Toggle pause game
      game.pause ^= 1;
      break;
    case 114:  // R - if on boundary reset hummer
      if (game.out_of_bounds()) {
        game.hummer->x = 1.5;
        game.hummer->y = 0;
        game.hummer->z = 0;
        game.hummer->dir = 0;
        game.pos = 0;
      }
      break;
    default:  // Key is not bound to an action
      printf("No Action! %d\n", key);
      break;
  }
}


// Keyboard controls for camera control with function keys
void mySpecialKeyControl(int key, int x, int y) {
  if (game.pause)  // Do nothing if game is paused
    return;

  switch(key) {
    // In hummer views
    case GLUT_KEY_F1:  // Looking forward
      game.pos = 0;
      break;
    case GLUT_KEY_F2:  // Looking right
      game.pos = 1;
      break;
    case GLUT_KEY_F3:  // Looking left
      game.pos = 2;
      break;
    case GLUT_KEY_F4:  // Move camera into hummer looking forward
      game.pos = 0;
      break;

    // Out of hummer views
    case GLUT_KEY_F5:  // Right Rear close
      game.pos = 3;
      break;
    case GLUT_KEY_F6:  // Right Front close
      game.pos = 4;
      break;
    case GLUT_KEY_F7:  // Left Front close
      game.pos = 5;
      break;
    case GLUT_KEY_F8:  // Left Rear close
      game.pos = 6;
      break;

    // More distant views
    case GLUT_KEY_F9:  // Right Rear far
      game.pos = 7;
      break;
    case GLUT_KEY_F10:  // Right Front far
      game.pos = 8;
      break;
    case GLUT_KEY_F11:  // Left Front far
      game.pos = 9;
      break;
    case GLUT_KEY_F12:  // Left Rear far
      game.pos = 10;
      break;

    default:  // No binding for this key
      printf("No action: %d\n", key);
      break;
   }
}


// Initialize some OpenGl states and setup the Game object
void init(int width, int height) {
  glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);

  glShadeModel(GL_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Setup the game objects
  game.build();
  mySpecialKeyControl(GLUT_KEY_F4, 0, 0);  // Set default view


  resize(width,height);
}


// Setup OpenGl and run the main loop
int main(int argc, char** argv) {
   srand(time(0));

   glutInit(&argc, argv);

   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize(window.w, window.h);
   window.id = glutCreateWindow(window.title.c_str());

   glutDisplayFunc(&display);
   glutIdleFunc(&display);
   glutReshapeFunc(&resize);

   glutKeyboardFunc(&myControlKeyboard);
   glutSpecialFunc(&mySpecialKeyControl);

   init(window.w, window.h);
   glutMainLoop();

   return 1;
}
