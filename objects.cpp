#include "pch.h"
#include "objects.h"
#include "draw_item.h"

std::uniform_real<> rand_speed(-0.3, 0.3);

Ball::Ball() :x(0), z(0), x_speed(rand_speed(mt)), z_speed(rand_speed(mt)), size(1.0), score(0) {};

void Ball::draw() {
  glPushMatrix();
  glTranslated(x, 0, z);
  glutSolidCube(size);
  glPopMatrix();

  x += x_speed;
  z += z_speed;
}

void Ball::hit(AXIS axis) {
  ++score;
  if (axis == X) {
    z_speed *= -1;
  }
  else if (axis == Z) {
    x_speed *= -1;
  }

  double add = 0.05;
  z_speed += z_speed < 0 ? -add : add;
  x_speed += x_speed < 0 ? -add : add;
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

int BarPair::checkHit(Ball& ball) {
  if (angle == 0) {
    if (ball.z + ball.size / 2 > width / 2 || ball.z - ball.size / 2 < -width / 2) {
      if (ball.x - ball.size / 2 <= position + length / 2 && ball.x + ball.size / 2 >= position - length / 2) {
        ball.hit(X);
        // Hit
        return 1;
      }
      else {
        // ゲームオーバー
        return 0;
      }
    }
    else {
      // 端まで未到達
      return -1;
    }
  }
  else {
    if (ball.x + ball.size / 2 > width / 2 || ball.x - ball.size / 2 < -width / 2) {
      if (ball.z + ball.size / 2 <= position + length / 2 && ball.z - ball.size / 2 >= position - length / 2) {
        ball.hit(Z);
        // Hit
        return 1;
      }
      else {
        // ゲームオーバー
        return 0;
      }
    }
    else {
      // 端まで未到達
      return -1;
    }
  }
}