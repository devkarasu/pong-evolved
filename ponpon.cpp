#include "pch.h"
#include "draw_item.h"
#include "objects.h"
#include "particle.h"

void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void specialkeyDown(int key, int x, int y);
void specialkeyUp(int key, int x, int y);
void timer(int t);
void timer_gameover1(int t);
void timer_gameover2(int t);
void printScore();
void printRule();

enum GameState { START, PLAY, GAMEOVER };
GameState gamestate = START;

Ball ball;
Particles p;
BarPair bar_x(0.8, 4, 0, 1.6);
BarPair bar_z(0.8, 4, 90, 1.6);
bool isPressL = false;
bool isPressR = false;
bool isPressU = false;
bool isPressD = false;

int score = 0;

// Initialization
void GLUT_INIT() {
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowSize(640, 480);
  glutCreateWindow("PONG:Evolved");
}

void GLUT_CALL_FUNC() {
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutTimerFunc(0, timer, 20);
  glutKeyboardFunc(keyboard);
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

  printRule();

  glutMainLoop();

  return 0;
}

// Callback Functions
void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  // 視点の設定
  gluLookAt(4.0, 10.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  // 軸の表示
  //drawAxis();

  switch (gamestate) {
  case START:
    glColor3d(0.0, 0.7, 0.0);
    bar_x.draw();
    bar_z.draw();
    break;
  case PLAY:
    glColor3d(0.0, 0.7, 0.0);
    bar_x.draw();
    bar_z.draw();
    ball.draw();
    p.draw();
    printScore();
    break;
  case GAMEOVER:
    glColor3d(1, 0, 0);
    bar_x.draw();
    bar_z.draw();
    p.draw();
    printScore();
    break;
  }

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

void keyboard(unsigned char key, int x, int y) {
  if (gamestate == START || gamestate == GAMEOVER) {
    if (key == 's' || key == 'S') {
      std::cout << "Start\n";
      ball = Ball();
      p.data.erase(std::begin(p.data), std::end(p.data));
      score = 0;
      if (gamestate == GAMEOVER)
        glutTimerFunc(20, timer, 20);
      gamestate = PLAY;
    }
  }
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
  if (gamestate == START) {
    glutPostRedisplay();
    glutTimerFunc(t, timer, 20);
  }
  else if (gamestate == PLAY) {
    if (isPressU && isPressD);
    else if (isPressU)
      bar_x.moveLeft(0.02);
    else if (isPressD)
      bar_x.moveRight(0.02);

    if (isPressL && isPressR);
    else if (isPressL)
      bar_z.moveRight(0.02);
    else if (isPressR)
      bar_z.moveLeft(0.02);
    
    int zc = bar_z.checkHit(ball);
    int xc = bar_x.checkHit(ball);
    if (zc == 1) {
      ++score;
      p.addParticles(100, ball.x, 0, ball.z);
    }
    if (xc == 1) {
      ++score;
      p.addParticles(100, ball.x, 0, ball.z);
    }


    if (zc == 0 || xc == 0) {
      gamestate = GAMEOVER;
      p.addParticles(5000, ball.x, 0, ball.z);
      glutPostRedisplay();
      glutTimerFunc(1000, timer_gameover1, 20);
    }
    else {
      glutPostRedisplay();
      glutTimerFunc(t, timer, 20);
    }
  }
}

void timer_gameover1(int t) {
  glutTimerFunc(20, timer_gameover2, 20);
}

void timer_gameover2(int t) {
  glutPostRedisplay();
  if(gamestate == GAMEOVER)
    glutTimerFunc(20, timer_gameover2, 20);
}

void printScore() {
  // スコア表示
  void *font = GLUT_BITMAP_HELVETICA_18;
  std::string cscore = std::to_string(score);
  if (cscore.length() == 1) {
    glRasterPos3d(0, 0, 0);
    glutBitmapCharacter(font, cscore[0]);
  }
  else {
    glRasterPos3d(-0.5, 0, 0);
    for (char x : cscore)
      glutBitmapCharacter(font, x);
  }
}

void printRule() {
  std::cout << "--------------Control-----------------" << std::endl;
  std::cout << "'s' key : GAME START" << std::endl;
  std::cout << "Arrow key : Move Bar" << std::endl;
  std::cout << "--------------------------------------" << std::endl;
}
