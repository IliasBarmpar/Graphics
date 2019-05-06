#pragma once

#include <iostream>
#include <math.h>
#include "gl/glut.h"

#define PI 3.14159

static int stripes = 7;

static float L = 1.5;			//
static float R = 0.8;			//
static float D = 0.4;			//
static float T = 0.05;	//
static float Q = 0.4;	//
static float N = 0.3;	//

static float G = (float)L / 2; // Bridge length

extern float dt;
static float bridgeInc = dt * 100;
static float rotBridge = 0.0;


class Racetracks {
private:
	bool bridgeIsMoving;
public:
    Racetracks() { bridgeIsMoving = false; }
	void Display();
	bool bridgeCheck();

	void openBridge() { bridgeIsMoving = true; }
	void resetBridge();
};
