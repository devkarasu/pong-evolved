#pragma once

class BarPair {
  double position;
  double length; // バーの長さ
  double width; // バー間の距離
  double speed;
  double angle;

public:
  BarPair(double length, double width, double angle);
  void moveRight(double a);
  void moveLeft(double a);

  void draw() const;

  double getSpeed() const;
  void stop();
};
