#include "../include/Hummer.h"
#include "../include/GameObject.h"
#include "../include/LookAt.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cmath>
#include <vector>
using namespace std;


Hummer::Hummer(float x, float y, float z) : GameObject(x,y,z), dir(0) {
  speed = -3;
  angle = 0;

  r = 1;
}


Hummer::~Hummer() {}


void Hummer::display(const LookAt& look) {

  draw_indicators(look);
  draw_extras(look);
  draw_launchers(look);

  draw_wheels(look);
  draw_antenna(look);

  draw_cab(look);
  draw_body(look);
}


void Hummer::update() {
  angle+=speed;  // Update antenna rotation
}


P3 Hummer::center() {
  return {x+1.5f, y+1.8f, z-5};
}

void Hummer::move(float amount) {
  float dx = 0;
  float dz = 0;

  if (dir == 0)
    dz-=amount;
  else if (dir == 1)
    dx+=amount;
  else if (dir == 2)
    dz+=amount;
  else
    dx-=amount;

  x += dx;
  z += dz;
}


void Hummer::light_up(bool on) {
  // Changes r value so that indicator objects will appear brighter
  if (on)
    r = 0.9;
  else
    r = 0.5;
}


void Hummer::reset(const LookAt& look) {
  glLoadIdentity();
  gluLookAt(look.ex, look.ey, look.ez,
            look.cx, look.cy, look.cz,
            look.ux, look.uy, look.uz);
}

void Hummer::translate() {
  glTranslatef(x+1.5, y-0.2 , z-5);
  glRotatef(-90 * dir, 0, 1, 0);
}

void Hummer::draw_body(const LookAt& look) {
  reset(look);
  translate();

  glTranslatef(0,1,2);  // Move center of cab to origin
  glScalef(1,0.5,3);
  glColor4f(0.1,0.1,0.1,1);
  glutWireCube(2.001);
  glColor4f(0.6, 0.6, 0.6, 1);
  glutSolidCube(2);
}

void Hummer::draw_cab(const LookAt& look) {
  reset(look);
  translate();

  // Create the cab with windows build as if center of cab is at origin
  glBegin(GL_QUADS);
    // Cab Roof
    glColor4f(0.6, 0.6, 0.6, 1);
    glTexCoord2f(1, 0); glVertex3f(-1, 2.5, 1);
    glTexCoord2f(1, 1); glVertex3f(-1, 2.5, -1);
    glTexCoord2f(0, 1); glVertex3f(1, 2.5, -1);
    glTexCoord2f(0, 0); glVertex3f(1, 2.5, 1);

    // Left side posts
    glColor4f(0.5,0.5,0.5,1);
    glTexCoord2f(1, 0); glVertex3f(-1, 1.5, 1);
    glTexCoord2f(1, 1); glVertex3f(-1, 2.5, 1);
    glTexCoord2f(0, 1); glVertex3f(-1, 2.5, 0.8);
    glTexCoord2f(0, 0); glVertex3f(-1, 1.5, 0.8);

    glTexCoord2f(1, 0); glVertex3f(-1, 1.5, -1);
    glTexCoord2f(1, 1); glVertex3f(-1, 2.5, -1);
    glTexCoord2f(0, 1); glVertex3f(-1, 2.5, -0.8);
    glTexCoord2f(0, 0); glVertex3f(-1, 1.5, -0.8);

    // left upper and lower boarders
    glTexCoord2f(1, 0); glVertex3f(-1.01, 0.5, -1);
    glTexCoord2f(1, 1); glVertex3f(-1.01, 1.7, -1);
    glTexCoord2f(0, 1); glVertex3f(-1.01, 1.7, 1);
    glTexCoord2f(0, 0); glVertex3f(-1.01, 0.5, 1);

    glTexCoord2f(1, 0); glVertex3f(-1, 2.3, -1);
    glTexCoord2f(1, 1); glVertex3f(-1, 2.5, -1);
    glTexCoord2f(0, 1); glVertex3f(-1, 2.5, 1);
    glTexCoord2f(0, 0); glVertex3f(-1, 2.3, 1);

    // right side posts
    glColor4f(0.5,0.5,0.5,1);
    glTexCoord2f(1, 0); glVertex3f(1, 1.5, 1);
    glTexCoord2f(1, 1); glVertex3f(1, 2.5, 1);
    glTexCoord2f(0, 1); glVertex3f(1, 2.5, 0.8);
    glTexCoord2f(0, 0); glVertex3f(1, 1.5, 0.8);

    glTexCoord2f(1, 0); glVertex3f(1, 1.5, -1);
    glTexCoord2f(1, 1); glVertex3f(1, 2.5, -1);
    glTexCoord2f(0, 1); glVertex3f(1, 2.5, -0.8);
    glTexCoord2f(0, 0); glVertex3f(1, 1.5, -0.8);

    // right upper and lower boarders
    glTexCoord2f(1, 0); glVertex3f(1.01, 0.5, -1);
    glTexCoord2f(1, 1); glVertex3f(1.01, 1.7, -1);
    glTexCoord2f(0, 1); glVertex3f(1.01, 1.7, 1);
    glTexCoord2f(0, 0); glVertex3f(1.01, 0.5, 1);

    glTexCoord2f(1, 0); glVertex3f(1, 2.3, -1);
    glTexCoord2f(1, 1); glVertex3f(1, 2.5, -1);
    glTexCoord2f(0, 1); glVertex3f(1, 2.5, 1);
    glTexCoord2f(0, 0); glVertex3f(1, 2.3, 1);

    // Back side posts
    glColor4f(0.4,0.4,0.4,1);
    glTexCoord2f(1, 0); glVertex3f(-1, 1.5, 1);
    glTexCoord2f(1, 1); glVertex3f(-1, 2.5, 1);
    glTexCoord2f(0, 1); glVertex3f(-0.8, 2.5, 1);
    glTexCoord2f(0, 0); glVertex3f(-0.8, 1.5, 1);

    glTexCoord2f(1, 0); glVertex3f(1, 1.5, 1);
    glTexCoord2f(1, 1); glVertex3f(1, 2.5, 1);
    glTexCoord2f(0, 1); glVertex3f(0.8, 2.5, 1);
    glTexCoord2f(0, 0); glVertex3f(0.8, 1.5, 1);

    // Back upper and lower boarders
    glTexCoord2f(1, 0); glVertex3f(-1, 1.5, 1);
    glTexCoord2f(1, 1); glVertex3f(-1, 1.7, 1);
    glTexCoord2f(0, 1); glVertex3f(1, 1.7, 1);
    glTexCoord2f(0, 0); glVertex3f(1, 1.5, 1);

    glTexCoord2f(1, 0); glVertex3f(1, 2.3, 1);
    glTexCoord2f(1, 1); glVertex3f(1, 2.5, 1);
    glTexCoord2f(0, 1); glVertex3f(-1, 2.5, 1);
    glTexCoord2f(0, 0); glVertex3f(-1, 2.3, 1);

    // Front upper and lower boarders
    glColor4f(0.4,0.4,0.4,1);
    glTexCoord2f(1, 0); glVertex3f(-1, 1.5, -1);
    glTexCoord2f(1, 1); glVertex3f(-1, 1.7, -1);
    glTexCoord2f(0, 1); glVertex3f(1, 1.7, -1);
    glTexCoord2f(0, 0); glVertex3f(1, 1.5, -1);

    glTexCoord2f(1, 0); glVertex3f(1, 2.3, -1);
    glTexCoord2f(1, 1); glVertex3f(1, 2.5, -1);
    glTexCoord2f(0, 1); glVertex3f(-1, 2.5, -1);
    glTexCoord2f(0, 0); glVertex3f(-1, 2.3, -1);
  glEnd();

  // Put some wire boxes around the cab and doors to make them stand out better
  reset(look);
  translate();
  glTranslatef(0,2.001,0);
  glScalef(2.03,1,2);
  glColor4f(0,0,0,1);
  glutWireCube(1);

  reset(look);
  translate();
  glTranslatef(0,1,0);
  glScalef(2.03,1,2);
  glColor4f(0,0,0,1);
  glutWireCube(1);
}


void Hummer::draw_antenna(const LookAt& look) {
  reset(look);
  translate();

  // Draw the pole
  GLUquadric* quad = gluNewQuadric();
  glTranslatef(0,1.5,4);
  glRotatef(-90, 1,0,0);
  glColor4f(0,0,0,1);
  gluCylinder(quad, 0.05, 0.05, 2, 30, 30);
  //free (quad);
  gluDeleteQuadric(quad);

  // Draw the antenna
  reset(look);
  translate();

  glTranslatef(0, 4, 4);
  glRotatef(angle, 0,1,0);
  glRotatef(22.5, 0,0,1);
  glScalef(0.5,0.5,0.5);
  glutWireIcosahedron();
  glColor4f(r,0,0,1);
  glutSolidIcosahedron();

}


void Hummer::draw_wheels(const LookAt& look) {
  // Right Front Wheel
  reset(look);
  translate();

  GLUquadric* quad = gluNewQuadric();
  glTranslatef(0.9,0.5,-0.4);
  glRotatef(90, 0,1,0);
  glColor4f(0,0,0,1);
  gluCylinder(quad, 0.3, 0.3, 0.2, 30, 30);
  //free (quad);
  gluDeleteQuadric(quad);

  glColor4f(1,1,1,1);
  draw_circle(0.3, 0,0,0.19);
  glColor4f(0,0,0,1);
  draw_circle(0.1, 0,0,0.2);

  // Right Back Wheel
  reset(look);
  translate();

  quad = gluNewQuadric();
  glTranslatef(0.9,0.5,4);
  glRotatef(90, 0,1,0);
  glColor4f(0,0,0,1);
  gluCylinder(quad, 0.3, 0.3, 0.2, 30, 30);
  //free (quad);
  gluDeleteQuadric(quad);

  glColor4f(1,1,1,1);
  draw_circle(0.3, 0,0,0.19);
  glColor4f(0,0,0,1);
  draw_circle(0.1, 0,0,0.195);

  // Left Front Wheel
  reset(look);
  translate();

  quad = gluNewQuadric();
  glTranslatef(-1.1,0.5,-0.4);
  glRotatef(90, 0,1,0);
  glColor4f(0,0,0,1);
  gluCylinder(quad, 0.3, 0.3, 0.2, 30, 30);
  gluDeleteQuadric(quad);

  glColor4f(1,1,1,1);
  draw_circle(0.3, 0,0,0.03);
  glColor4f(0,0,0,1);
  draw_circle(0.1, 0,0,0.01);

  // Right Back Wheel
  reset(look);
  translate();

  quad = gluNewQuadric();
  glTranslatef(-1.1,0.5,4);
  glRotatef(90, 0,1,0);
  glColor4f(0,0,0,1);
  gluCylinder(quad, 0.3, 0.3, 0.2, 30, 30);
  gluDeleteQuadric(quad);

  glColor4f(1,1,1,1);
  draw_circle(0.3, 0,0,0.03);
  glColor4f(0,0,0,1);
  draw_circle(0.1, 0,0,0.01);
}


void Hummer::draw_extras(const LookAt& look) {
  reset(look);
  translate();

  // Draw headlight borders
  glColor4f(0,0,0,1);
  draw_circle(0.2, 0.7, 1.2, -1.02);
  draw_circle(0.2, -0.7, 1.2, -1.02);
  draw_circle(0.2, 0.7, 1.2, 5.02);
  draw_circle(0.2, -0.7, 1.2, 5.02);

  // Draw headlight centers
  glColor4f(1,1,0,1);
  draw_circle(0.15, 0.7, 1.2, -1.03);
  draw_circle(0.15, -0.7, 1.2, -1.03);

  glColor4f(1,0,0,1);
  draw_circle(0.15, 0.7, 1.2, 5.03);
  draw_circle(0.15, -0.7, 1.2, 5.03);

  // Draw grill
  glBegin(GL_QUADS);
    glColor4f(0,0,0,1);
    glTexCoord2f(1, 0); glVertex3f(-0.9, 0.5, -1.01);
    glTexCoord2f(1, 1); glVertex3f(-0.9, 0.8, -1.01);
    glTexCoord2f(0, 1); glVertex3f(0.9, 0.8, -1.01);
    glTexCoord2f(0, 0); glVertex3f(0.9, 0.5, -1.01);

    glColor4f(1,1,1,1);
    for (float i = -0.8; i < 0.7; i+=0.21) {
      glTexCoord2f(1, 0); glVertex3f(i, 0.53, -1.02);
      glTexCoord2f(1, 1); glVertex3f(i, 0.77, -1.02);
      glTexCoord2f(0, 1); glVertex3f(i+0.1, 0.77, -1.02);
      glTexCoord2f(0, 0); glVertex3f(i+0.1, 0.53, -1.02);
    }
  glEnd();

  // Draw license plate
  glBegin(GL_QUADS);
    glColor4f(0,0,0,1);
    glTexCoord2f(1, 0); glVertex3f(-0.9, 0.5, 5.01);
    glTexCoord2f(1, 1); glVertex3f(-0.9, 0.8, 5.01);
    glTexCoord2f(0, 1); glVertex3f(0.9, 0.8, 5.01);
    glTexCoord2f(0, 0); glVertex3f(0.9, 0.5, 5.01);

    glColor4f(1,1,1,1);
    glTexCoord2f(1, 0); glVertex3f(-0.85, 0.53, 5.02);
    glTexCoord2f(1, 1); glVertex3f(-0.85, 0.77, 5.02);
    glTexCoord2f(0, 1); glVertex3f(0.85, 0.77, 5.02);
    glTexCoord2f(0, 0); glVertex3f(0.85, 0.53, 5.02);
  glEnd();

  // Wanted to put something on the license plate but I do not know how to
  // get this to work in 3d without other libraries.
}


void Hummer::draw_launchers(const LookAt& look) {
  // Right Rocket Launcher body
  reset(look);
  translate();

  GLUquadric* quad = gluNewQuadric();
  glTranslatef(1.25,1,1.2);
  glColor4f(0.6,0,0,1);
  gluCylinder(quad, 0.2, 0.2, 1, 30, 30);
  gluDeleteQuadric(quad);

  // Right front tip
  reset(look);
  translate();

  quad = gluNewQuadric();
  glTranslatef(1.25,1,1.2);
  glColor4f(0,0,0,1);
  gluCylinder(quad, 0.22, 0.22, 0.2, 30, 30);
  gluDeleteQuadric(quad);

  // Right rear tip
  reset(look);
  translate();

  quad = gluNewQuadric();
  glTranslatef(1.25,1,2.2);
  glColor4f(0,0,0,1);
  gluCylinder(quad, 0.22, 0.22, 0.2, 30, 30);
  gluDeleteQuadric(quad);

  draw_circle(0.22, 0,0,0.2);

  // Left Rocket Launcher
  reset(look);
  translate();

  quad = gluNewQuadric();
  glTranslatef(-1.25,1,1.2);
  glColor4f(0.6,0,0,1);
  gluCylinder(quad, 0.2, 0.2, 1, 30, 30);
  gluDeleteQuadric(quad);

  // Left front tip
  reset(look);
  translate();

  quad = gluNewQuadric();
  glTranslatef(-1.25,1,1.2);
  glColor4f(0,0,0,1);
  gluCylinder(quad, 0.22, 0.22, 0.2, 30, 30);
  gluDeleteQuadric(quad);

  // Left rear tip
  reset(look);
  translate();

  quad = gluNewQuadric();
  glTranslatef(-1.25,1,2.2);
  glColor4f(0,0,0,1);
  gluCylinder(quad, 0.22, 0.22, 0.2, 30, 30);
  gluDeleteQuadric(quad);

  draw_circle(0.22, 0,0,0.2);
}


void Hummer::draw_indicators(const LookAt& look) {
  // Draw some lights in the cab to tell you it is possible to turn
  reset(look);
  translate();


  glBegin(GL_QUADS);
    // Front in cab
    glColor4f(r,0,0,1);
    glTexCoord2f(1, 0); glVertex3f(-0.1, 1.55, -0.98);
    glTexCoord2f(1, 1); glVertex3f(-0.1, 1.65, -0.98);
    glTexCoord2f(0, 1); glVertex3f(0.1, 1.65, -0.98);
    glTexCoord2f(0, 0); glVertex3f(0.1, 1.55, -0.98);

    glColor4f(0,0,0,1);
    glTexCoord2f(1, 0); glVertex3f(-0.12, 1.53, -0.99);
    glTexCoord2f(1, 1); glVertex3f(-0.12, 1.67, -0.99);
    glTexCoord2f(0, 1); glVertex3f(0.12, 1.67, -0.99);
    glTexCoord2f(0, 0); glVertex3f(0.12, 1.53, -0.99);

    // Right in cab
    glColor4f(r,0,0.6,1);
    glTexCoord2f(1, 0); glVertex3f(0.98, 1.55, -0.1);
    glTexCoord2f(1, 1); glVertex3f(0.98, 1.65, -0.1);
    glTexCoord2f(0, 1); glVertex3f(0.98, 1.65, 0.1);
    glTexCoord2f(0, 0); glVertex3f(0.98, 1.55, 0.1);

    glColor4f(0,0,0,1);
    glTexCoord2f(1, 0); glVertex3f(0.99, 1.53, -0.12);
    glTexCoord2f(1, 1); glVertex3f(0.99, 1.67, -0.12);
    glTexCoord2f(0, 1); glVertex3f(0.99, 1.67, 0.12);
    glTexCoord2f(0, 0); glVertex3f(0.99, 1.53, 0.12);

    // Left in cab
    glColor4f(r,0.6,0,1);
    glTexCoord2f(1, 0); glVertex3f(-0.98, 1.55, -0.1);
    glTexCoord2f(1, 1); glVertex3f(-0.98, 1.65, -0.1);
    glTexCoord2f(0, 1); glVertex3f(-0.98, 1.65, 0.1);
    glTexCoord2f(0, 0); glVertex3f(-0.98, 1.55, 0.1);

    glColor4f(0,0,0,1);
    glTexCoord2f(1, 0); glVertex3f(-0.99, 1.53, -0.12);
    glTexCoord2f(1, 1); glVertex3f(-0.99, 1.67, -0.12);
    glTexCoord2f(0, 1); glVertex3f(-0.99, 1.67, 0.12);
    glTexCoord2f(0, 0); glVertex3f(-0.99, 1.53, 0.12);
  glEnd();
}


void Hummer::draw_circle(float r, float x, float y, float z) {
	int amt = 30;  // # of triangles used to draw circle
	float Pi2 = 2.0f * M_PI;

	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(x, y, z); // center of circle
		for(int i = 0; i <= amt;i++) {
			glVertex3f(
		        x + (r * cos(i *  Pi2 / amt)),
			    y + (r * sin(i * Pi2 / amt)),
                z
			);
		}
	glEnd();
}
