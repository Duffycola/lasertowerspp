//
//  gl_util.h
//  lasertowerspp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 19.05.12.
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

#ifndef lasertowerspp_gl_util_h
#define lasertowerspp_gl_util_h

#include <iostream>
#include <sstream>
#include <string>
using namespace std;



#include <math.h>
#define DEGREE2RADIAN(deg)  ((deg)*M_PI/180.0)




#include <opengl/System.h>






#define glColorRed            glColor3f( 1, 0, 0 )
#define glColorGreen          glColor3f( 0, 1, 0 )
#define glColorBlue           glColor3f( 0, 0, 1 )
#define glColorYellow         glColor3f( 1, 1, 0 )
#define glColorOrange         glColor3f( 1, 0.5, 0 )
#define glColorBlack          glColor3f( 0, 0, 0 )
#define glColorWhite          glColor3f( 1, 1, 1 )
#define glColorDarkGreen      glColor3f( 0, 0.2, 0 )
#define glColorLightGreen     glColor3f( 0, 0.6, 0 )



#define glColorBackup         GLfloat currentColor[4]; glGetFloatv(GL_CURRENT_COLOR, currentColor);
#define glColorReset          glColor4fv(currentColor);

void renderBitmapString(
						float x,
						float y,
						float z,
						void *font,
						const char *string);

void renderStrokeFontString(
							float x,
							float y,
							float z,
							void *font,
							char *string);

void restorePerspectiveProjection();

void setOrthographicProjection();

const float DEG2RAD = 3.14159/180;

void drawCircle(float radius);
void drawDashedCircle(float radius, float dashed_arc_angle, float offset);
void drawArc(float radius, float start_angle, float arc_angle);
void drawArc(float radius, float start_angle, float arc_angle, int num_segments);
void drawString(string& str);

void drawBox(float scale = 1.0);
void drawBoxFilled(float scale = 1.0);
void drawCross(float scale = 1.0);


#endif
