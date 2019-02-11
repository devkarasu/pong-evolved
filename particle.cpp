#include "pch.h"
#include "particle.h"

std::uniform_real_distribution<> rand_vec(-3.0, 3.0);

Particle::Particle() {};

Particle::Particle(double x, double y, double z, int life) 
  : pos{ x, y, z }, life(life), vec{ rand_vec(mt), rand_vec(mt), rand_vec(mt) }, life_max(life) { }

Particle::Particle(const Particle& lhs)
  : pos{ lhs.pos[0], lhs.pos[1], lhs.pos[2] }, 
  vec{ lhs.vec[0], lhs.vec[1], lhs.vec[2] }, life(lhs.life), life_max(lhs.life_max) {}

bool Particle::draw() {
  if (life-- < 0)
    return true;

  glColor4d(0.3, 1, 0.4, life / (double)life_max);
  glVertex3dv(pos);

  for (int i = 0; i != 3; ++i)
    pos[i] += vec[i];

  return false;
}

Particles::Particles() {}

Particles::Particles(int n, double x, double y, double z) {
  addParticles(n, x, y, z);
}

void Particles::addParticles(int n, double x, double y, double z) {
  for (int i = 0; i != n; ++i) {
    data.push_back(Particle(x, y, z, 1000));
  }
}

void Particles::draw() {
  glEnable(GL_BLEND);
  glPointSize(3);
  glBegin(GL_POINTS);

  auto itr = std::begin(data);
  while (itr != std::end(data)) {
    if (itr->draw())
      itr = data.erase(itr);
    else
      itr++;
  }

  glEnd();
  glDisable(GL_BLEND);
  glPointSize(1);
}
