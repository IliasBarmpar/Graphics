#include "car.hpp"

Car::Car(float x, float z) : movingStage(1),
                            currentAngle(0),
                            startingAngle(180),
                            speed(1.0),
                            moving(true),
                            visible(true),
							laps(0) {
    currentPosition.x = 0;
    currentPosition.y = 0;
    currentPosition.z = 0;
    obj_loader obj("./clk.obj");
    md = obj.get_model();
    setMinMax();

    setCenterOfMass();
    frontDist = (centerOfMass.x - min.x)*carScale;
	backDist  = (max.x - centerOfMass.x)*carScale;
    startingPosition.x = x;
    startingPosition.y = -carScale * min.z;
    startingPosition.z = z;
}

void Car::reset() {
    visible = true;
    moving = true;
    speed = 1;
    movingStage = 1;
    currentPosition.x = 0;
    currentPosition.z = 0;
    currentPosition.y = 0;
    currentAngle = 0;
	laps = 0;
}

void Car::setMinMax() {
	min.x = md.obj_vertices[0].x;
	max.x = md.obj_vertices[0].x;

	min.y = md.obj_vertices[0].y;
	max.y = md.obj_vertices[0].y;

	min.z = md.obj_vertices[0].z;
	max.z = md.obj_vertices[0].z;

	for (int i = 1; i < md.obj_vertices.size(); i++) {
		if (md.obj_vertices[i].x < min.x) {
			min.x = md.obj_vertices[i].x;
		}
		if (md.obj_vertices[i].x > max.x) {
			max.x = md.obj_vertices[i].x;
		}

		if (md.obj_vertices[i].y < min.y) {
			min.y = md.obj_vertices[i].y;
		}
		if (md.obj_vertices[i].y > max.y) {
			max.y = md.obj_vertices[i].y;
		}

		if (md.obj_vertices[i].z < min.z) {
			min.z = md.obj_vertices[i].z;
		}
		if (md.obj_vertices[i].z > max.z) {
			max.z = md.obj_vertices[i].z;
		}
	}
}

void Car::setCenterOfMass() {
	float xsum = 0, ysum = 0, zsum = 0;
	for (int i = 0; i <md.obj_vertices.size(); i++) {
		xsum += md.obj_vertices[i].x;
		ysum += md.obj_vertices[i].y;
		zsum += md.obj_vertices[i].z;
	}
	centerOfMass.x = (float)xsum / md.obj_vertices.size();
	centerOfMass.y = (float)ysum / md.obj_vertices.size();
	centerOfMass.z = (float)zsum / md.obj_vertices.size();
}

void Car::Movement( float dt, float L, float R) {
	if (moving) {
		if (movingStage == 1) { //katw eutheia
			currentPosition.x += speed * dt;
			currentPosition.z = 0;
			currentPosition.y = 0;
			if (currentPosition.x >= 2 * L)
				movingStage = 2;
		}
		else if (movingStage == 2) { //deksia strofh
			currentAngle += (speed / R)*dt * 50;
			currentPosition.x = 2 * L + R * sin(currentAngle * PI / 180);
			currentPosition.z = 0 + R * (cos(currentAngle * PI / 180) - 1);
			if (currentAngle >= 180) {
				movingStage = 3;
				currentAngle = 180;
			}
		}
		else if (movingStage == 3) { //panw eutheia
			currentPosition.x -= speed * dt;
			if (currentPosition.x <= 0)
				movingStage = 4;
		}
		else if (movingStage == 4) { //aristerh strofh
			currentAngle += (speed / R)*dt * 50;
			currentPosition.x = R * sin(currentAngle * PI / 180);
			currentPosition.z = R * (cos(currentAngle * PI / 180) - 1);
			if (currentAngle >= 360) {
				movingStage = 1;
				currentAngle = 0;
				laps++;
			}
		}
	}
}

void Car::Display() {
	glPushMatrix();
		glTranslatef(currentPosition.x, currentPosition.y, currentPosition.z);
		glTranslatef(startingPosition.x, startingPosition.y, startingPosition.z);
        glRotatef(currentAngle, 0, 1, 0);
		glRotatef(startingAngle, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
        glScalef(carScale, carScale, carScale);
        glTranslatef(-centerOfMass.x, -centerOfMass.y, -centerOfMass.z);
		// glColor3f(0.8, 0.8, 0.8);
       // glColor3ub(217.0, 191.0, 169.0);
			glBegin(GL_TRIANGLES);
                for (int i = 0; i < md.obj_faces.size(); i++) {
                  glVertex3f(md.obj_vertices[md.obj_faces[i].vtx_indices[0]-1].x,md.obj_vertices[md.obj_faces[i].vtx_indices[0]-1].y,md.obj_vertices[md.obj_faces[i].vtx_indices[0]-1].z);
                  glVertex3f(md.obj_vertices[md.obj_faces[i].vtx_indices[2]-1].x,md.obj_vertices[md.obj_faces[i].vtx_indices[2]-1].y,md.obj_vertices[md.obj_faces[i].vtx_indices[2]-1].z);
                  glVertex3f(md.obj_vertices[md.obj_faces[i].vtx_indices[1]-1].x,md.obj_vertices[md.obj_faces[i].vtx_indices[1]-1].y,md.obj_vertices[md.obj_faces[i].vtx_indices[1]-1].z);
                }
		    glEnd();
	glPopMatrix();
}
