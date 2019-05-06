#pragma once
#include "obj_loader.hpp"
#include "gl/glut.h"

#define RED 1
#define GREEN 2
#define YELLOW 3
#define PI 3.14159

class TrafficLight{
	private:
		// point centerOfMass;
		model md;
        int state;

    	float red;
		float green;
		float blue;
	public:
		float startingAngle;
		point startingPosition;
		point currentPosition;
        
        TrafficLight(float, float, float, float);
		void Display();
        void changeState(int);
        int getState() { return state; }
};
