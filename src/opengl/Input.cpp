//
//  Input.cpp
//  lasertowerspp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 21.05.12.
//
//
// The MIT License (MIT)
//
// Copyright (c) 2012 Eduard Feicho
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//

#include "Input.h"

#include "globals.h"

#include "NotificationCenter.h"
#include <opencv2/core/core.hpp>

#include "util.h"

namespace Input {
	
	bool repaint = false;
	
	int NVERT = 10;
	
	// Frames per second timing
	int time_current = 0;
	int time_lastframe = 0;
	int time_last = 0;
	int time_lastAnimChanged = 0;

	int time_limit = 10;
	
	bool editing = false;
	bool animateControlePoints		= false;
	bool firstAnimateControlePoints = false;
	bool drawTangents = true;
	bool drawHelp = true;

	// Screen dimensions
	int screen_width = 800, screen_height = 600;
	
	// Mouse movement
	int   last_x = 0, last_y = 0;

	// 3D Camera
	double zoom = 10;
	cv::Vec3f translation(0,0,0);
	bool rotation = false;
	float rotationX = 0, rotationY = 0;
	float rotationXold = 0, rotationYold = 0;
	float rotationDeltaX = 0, rotationDeltaY = 0;

	// Keyboard states
	bool keyStates[256];
	bool keySpecialStates[256];
	const float deltaKeyboard = 0.5f;


};

void Input::mouseButton( int boton, int estado, int x, int y )
{
	if (boton == GLUT_LEFT_BUTTON) {
		if (estado == GLUT_DOWN) {
			x -= screen_width / 2.0;
			y -= screen_height / 2.0;
			
			last_x = x;
			last_y = y;
			
			cv::Vec3f* v = new cv::Vec3f(x,y,0);
			NotificationCenter::defaultCenter()->postNotification(MOUSE_CLICK_NOTIFICATION, v);
			delete v;
		}
	}
}


void Input::mouseMove(int x, int y)
{
	if (rotation) {
		
		rotationDeltaX = (float) (last_x - x);
		rotationDeltaY = (float) (last_y - y);
		
		rotationDeltaX /= screen_width;
		rotationDeltaY /= screen_height;
		
		rotationX = rotationXold + rotationDeltaX;
		rotationY = rotationYold + rotationDeltaY;
		
		if (editing) {
			repaint = true;
		}
		glutPostRedisplay();
	}
}



void Input::keyPressed(unsigned char key, int x, int y)
{
	cout << key;
	keyStates[key] = true;
	
	if (keyStates['+']) {
		game_speed_factor = 2.0;
	}
	if (keyStates['-']) {
		game_speed_factor = 1.0;
	}
	if (keyStates['p']) {
		game_pause = !game_pause;
	}
	
	glutPostRedisplay();
}



void Input::keySpecial(int key, int x, int y)
{
	keySpecialStates[key] = true;
	glutPostRedisplay();
}



void Input::keyUp(unsigned char key, int x, int y)
{
	if (key == 'e') {
		setEditing(!editing);
	}
	
	if (key == 't') {
		drawTangents = !drawTangents;
	}
	if (key == 'h') {
		drawHelp = !drawHelp;
	}
	

	
	keyStates[key] = false;
	
	glutPostRedisplay();
}



void Input::keySpecialUp(int key, int x, int y)
{
	keySpecialStates[key] = false;
	glutPostRedisplay();
}



void Input::keyOperations(int time_delta)
{
	if (time_delta > time_limit) {
		time_delta = time_limit;
	}
	float d = deltaKeyboard*(time_delta/100.0f);
	
	if (keyStates['o']) {
		zoom += d;
	}
	if (keyStates['l'] && zoom > d) {
		zoom -= d;
	}
	
	if (keyStates['q']) {
		exit(-1);
	}
}


void Input::initInput() {
	time_lastframe = glutGet(GLUT_ELAPSED_TIME);
	time_last = time_lastframe;
	
	memset(&keyStates, 0, sizeof(bool)*256);
	memset(&keySpecialStates, 0, sizeof(bool)*256);
	
	glutMotionFunc(mouseMove);
	glutMouseFunc(mouseButton);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(keySpecial);
	glutSpecialUpFunc(keySpecialUp);
}



void Input::initLight()
{
	
	GLfloat ambient[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
	
	GLfloat lmodel_ambient[] = {1, 1, 1, 1.0};
	GLfloat local_view[] = {0.0};
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT3, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
	
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	
	glFrontFace(GL_CW);
	
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	
	glShadeModel(GL_SMOOTH);
}



float Input::handleFramerate()
{
	time_current = glutGet(GLUT_ELAPSED_TIME);
	
	int time_deltaframe = time_current - time_lastframe;
	time_last = time_current;
	
	if (time_deltaframe < time_limit) {
		return -1;
	}
	keyOperations(time_deltaframe);
	
	time_lastframe = time_current;
	
	return time_deltaframe;
}



void Input::setEditing(bool editmode)
{
	editing = editmode;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (Input::editing) {
		glOrtho(-1.0, 1.0, -1.0, 1.0, -10000.0, 10000.0);
	} else {
		gluOrtho2D(0.0, (GLfloat)screen_width, 0.0, (GLfloat)screen_height);
	}
	
	
	cout << " Editing: " << editing << endl;
	glutPostRedisplay();
}
