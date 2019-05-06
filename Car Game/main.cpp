#include "visuals.hpp"

int main(int argc, char* argv[]){
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_MULTISAMPLE | GLUT_DOUBLE| GLUT_DEPTH);
    glutInitWindowSize(1000,600);
    glutInitWindowPosition(1000,50);

    glutCreateWindow("Road Rage");
    Setup();

    glutDisplayFunc(Render);
    glutReshapeFunc(Resize);

    glutIdleFunc(Idle);
    glutKeyboardFunc(Keyboard);

    glutSpecialFunc(SpecialInput);
    glutMouseFunc(Mouse);

    glutCreateMenu(MenuSelect);
    glutAddMenuEntry("Easy",EASY);
    glutAddMenuEntry("Medium",MEDIUM);
    glutAddMenuEntry("Hard",HARD);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);

    glutMainLoop();
    return 0;
}
