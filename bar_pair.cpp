#include "pch.h"
#include "bar_pair.h"
#include "draw_item.h"

BarPair::BarPair(double length, double width, double angle) 
  : position(0), length(length), width(width), speed(0), angle(angle) { }

void BarPair::moveRight(double speed) {
  this->speed = speed;
  position += speed;
}

void BarPair::moveLeft(double speed) {
  this->speed = speed;
  position -= speed;
}

void BarPair::draw() const {
  glPushMatrix();
  glTranslated(width / 2, 0.0, 0.0);
  glRotated(angle, 0.0, 1.0, 0.0);
  drawPrism(1.0, length);
  glPopMatrix();

  glPushMatrix();
  glTranslated(-width / 2, 0.0, 0.0);
  glRotated(angle, 0.0, 1.0, 0.0);
  drawPrism(1.0, length);
  glPopMatrix();
}

double BarPair::getSpeed() const {
  return speed;
}
