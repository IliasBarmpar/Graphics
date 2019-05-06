#include "visuals.hpp"
#include "car.hpp"
#include "trafficlight.hpp"
#include "racetracks.hpp"
#include <sstream>

// Moving / Rotating whichever axis
static float moveX = 0;
static bool animateX = false;
static float rotx = 0.0;
static float rotationSpeedx = 0.04;

static float moveY = 0;
static bool animateY = false;
static float roty = 0.0;
static float rotationSpeedy = 0.04;

static float moveZ = -3.5;
static bool animateZ = false;
static float rotz = 0.0;
static float rotationSpeedz = 0.04;

void resetAxisInfo() {
	moveX = 0;
	animateX = false;
	rotx = 0.0;
	rotationSpeedx = 0.04;

	moveY = 0;
	animateY = false;
	roty = 0.0;
	rotationSpeedy = 0.04;

	moveZ = -3;
	animateZ = false;
	rotz = 0.0;
	rotationSpeedz = 0.04;
}
/////////////////////////////////////

// General Info
float dt = 0.01;
static bool running = false;

// User's car speed info
static bool showVictoryA = false;
static bool showVictoryB = false;

static int lapsA = 3;
static int lapsB = 3;
static float Vmax = 5;
static float Vop = 4;
static float dv = 0.25;
Car carA(-L, R);
Car carB(-L, R + D);

//  Bridge / TrfLight info
static float timerGreen = 0;
static float timerGreenInc = 3 * dt;
static int rnd = 0;
static float timerYellow = 0;
static float sufficientAmmountOfTime = 10;
TrafficLight trfLight(0, 0, -R*2, 0);

// Crash info
static bool showCrash = false;
static float timerCrash = 0;
static float crashDuration = 100;

Racetracks racetracks;

void reset() {
	carA.reset();
	carB.reset();

	// Bridge / TrfLight reset
	timerGreen = 0;
	timerYellow = 0;
	racetracks.resetBridge();
	trfLight.changeState(GREEN);
	///////////////

	timerCrash = 0;
	showCrash = false;

	running = false;
	showVictoryA = false;
	showVictoryB = false;
}

void Text(const char *str, float size) {
	
	glPushMatrix();
		glTranslatef(-1.25, 0 , -3);
		glScalef(size, size, size);
		for (int i = 0; i<strlen(str); i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	glPopMatrix();
}
static float timerWin = 0;
void Render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
                                                         // and the depth buffer
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	stringstream ss , ss1, ss2;
	

	
	if (showVictoryA) {
		timerWin += dt / 2;
		glColor3f(1, 0, 0);
		Text("You Lose !", 0.004f);
		if (timerWin > sufficientAmmountOfTime)
			reset();
	}else if (showVictoryB) {
		timerWin += dt / 2;
		glColor3f(0, 1, 0);
		Text("You Win!", 0.004f);
		if (timerWin > sufficientAmmountOfTime)
			reset();
	}else if (showCrash) {
		timerCrash += dt * 5;
		glColor3f(1, 1, 0);
		Text("CRASH!", 0.006f);
		if (timerCrash > crashDuration)
			reset();
	}
	else{
		// helpers //
		//DrawAxes();
		//DrawTinyHelperTriangles();
		////////////
		ss << "Speed:";
		ss << carB.speed;
		string speedStr = ss.str();
		glPushMatrix();
			glTranslatef(4.5, 2, -3);
			glColor3f(0, 1, 0);
			Text(speedStr.c_str(), 0.003f);
		glPopMatrix();
		ss1 << "A's laps:";
		ss1 << carA.laps;
		speedStr = ss1.str();
		glPushMatrix();
			glTranslatef(-4.5, 2.2, -3);
			glColor3f(0, 1, 0);
			Text(speedStr.c_str(), 0.0015f);
		glPopMatrix();
		ss.clear(); speedStr.clear();
		ss2 << "B's laps:";
		ss2 << carB.laps;
		speedStr = ss2.str();
		glPushMatrix();
			glTranslatef(-4.5, 2, -3);
			glColor3f(0, 1, 0);
			Text(speedStr.c_str(), 0.0015f);
		glPopMatrix();

		glTranslatef(moveX, moveY, moveZ);
		glRotatef(45, 1, 0, 0);
		glRotatef(rotx, 1, 0, 0);
		glRotatef(roty, 0, 1, 0);
		glRotatef(rotz, 0, 0, 1);

		

		if(carA.getVisibility())
			glPushMatrix();
				glColor3f(1, 0, 0);
				carA.Display();
			glPopMatrix();
			
		if(carB.getVisibility())
			glPushMatrix();
				glColor3f(1, 0, 1);
				carB.Display();
			glPopMatrix();

		racetracks.Display();
		trfLight.Display();

	}
    glutSwapBuffers();
}

void Setup(){

	glShadeModel (GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );

	GLfloat light_position[] = { 0.0, -30.0, 0.0, 0.0 };

	glLightfv( GL_LIGHT0, GL_POSITION, light_position);

	GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };


	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);
}

void Idle() {
    if (animateX)
        rotx += rotationSpeedx;
    if (animateY)
        roty += rotationSpeedy;
    if (animateZ)
        rotz += rotationSpeedz;


    if (running) {
		timerGreen += timerGreenInc;
		// If a sufficient ammount of time has passed we can start considering
		// to open the gate
		if (timerGreen > sufficientAmmountOfTime){
			rnd = rand() % 5000;
			if (rnd < 50) {
				if (trfLight.getState() == GREEN)
					trfLight.changeState(YELLOW);
			}
			// to avoid waiting more than necessary let's have a limit to how much we are willing to wait
			else if (timerGreen > sufficientAmmountOfTime * 3) {
				if (trfLight.getState() == GREEN)
					trfLight.changeState(YELLOW);
			}

			// Since we moved from Green to Yellow now we set another timer before opening the bridge
			if (trfLight.getState()==YELLOW){
				timerYellow += dt*3;
				if (timerYellow > sufficientAmmountOfTime) {
					trfLight.changeState(RED);
				}
			}
			// The traffic light is red
			if (trfLight.getState() == RED) {
				racetracks.openBridge();
				// Instructions for CarA
				if (carA.currentPosition.x >= L - 0.1 && carA.currentPosition.x <= L + 0.1 && carA.getMovingStage() == 3)
					carA.stop();

				// Instructions for CarB
				if(carB.getMovingStage() == 3 || carB.getMovingStage() == 4){
					if ( (carB.currentPosition.x - carB.getFrontDist() ) >= 0 && (carB.currentPosition.x - carB.getFrontDist() ) <= L/2) {
						carB.makeInvisible();
						showCrash = true;
					}
					else if ( (carB.currentPosition.x + carB.getBackDist()) >= 0 && (carB.currentPosition.x + carB.getBackDist() ) <= L/2 && carB.currentPosition.z <= -R) {
						carB.makeInvisible();
						showCrash = true;
					}
				}
			}
			// Checks if bridge is being opened and once it is it waits for a return true
			// to allow carA to start / make traffic light green and reset timers
			if(racetracks.bridgeCheck()){
				timerGreen = 0;
				timerYellow = 0;
				trfLight.changeState(GREEN);
				carA.start();
			}
		}

		carA.Movement( dt, L, R);
		carB.Movement( dt, L, R+D);

		if(carA.laps == 3)
			showVictoryA = true;
		if(carB.laps == 3)
			showVictoryB = true;

		// Check if carB (user's car) speed is over the limit while driving in circular motion
		if (carB.getMovingStage() == 4 || carB.getMovingStage() == 2) {
			if (carB.speed >= Vop){
				carB.makeInvisible();
				showCrash = true;
			}
		}
	}
    glutPostRedisplay();
}

void Resize(int w, int h) {
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (float)w / (float)h, 1.0, 500.0);
}

void DrawAxes() {
    glColor3f(0.9, 0.1, 0.1);
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(1000, 0.0, 0.0);
        glColor3f(0.1, 0.9, 0.1);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 1000, 0.0);
        glColor3f(0.1, 0.1, 0.9);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 1000);
        glColor3f(0.5, 0.5, 0.5);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(500, 500, 500);
    glEnd();
}

void DrawTinyHelperTriangles() {
	glColor3f(0.9, 0.9, 0.1);
	glBegin(GL_TRIANGLES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.25, 0.0, 0.0);
		glVertex3f(0.0, 0.25, 0.0);
	glEnd();

	glColor3f(0.1, 0.9, 0.9);
	glBegin(GL_TRIANGLES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.25, 0.0);
		glVertex3f(0.0, 0.0, 0.25);
	glEnd();

	glColor3f(0.9, 0.1, 0.9);
	glBegin(GL_TRIANGLES);

		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0, 0.0, 0.25);
		glVertex3f(0.25, 0.0, 0.0);

	glEnd();
}

void SpecialInput(int key, int x, int y) {
	switch (key) {
    	case GLUT_KEY_UP:    moveY -= 0.25;
    		break;
    	case GLUT_KEY_DOWN:  moveY += 0.25;
    		break;
    	case GLUT_KEY_RIGHT: moveX -= 0.25;
    		break;
    	case GLUT_KEY_LEFT:  moveX += 0.25;
    		break;
    	case GLUT_KEY_F1:    moveZ += 0.25;
    		break;
    	case GLUT_KEY_F2:    moveZ -= 0.25;
    		break;
    	case GLUT_KEY_F3:
    		if (dt <= 0.05)
    			dt += 0.005;
    		break;
    	case GLUT_KEY_F4:
    		if (dt >= 0.005)
    			dt -= 0.005;
    		break;
    	default: break;
    	}
}

void Keyboard(unsigned char key,int x,int y) {
    switch(key) {
        case 27:
            exit(0);
    	case 't': running = true;
    		break;
    	case 's': running = false;
    		break;
    	case 'r':
    		reset();
    		break;
    	case 'p':
    		resetAxisInfo();
    		break;
    	case '7':
    		animateX = !animateX;
    		glutPostRedisplay();
    		break;
    	case '8':
    		rotationSpeedx = -rotationSpeedx;
    		break;
    	case '4':
    		animateY = !animateY;
    		glutPostRedisplay();
    		break;
    	case '5':
    		rotationSpeedy = -rotationSpeedy;
    		break;
    	case '1':
    		animateZ = !animateZ;
    		glutPostRedisplay();
    		break;
    	case '2':
    		rotationSpeedz = -rotationSpeedz;
    		break;
    	case 'w' :
    		if (carB.speed < Vmax)
    			carB.speed += dv;
    		break;
    	case 'x':
    		if (carB.speed > 0)
    			carB.speed -= dv;
    		break;
    	default : break;
	}

	glutPostRedisplay();
}

void Mouse(int button,int state,int x,int y) {
	 if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	 {
		 animateX = !animateX;
         glutPostRedisplay();
	 }
	 if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)
	 {
		 animateY = !animateY;
		 glutPostRedisplay();
	 }
}

void MenuSelect(int choice) {
	switch (choice) {
		case EASY :
			timerGreenInc = 3*dt;
            Vmax = 5;
            Vop = 4;
            carA.speed = 1;
			break;
		case MEDIUM :
			timerGreenInc = 5*dt;
			Vmax = 5 + 2*dv;
            Vop = 4 - 2*dv;
            carA.speed = 1 + 2*dv;
			break;
		case HARD :
			timerGreenInc = 8*dt;
			Vmax = 4 + 2 * dv;
            Vop = 4 - 4*dv;
            carA.speed = 1 + 3*dv;
			break;
	}
}
