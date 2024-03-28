#include "../include/Building.h"
#include "../include/LookAt.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cmath>
#include <iostream>
using namespace std;


Building::Building(float x, float y, float z, int t)
    : GameObject(x, y, z), type(t) {

  // rotation values based on type
  speed = type == 2 ? 1.5 : -2.3;
  y_rot = 1;
  x_rot = 0;
  z_rot = 0;
}


Building::~Building() {}


void Building::display(const LookAt& look) {
  glLoadIdentity();
  gluLookAt(look.ex, look.ey, look.ez,
            look.cx, look.cy, look.cz,
            look.ux, look.uy, look.uz);

  // Decide what building we are drawing based on type
  if (type == 1)
    display_office();
  else if (type == 2)
    display_tower();
  else
    display_sphere();
}


void Building::update() {
  // Update the rotation angle for the moving parts
  angle += speed;
}


void Building::display_office() {
  float height = 20;
  float width = 5;

  // Build a rectangular office building
  glBegin(GL_QUADS);

    // Front Face
    glColor4f(0.6, 0.6, 0.6, 1);

    glTexCoord2f(1, 0); glVertex3f(x, y, z);
    glTexCoord2f(1, 1); glVertex3f(x, y+height, z);
    glTexCoord2f(0, 1); glVertex3f(x+width, y+height, z);
    glTexCoord2f(0, 0); glVertex3f(x+width, y, z);

    // Back Face
    glTexCoord2f(1, 0); glVertex3f(x, y, z-width);
    glTexCoord2f(1, 1); glVertex3f(x, y+height, z-width);
    glTexCoord2f(0, 1); glVertex3f(x+width, y+height, z-width);
    glTexCoord2f(0, 0); glVertex3f(x+width, y, z-width);

    // Left Face
    glColor4f(0.7, 0.7, 0.7, 1);

    glTexCoord2f(1, 0); glVertex3f(x, y, z);
    glTexCoord2f(1, 1); glVertex3f(x, y+height, z);
    glTexCoord2f(0, 1); glVertex3f(x, y+height, z-width);
    glTexCoord2f(0, 0); glVertex3f(x, y, z-width);

    // Right Face
    glColor4f(0.5, 0.5, 0.5, 1);

    glTexCoord2f(1, 0); glVertex3f(x+width, y, z);
    glTexCoord2f(1, 1); glVertex3f(x+width, y+height, z);
    glTexCoord2f(0, 1); glVertex3f(x+width, y+height, z-width);
    glTexCoord2f(0, 0); glVertex3f(x+width, y, z-width);

    // Top face
    glColor4f(0.65, 0.65, 0.65, 1);

    glTexCoord2f(1, 0); glVertex3f(x, y+height, z);
    glTexCoord2f(1, 1); glVertex3f(x, y+height, z-width);
    glTexCoord2f(0, 1); glVertex3f(x+width, y+height, z-width);
    glTexCoord2f(0, 0); glVertex3f(x+width, y+height, z);

    // Add some windows to each side of the building
    float win_off = 1;
    float win_w = 3;
    float win_h = 2.5;
    glColor4f(0,0,0.3, 1);

    // Front windows
    for (int i = 0; i + win_h + win_off < height; i+=win_h+win_off) {
      glTexCoord2f(1, 0); glVertex3f(x+win_off, y+win_off+i, z+0.03);
      glTexCoord2f(1, 1); glVertex3f(x+win_off, y+win_off+win_h+i, z+0.03);
      glTexCoord2f(0, 1); glVertex3f(x+win_off+win_w, y+win_off+win_h+i, z+0.03);
      glTexCoord2f(0, 0); glVertex3f(x+win_off+win_w, y+win_off+i, z+0.03);
    }

    // Back windows
    for (int i = 0; i + win_h + win_off < height; i+=win_h+win_off) {
      glTexCoord2f(1, 0); glVertex3f(x+win_off, y+win_off+i, z-width-0.03);
      glTexCoord2f(1, 1); glVertex3f(x+win_off, y+win_off+win_h+i, z-width-0.03);
      glTexCoord2f(0, 1); glVertex3f(x+win_off+win_w, y+win_off+win_h+i, z-width-0.03);
      glTexCoord2f(0, 0); glVertex3f(x+win_off+win_w, y+win_off+i, z-width-0.03);
    }

    // Right windows
    for (int i = 0; i + win_h + win_off < height; i+=win_h+win_off) {
      glTexCoord2f(1, 0); glVertex3f(x-0.03, y+win_off+i, z-win_off);
      glTexCoord2f(1, 1); glVertex3f(x-0.03, y+win_off+win_h+i, z-win_off);
      glTexCoord2f(0, 1); glVertex3f(x-0.03, y+win_off+win_h+i, z-win_off-win_w);
      glTexCoord2f(0, 0); glVertex3f(x-0.03, y+win_off+i, z-win_off-win_w);
    }

    // Left windows
    for (int i = 0; i + win_h + win_off < height; i+=win_h+win_off) {
      glTexCoord2f(1, 0); glVertex3f(x+width+0.03, y+win_off+i, z-win_off);
      glTexCoord2f(1, 1); glVertex3f(x+width+0.03, y+win_off+win_h+i, z-win_off);
      glTexCoord2f(0, 1); glVertex3f(x+width+0.03, y+win_off+win_h+i, z-win_off-win_w);
      glTexCoord2f(0, 0); glVertex3f(x+width+0.03, y+win_off+i, z-win_off-win_w);
    }
  glEnd();
}


void Building::display_tower() {
  // Build a cylinder by stacking circles
  float r = 1;
  float segments = 15;
  float height = 25;

  for (float i = 0; i < height; i+=0.01) {
    // Switch between slightly different colors to make it striped
    if ((int)i % 2 < 1)
      glColor4f(1,0.5,0,1);
    else
      glColor4f(0.8,0.3,0,1);

    // Draw the circle
    glBegin(GL_LINE_LOOP);
    for(float j = 0; j < segments; j++)
    {
        float theta = 2.0 * M_PI * j / segments;
        float dx = r * cosf(theta);
        float dz = r * sinf(theta);

        glVertex3f(x+dx, y+i, z+dz);
    }
    glEnd();
  }


  // Create a wire cube for the rotating part
  float width = 5;
  glTranslatef(x,y+height-2.5,z);
  glRotatef(angle, x_rot, y_rot, z_rot);
  glColor4f(1,1,1,1);
  glutWireCube(width);

  // Create some faces for the rotating cube
  glBegin(GL_QUADS);
    // Top
    glTexCoord2f(1, 0); glVertex3f(-width/1.97, width/1.97, width/1.97);
    glTexCoord2f(1, 1); glVertex3f(-width/1.97, width/1.97,-width/1.97);
    glTexCoord2f(0, 1); glVertex3f(width/1.97, width/1.97, -width/1.97);
    glTexCoord2f(0, 0); glVertex3f(width/1.97, width/1.97, width/1.97);

    // Bottom
    glTexCoord2f(1, 0); glVertex3f(-width/1.97, -width/1.97, width/1.97);
    glTexCoord2f(1, 1); glVertex3f(-width/1.97, -width/1.97,-width/1.97);
    glTexCoord2f(0, 1); glVertex3f(width/1.97, -width/1.97, -width/1.97);
    glTexCoord2f(0, 0); glVertex3f(width/1.97, -width/1.97, width/1.97);
  glEnd();
}


void Building::display_sphere() {
  float height = 10;

  // Add a few stripes to the sphere to make it look more 3d
  glColor4f(1,1,1,1);
  for (float i = -0.5; i < 0.5; i+=0.2) {
    glBegin(GL_LINE_LOOP);
      for(float j = 0; j < 30; j++) {
        float theta = 2.0 * M_PI * j / 30;
        float dx = 5.1 * cosf(theta);
        float dz = 5.1 * sinf(theta);

        glVertex3f(x+dx, y+(height/2)+i, z+dz);
      }
    glEnd();
  }

  // Create the sphere and move the objects into final position
  glTranslatef(x,y+(height/2),z);
  glColor4f(0.5, 0, 0.5, 1);
  glutSolidSphere(height/2, 20, 20);


  // Rotate the antenna and move it to a nice point toucging the circle
  glTranslatef(0,height-3.3,0);
  glRotatef(angle, x_rot, y_rot, z_rot);

  // Move the cone into a position that is good for rotating
  glTranslatef(1,0,0);
  glRotatef(90, 0, 1, 0);
  glRotatef(120, 1, 0, 0);

  // Create cone for antenna
  glColor4f(0.9, 0, 0.2, 1);
  glutWireCone(3, 2, 40, 20);
}

