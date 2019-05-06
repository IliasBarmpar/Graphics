#pragma once
#include "obj_loader.hpp"
#include "math.h"
#include "gl/glut.h"

#define PI 3.14159
static float carScale = 0.0015;

class Car{
	private:
        model md;
		point centerOfMass;
        point min;
		point max;
        point startingPosition;

        int movingStage;
        float startingAngle;
        float frontDist;
		float backDist;
		bool moving;
		bool visible;
	public:
		int laps;
		float speed;
		point currentPosition;
		float currentAngle;

        Car(float, float);
		void Display();

        ////////////SET/////////////////
        void setCenterOfMass();
        void setMinMax();
        void setMovingStage(int a) { movingStage = a; }
        void makeVisible() { visible = true; }
        void makeInvisible() { visible = false; }
        void stop() { moving = false; }
        void start() { moving = true; }

        ////////////GET/////////////////
		int getMovingStage() { return movingStage; }
		bool getVisibility() { return visible; }
		float getFrontDist() { return frontDist; }
		float getBackDist() { return backDist; }
		///////////////////////////////

        void reset();
		void Movement(float, float, float);
};
