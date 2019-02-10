#include "pch.h"
#include "bar_pair.h"
#include "draw_item.h"

BarPair::BarPair(double length, double width, double angle) 
  : position(0), length(length), width(width), speed(0), angle(angle) { }

void BarPair::moveRight(double a) {
  this->speed += a;
  position += speed;
}

void BarPair::moveLeft(double a) {
  this->speed += a;
  position -= speed;
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