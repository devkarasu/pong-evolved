#include "pch.h"
#include "objects.h"
#include "draw_item.h"

Ball::Ball() :x(0), z(0), x_speed(0.2), z_speed(0.4) {};

void Ball::draw() {
  glPushMatrix();
  glTranslated(x, 0, z);
  glutSolidCube(1.0);
  glPopMatrix();

  x += x_speed;
  z += z_speed;
}
BarPair::BarPair(double length, double width, double angle, double limit) 
  : position(0), length(length), width(width), speed(0), angle(angle), limit(limit) { }

void BarPair::moveRight(double a) {
  this->speed += a;
  position += speed;
  if (position > limit)
    position = limit;
  else if (position < -limit)
    position = -limit;
}

void BarPair::moveLeft(double a) {
  this->speed += a;
  position -= speed;
  if (position > limit)
    position = limit;
  else if (position < -limit)
    position = -limit;
}

void BarPair::draw() const {
  for (int i = -1; i < 2; i += 2) {
    glPushMatrix();
    if (angle == 0)
      glTranslated(position, 0.0, i * width / 2);
    else
      glTranslated(i * width / 2, 0.0, position);
    glRotated(angle, 0.0, 1.0, 0.0);
    drawPrism(1.0, length);
    glPopMatrix();
  }
}

double BarPair::getSpeed() const {
  return speed;
}

void BarPair::stop() {
  speed = 0;
}