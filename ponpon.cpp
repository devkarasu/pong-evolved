#include "pch.h"
#include "draw_item.h"
#include "bar_pair.h"

void display();
void reshape(int w, int h);
void specialkeyDown(int key, int x, int y);
void specialkeyUp(int key, int x, int y);
void timer(int t);

BarPair bar_x(6, 20, 0, 10);
BarPair bar_z(6, 20, 90, 10);
bool isPressL = false;
bool isPressR = false;
bool isPressU = false;
bool isPressD = false;

// Initialization
void GLUT_INIT() {
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowSize(640, 480);
  glutCreateWindow("PONG");
}

void GLUT_CALL_FUNC() {
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutTimerFunc(0, timer, 20);
  glutSpecialFunc(specialkeyDown);
  glutSpecialUpFunc(specialkeyUp);
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
  gluLookAt(30.0, 40.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  // 軸の表示
  drawAxis();

  // 物体の色
  glColor3d(0.0, 1.0, 0.0);

  // 枠の表示
  bar_x.draw();
  bar_z.draw();

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

void specialkeyDown(int key, int x, int y) {
  if (key == GLUT_KEY_UP) {
    isPressU = true;
  }
  if (key == GLUT_KEY_DOWN) {
    isPressD = true;
  }
  if (key == GLUT_KEY_LEFT) {
    isPressL = true;
  }
  if (key == GLUT_KEY_RIGHT) {
    isPressR = true;
  }
}

void specialkeyUp(int key, int x, int y) {
  if (key == GLUT_KEY_UP) {
    isPressU = false;
    bar_x.stop();
  }
  if (key == GLUT_KEY_DOWN) {
    isPressD = false;
    bar_x.stop();
  }
  if (key == GLUT_KEY_LEFT) {
    isPressL = false;
    bar_z.stop();
  }
  if (key == GLUT_KEY_RIGHT) {
    isPressR = false;
    bar_z.stop();
  }
}

void timer(int t) {
  if (isPressU && isPressD);
  else if (isPressU)
    bar_x.moveLeft(0.05);
  else if (isPressD)
    bar_x.moveRight(0.05);

  if (isPressL && isPressR);
  else if (isPressL)
    bar_z.moveRight(0.05);
  else if (isPressR)
    bar_z.moveLeft(0.05);
  
  glutPostRedisplay();
  glutTimerFunc(t, timer, 20);
}
