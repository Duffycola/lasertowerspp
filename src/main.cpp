#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include <opengl/System.h>

#include "LevelModel.h"
#include "GameController.h"

#include "Input.h"


#include "gl_util.h"
#include "util.h"


bool editMode = false;

void myReshape(GLsizei w, GLsizei h);
void myReshape(GLsizei w, GLsizei h)
{
	cout << "my reshape (" << w << "," << h << ")" << endl;
	
    h = (h == 0) ? 1 : h;
	w = (w == 0) ? 1 : w;
	
	Input::screen_width = w;
	Input::screen_height = h;
	
    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(-w/2.0, +w/2.0, -h/2.0, +h/2.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



void myKeyboard(unsigned char tecla, int x, int y);
void myKeyboard(unsigned char tecla, int x, int y) {
	switch (tecla) {
		case 'q':
			exit(-1);
			break;
			
		case '+':
			game_speed_factor = 2.0;
			break;
		case '-':
			game_speed_factor = 1.0;
			break;
		case 'p':
			game_pause = !game_pause;
			break;
		case '\t':
			if (editMode) {
				
			}
			break;
		case 'e':
			editMode = !editMode;
			if (editMode) {
				cout << "Editmode ON" << endl;
			} else {
				cout << "Editmode OFF" << endl;
			}
			glutPostRedisplay();
			break;
		
		case 27:
			exit(0);
		default:
			break;
	};
	return;
}


GameController* game;

void idle() {
	game->mainLoop();
}

int main(int argc, char** argv)
{
	game = new GameController();
	
	Input::screen_width = 850;
	Input::screen_height = 450;
	
	cout.setf(ios::fixed, ios::floatfield);
	cout.setf(ios::showpoint);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA );
	glutInitWindowSize(Input::screen_width, Input::screen_height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("LaserTowers - Tower Defense Game");
	glutDisplayFunc(idle);
	glutIdleFunc(idle);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(myKeyboard);
	
	Input::initInput();
	game->initGame();
	
	glutMainLoop();
	return(0);
}

