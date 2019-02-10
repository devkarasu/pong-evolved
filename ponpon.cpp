#include "pch.h"

int quad_face[][4] = {
  {0, 1, 2, 3},
  {1, 5, 6, 2},
  {5, 4, 7, 6},
  {4, 0, 3, 7},
  {4, 5, 1, 0},
  {3, 2, 6, 7}
};

void display();
void reshape(int w, int h);
void drawAxis();
void drawPrism(double thickness, double length);

// Initialization
void GLUT_INIT() {
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowSize(640, 480);
  glutCreateWindow("PONG");
}

void GLUT_CALL_FUNC() {
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
}

void MY_INIT() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
}

// Main
int main(int argc, char *argv[]) {
  glutInit(&argc, argv);

  GLUT_INIT();
  GLUT_CALL_FUNC();
  MY_INIT();

  glutMainLoop();

  return 0;
}

// Callback Functions
void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  // 視点の設定
  gluLookAt(0.0, 80.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

  // 軸の表示
  drawAxis();

  // 物体の色
  glColor3d(0.0, 1.0, 0.0);

  // 枠の表示
  glPushMatrix();
  glTranslated(10.0, 0.0, 0.0);
  glRotated(90, 0.0, 1.0, 0.0);
  drawPrism(1.0, 30);
  glPopMatrix();

  glPushMatrix();
  glTranslated(-10.0, 0.0, 0.0);
  glRotated(90, 0.0, 1.0, 0.0);
  drawPrism(1.0, 30);
  glPopMatrix();

  glPushMatrix();
  glTranslated(0.0, 0.0, 15.0);
  drawPrism(1.0, 21);
  glPopMatrix();

  glPushMatrix();
  glTranslated(0.0, 0.0, -15.0);
  drawPrism(1.0, 21);
  glPopMatrix();

  // 玉の表示
  glPushMatrix();
  glutSolidCube(2);
  glPopMatrix();

  glFlush();
}

void reshape(int w, int h) {
  // ウィンドウの描画範囲
  glViewport(0, 0, w, h);

  // 透視投影
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

// Drawing Functions
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