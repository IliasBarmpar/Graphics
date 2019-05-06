#pragma once


#include <string.h>
#include <iostream>
#include "time.h"
#include "gl/glut.h"

#define EASY 1
#define MEDIUM 2
#define HARD 3

using namespace std;

void Setup();
void Render();
void Idle();
void Resize(int w, int h);
void DrawAxes();
void DrawTinyHelperTriangles();
void Keyboard(unsigned char key,int x,int y);
void SpecialInput(int key, int x, int y);
void Mouse(int button,int state,int x,int y);
void MenuSelect(int choice);
void reset();
