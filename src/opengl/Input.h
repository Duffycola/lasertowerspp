//
//  Input.cpp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 05.11.11.
//  Copyright 2011 Eduard Feicho. All rights reserved.
//

#ifndef __INPUT_H
#define __INPUT_H


#include <iostream>
using namespace std;
#include <opengl/System.h>

#include <math.h>

#include <opencv2/core/core.hpp>


#include "util.h"



extern bool repaint;

namespace Input {
	
	extern int NVERT;
	
	extern int time_current, time_lastframe, time_last, time_lastAnimChanged;
	extern int time_limit;
	
	extern bool editing;
	extern bool animateControlePoints;
	extern bool firstAnimateControlePoints;
	extern bool drawTangents;
	extern bool drawHelp;
	
	
	void initInput();
	void initLight();
	float handleFramerate();
	
	void keyPressed(unsigned char key, int x, int y);
	void keySpecial(int key, int x, int y);
	void keyUp(unsigned char key, int x, int y);
	void keySpecialUp(int key, int x, int y);
	void keyOperations(int);
	void mouseButton(int boton, int estado, int x, int y );
	void mouseMove(int x, int y );
	
	
	void setEditing(bool editmode);
		
	extern bool keyStates[256];
	extern bool keySpecialStates[256];
	extern const float deltaKeyboard;
	
	
	extern int screen_width;
	extern int screen_height;
	
	// Mouse movement
	extern int last_x;
	extern int last_y;
	
	// Camera rotation angles
	extern bool rotation;
	extern float rotationX;
	extern float rotationY;
	extern float rotationXold;
	extern float rotationYold;
	extern float rotationDeltaX;
	extern float rotationDeltaY;
	
	extern double zoom;
	
	extern cv::Vec3f translation;

};


#endif
