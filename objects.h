#pragma once

enum AXIS { X, Y, Z };

struct Ball {
  double x;
  double z;

  double x_speed;
  double z_speed;

  double size;

  int score;

  Ball();
  void draw();
  void hit(AXIS axis);
};

class BarPair {
  double position;
  double length; // バーの長さ
  double width; // バー間の距離
  double speed;
  double angle;
  double limit; // バーの移動できる範囲(|position|の最大値)

public:
  BarPair(double length, double width, double angle, double limit);
  void moveRight(double a);
  void moveLeft(double a);

  void draw() const;

  double getSpeed() const;
  void stop();

  int checkHit(Ball& ball);
};

