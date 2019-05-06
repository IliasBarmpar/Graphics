#include "trafficlight.hpp"

TrafficLight::TrafficLight(float x, float y, float z, float th) : startingAngle(th),
                                                                    red(0.0),
                                                                    green(1.0),
                                                                    blue(0.0),
                                                                    state(GREEN){
    startingPosition.x = x;
    startingPosition.y = y;
    startingPosition.z = z;
    obj_loader obj("./trafficlight.obj");
    md = obj.get_model();
}

void TrafficLight::Display() {
    glPushMatrix();
        glTranslatef(startingPosition.x, startingPosition.y, startingPosition.z);
        glScalef(0.025, 0.025, 0.025);

        glColor3f(red, green, blue);
        // glColor3ub(217.0, 191.0, 169.0);


        glBegin(GL_TRIANGLES);
            for (int i = 0; i < md.obj_faces.size(); i++) {
              // if (md.obj_vertices[md.obj_faces[i].vtx_indices[0]-1].y >= 36.2
              //     && md.obj_vertices[md.obj_faces[i].vtx_indices[0]-1].y <= 38.8
              //     && md.obj_vertices[md.obj_faces[i].vtx_indices[0]-1].x >= -1.2
              //     && md.obj_vertices[md.obj_faces[i].vtx_indices[0]-1].x <= 1.2 ) {
              //     if (getState() == RED) {
              //         glColor3ub(255.0, 0.0, 0.0);
              //     }
              //     else
              //       glColor3ub(0.0, 255.0, 0.0);
              //
              // }
              // else{
              //     glColor3ub(217.0, 191.0, 169.0);
              // }
              glNormal3f(md.obj_normals[md.obj_faces[i].norm_indices[0]-1].x,md.obj_normals[md.obj_faces[i].norm_indices[0]-1].y,md.obj_normals[md.obj_faces[i].norm_indices[0]-1].z);
              glVertex3f(md.obj_vertices[md.obj_faces[i].vtx_indices[0]-1].x,md.obj_vertices[md.obj_faces[i].vtx_indices[0]-1].y,md.obj_vertices[md.obj_faces[i].vtx_indices[0]-1].z);

              glNormal3f(md.obj_normals[md.obj_faces[i].norm_indices[1]-1].x,md.obj_normals[md.obj_faces[i].norm_indices[1]-1].y,md.obj_normals[md.obj_faces[i].norm_indices[1]-1].z);
              glVertex3f(md.obj_vertices[md.obj_faces[i].vtx_indices[1]-1].x,md.obj_vertices[md.obj_faces[i].vtx_indices[1]-1].y,md.obj_vertices[md.obj_faces[i].vtx_indices[1]-1].z);

              glNormal3f(md.obj_normals[md.obj_faces[i].norm_indices[2]-1].x,md.obj_normals[md.obj_faces[i].norm_indices[2]-1].y,md.obj_normals[md.obj_faces[i].norm_indices[2]-1].z);
              glVertex3f(md.obj_vertices[md.obj_faces[i].vtx_indices[2]-1].x,md.obj_vertices[md.obj_faces[i].vtx_indices[2]-1].y,md.obj_vertices[md.obj_faces[i].vtx_indices[2]-1].z);
            }
        glEnd();
    glPopMatrix();
}

void TrafficLight::changeState(int color) {
		state = color;
		if (color == GREEN) {
			red = 0.0;
			green = 1.0;
			blue = 0.0;
		}else if (color == YELLOW) {
			red = 1.0;
			green = 1.0;
			blue = 0.0;
		}else if (color == RED) {
			red = 1.0;
			green = 0.0;
			blue = 0.0;
		}
}
