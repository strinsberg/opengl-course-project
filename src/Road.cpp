#include "../include/Road.h"
#include "../include/GameObject.h"
#include "../include/LookAt.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


Road::Road(float x, float y, float z, float l, float w, bool isAve)
    : GameObject(x,y,z), l(l), w(w), ave(isAve) {}


Road::~Road() {}


void Road::display(const LookAt& look) {

  glLoadIdentity();
  gluLookAt(look.ex, look.ey, look.ez,
            look.cx, look.cy, look.cz,
            look.ux, look.uy, look.uz);

  // If it is an avenue rotate 90cw and translate it so that the bottom right
  // corner is at the x,y,z given.
  if (ave) {
    glTranslatef(x, y,  z-w);
    glRotatef(-90, 0, 1, 0);
    glTranslatef(-x, -y, -z);
  }

  // Create the road surface and the lines
  glBegin(GL_QUADS);

    // Road surface
    glColor4f(0.2, 0.2, 0.2, 1);

    glTexCoord2f(1, 0); glVertex3f(x, y, z);
    glTexCoord2f(1, 1); glVertex3f(x, y, z-l);
    glTexCoord2f(0, 1); glVertex3f(x+w, y, z-l);
    glTexCoord2f(0, 0); glVertex3f(x+w, y, z);


    // Left side line
    glColor4f(1, 1, 1, 1);

    glTexCoord2f(1, 0); glVertex3f(x, y+0.01, z);
    glTexCoord2f(1, 1); glVertex3f(x, y+0.01, z-l);
    glTexCoord2f(0, 1); glVertex3f(x+(w/10), y+0.01, z-l);
    glTexCoord2f(0, 0); glVertex3f(x+(w/10), y+0.01, z);

    // Right side line
    glTexCoord2f(1, 0); glVertex3f((x+w)-(w/10), y+0.01, z);
    glTexCoord2f(1, 1); glVertex3f((x+w)-(w/10), y+0.01, z-l);
    glTexCoord2f(0, 1); glVertex3f(x+w, y+0.01, z-l);
    glTexCoord2f(0, 0); glVertex3f(x+w, y+0.01, z);

    // 5 Middle lines
    glColor4f(1, 1, 0, 1);
    for (int i = 0; i < 5; i++) {

      float loff = i * (l/5);
      glTexCoord2f(1, 0); glVertex3f(x+(w/2)-(w/20), y+0.01, z-loff);
      glTexCoord2f(1, 1); glVertex3f(x+(w/2)-(w/20), y+0.01, z-loff-(l/10));
      glTexCoord2f(0, 1); glVertex3f(x+(w/2)+(w/20), y+0.01, z-loff-(l/10));
      glTexCoord2f(0, 0); glVertex3f(x+(w/2)+(w/20), y+0.01, z-loff);
    }
  glEnd();
}


void Road::update() {}


/// Intersection /////////////////////////////////////////////////////////////

Intersection::Intersection(float x, float y, float z, float w)
    : GameObject(x,y,z), w(w) {}


Intersection::~Intersection() {}


void Intersection::display(const LookAt& look) {
  glLoadIdentity();
  gluLookAt(look.ex, look.ey, look.ez,
            look.cx, look.cy, look.cz,
            look.ux, look.uy, look.uz);

  // Create the road surface and the lines
  glBegin(GL_QUADS);
    // Road surface
    glColor4f(0.2, 0.2, 0.2, 1);

    glTexCoord2f(1, 0); glVertex3f(x, y, z);
    glTexCoord2f(1, 1); glVertex3f(x, y, z-w);
    glTexCoord2f(0, 1); glVertex3f(x+w, y, z-w);
    glTexCoord2f(0, 0); glVertex3f(x+w, y, z);


    // Bottom left corner
    glColor4f(1, 1, 1, 1);

    glTexCoord2f(1, 0); glVertex3f(x, y+0.01, z);
    glTexCoord2f(1, 1); glVertex3f(x, y+0.01, z-(w/10));
    glTexCoord2f(0, 1); glVertex3f(x+(w/10), y+0.01, z-(w/10));
    glTexCoord2f(0, 0); glVertex3f(x+(w/10), y+0.01, z);

    // Bottom right corner
    glTexCoord2f(1, 0); glVertex3f((x+w)-(w/10), y+0.01, z);
    glTexCoord2f(1, 1); glVertex3f((x+w)-(w/10), y+0.01, z-(w/10));
    glTexCoord2f(0, 1); glVertex3f(x+w, y+0.01, z-(w/10));
    glTexCoord2f(0, 0); glVertex3f(x+w, y+0.01, z);

    // Top left corner
    glTexCoord2f(1, 0); glVertex3f(x, y+0.01, z-w);
    glTexCoord2f(1, 1); glVertex3f(x, y+0.01, (z-w)+(w/10));
    glTexCoord2f(0, 1); glVertex3f(x+(w/10), y+0.01, (z-w)+(w/10));
    glTexCoord2f(0, 0); glVertex3f(x+(w/10), y+0.01, z-w);

    // Top right corner
    glTexCoord2f(1, 0); glVertex3f((x+w)-(w/10), y+0.01, z-w);
    glTexCoord2f(1, 1); glVertex3f((x+w)-(w/10), y+0.01, (z-w)+(w/10));
    glTexCoord2f(0, 1); glVertex3f(x+w, y+0.01, (z-w)+(w/10));
    glTexCoord2f(0, 0); glVertex3f(x+w, y+0.01, z-w);

  glEnd();
}


void Intersection::update() {}
