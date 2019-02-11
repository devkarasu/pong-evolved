#pragma once

struct Particle {
  double pos[3];
  double vec[3];
  int life;
  int life_max;

  Particle();
  Particle(double x, double y, double z, int life);
  Particle(const Particle& lhs);

  bool draw();
};

struct Particles {
  std::vector<Particle> data;

  Particles();
  Particles(int n, double x, double y, double z);
  void draw();

  void addParticles(int n, double x, double y, double z);
};