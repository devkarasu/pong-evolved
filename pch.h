// pch.h: This is a precompiled header file. 
// Files listed below are compiled only once, improving build performance for future builds. 
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds. 
// Do not add files that you will frequently be updating here (this negates the performance advantage).

#ifndef PCH_H
#define PCH_H

// TODO: add headers that you want to pre-compile here
#include <iostream>
#include <GL/glut.h>
#include <random>
#include <vector>
#include <string>
#include <MMSystem.h>

static std::random_device seed;
static std::mt19937 mt(seed());

#endif //PCH_H
