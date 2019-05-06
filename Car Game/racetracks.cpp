#include "racetracks.hpp"

void Racetracks::Display() {
	//			Pista				//
	// Panw euthis dromos //
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 1.00);
		glVertex3f(-L / 2, 0.0, -R + N);
		glVertex3f(-L / 2, 0.0, -R - D - N);
		glVertex3f(L, 0.0, -R - D - N);
		glVertex3f(L, 0.0, -R + N);
	glEnd();

    //gefyra
	glPushMatrix();
		//  rotation //
		glTranslatef(-(L - G), 0.0, 0.0);
		glRotatef(-rotBridge, 0, 0, 1);
		glTranslatef((L - G), 0.0, 0.0);
		///////////////
		glBegin(GL_QUADS);
			glColor3f(1.0, 0.0, 1.0);
			glVertex3f(-L, 0.0, -R + N);
			glVertex3f(-L, 0.0, -R - D - N);
			glVertex3f(-L / 2, 0.0, -R - D - N);
			glVertex3f(-L / 2, 0.0, -R + N);
		glEnd();
	glPopMatrix();



	// katw euthis dromos //
	glBegin(GL_QUADS);
		glColor3f(0.0, 0.0, 1.00);
		glVertex3f(-L, 0.0, R - N);
		glVertex3f(L, 0.0, R - N);
		glVertex3f(L, 0.0, R + D + N);
		glVertex3f(-L, 0.0, R + D + N);
	glEnd();

	// ekkinhsh //
	{
		glColor3f(1, 1, 1);
		float P = 2 * ((D + 2 * N - 2 * T) / (3 * stripes - 1));
		float z = R + D + N - T;
		for (int i = 0; i < stripes; i++) {
			glBegin(GL_QUADS);
			glColor3f(1.0, 1.0, 1.0);
				glVertex3f(-L + Q, 0.001, z);
				glVertex3f(-L + Q, 0.001, z - P);
				glVertex3f(-L + Q + P, 0.001, z - P);
				glVertex3f(-L + Q + P, 0.001, z);
			glEnd();
			z = z - 3 * P / 2;
		}
	}

	// deksia strofh //

	glPushMatrix();
		glColor3f(0.0, 0.0, 1.00);
		glTranslatef(L, 0.0, 0.0);
		glBegin(GL_QUAD_STRIP);
			glVertex3f(0.0, 0.0, -R + N);
			glVertex3f(0.0, 0.0, -R - D - N);
			for (float th = -89; th <= -1; th = th + 0.5) {
				glVertex3f((R - N)*cos(th*PI / 180), 0.0, (R - N)*sin(th*PI / 180));
				glVertex3f((R + D + N)*cos(th*PI / 180), 0.0, (R + D + N)*sin(th*PI / 180));
			}
			glVertex3f(R - N, 0.0, 0.0);
			glVertex3f(R + D + N, 0.0, 0.0);
			for (float th = 1; th <= 89; th = th + 0.5) {
				glVertex3f((R - N)*cos(th*PI / 180), 0.0, (R - N)*sin(th*PI / 180));
				glVertex3f((R + D + N)*cos(th*PI / 180), 0.0, (R + D + N)*sin(th*PI / 180));
			}
			glVertex3f(0.0, 0.0, (R - N));
			glVertex3f(0.0, 0.0, (R + D + N));
		glEnd();
	glPopMatrix();

	// aristerh strofh //
	glPushMatrix();
		glColor3f(0.0, 0.0, 1.00);
		glTranslatef(-L, 0.0, 0.0);
		glBegin(GL_QUAD_STRIP);
			glVertex3f(0.0, 0.0, (R - N));
			glVertex3f(0.0, 0.0, (R + D + N));
			for (float th = 91; th <= 179; th = th + 1) {
				glVertex3f((R - N)*cos(th*PI / 180), 0.0, (R - N)*sin(th*PI / 180));
				glVertex3f((R + D + N)*cos(th*PI / 180), 0.0, (R + D + N)*sin(th*PI / 180));
			}
			glVertex3f(-R + N, 0.0, 0.0);
			glVertex3f(-(R + D + N), 0.0, 0.0);
			for (float th = 181; th <= 269; th = th + 1) {
				glVertex3f((R - N)*cos(th*PI / 180), 0.0, (R - N)*sin(th*PI / 180));
				glVertex3f((R + D + N)*cos(th*PI / 180), 0.0, (R + D + N)*sin(th*PI / 180));
			}
			glVertex3f(0.0, 0.0, -R + N);
			glVertex3f(0.0, 0.0, -R - D - N);
		glEnd();
	glPopMatrix();
}

bool Racetracks::bridgeCheck() {
	if (bridgeInc < 0)
		bridgeInc = -dt * 3;
	else
		bridgeInc = dt * 3;

	if (bridgeIsMoving) {
		rotBridge += bridgeInc;
		if (rotBridge > 45)
			bridgeInc = -bridgeInc;
		if (rotBridge <= 0) {
			rotBridge = 0;
			bridgeInc = dt * 3;
			bridgeIsMoving = false;
			return true;
		}
	}
	return false;
}

void Racetracks::resetBridge() {
	bridgeIsMoving = false;
	rotBridge = 0;
	bridgeInc = dt * 3;
}
