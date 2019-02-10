#include "pch.h"
#include "draw_item.h"

// 直方体の面情報
int quad_face[][4] = {
  {0, 1, 2, 3},
  {1, 5, 6, 2},
  {5, 4, 7, 6},
  {4, 0, 3, 7},
  {4, 5, 1, 0},
  {3, 2, 6, 7}
};

// 軸の表示
void drawAxis() {
  glBegin(GL_LINES);

  // X
  glColor3d(1.0, 0.0, 0.0);
  glVertex3d(-100.0, 0.0, 0.0);
  glVertex3d(100.0, 0.0, 0.0);

  // Y
  glColor3d(0.0, 1.0, 0.0);
  glVertex3d(0.0, -100.0, 0.0);
  glVertex3d(0.0, 100.0, 0.0);

  // Z
  glColor3d(0.0, 0.0, 1.0);
  glVertex3d(0.0, 0.0, -100.0);
  glVertex3d(0.0, 0.0, 100.0);

  glEnd();

  glColor3d(1.0, 1.0, 1.0);
}

// X軸上に角柱を作る
void drawPrism(double thickness, double length) {
  glBegin(GL_QUADS);

  GLdouble vertex[][3] = {
    {-length / 2, thickness / 2, thickness / 2},
    {-length / 2, -thickness / 2, thickness / 2},
    {-length / 2, -thickness / 2, -thickness / 2},
    {-length / 2, thickness / 2, -thickness / 2},
    {length / 2, thickness / 2, thickness / 2},
    {length / 2, -thickness / 2, thickness / 2},
    {length / 2, -thickness / 2, -thickness / 2},
    {length / 2, thickness / 2, -thickness / 2}
  };

  for (int i = 0; i != 6; ++i) {
    for (int j = 0; j != 4; ++j) {
      glVertex3dv(vertex[quad_face[i][j]]);
    }
  }

  glEnd();
}
