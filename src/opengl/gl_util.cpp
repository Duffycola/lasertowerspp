//
//  gl_util.cpp
//  lasertowerspp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 20.05.12.
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

#include "gl_util.h"

#include "Input.h"

void renderBitmapString(
						float x,
						float y,
						float z,
						void *font,
						const char *string) {
	
	const char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void renderStrokeFontString(
							float x,
							float y,
							float z,
							void *font,
							const char *string) {  
	
	const char *c;
	glPushMatrix();
	glTranslatef(x, y,z);
	glScalef(0.002f, 0.002f, 0.002f);
	for (c=string; *c != '\0'; c++) {
		glutStrokeCharacter(font, *c);
	}
	glPopMatrix();
}

void restorePerspectiveProjection() {
	
	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();
	
	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void setOrthographicProjection() {
	
	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	
	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();
	
	// reset matrix
	glLoadIdentity();
	
	// set a 2D orthographic projection
	gluOrtho2D(0, Input::screen_width, Input::screen_height, 0);
	
	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}


void drawCircle(float radius)
{	
	glBegin(GL_LINE_LOOP);
	
	for (int i=0; i < 360; i++)
	{
		float degInRad = DEGREE2RADIAN(i);
		glVertex2f(cos(degInRad)*radius, sin(degInRad)*radius);
	}
	
	glEnd();
}

void drawDashedCircle(float radius, float dashed_arc_angle, float offset)
{
	float dash_counter = dashed_arc_angle;
	
	glBegin(GL_LINE_STRIP);
	for (int i=offset; i < 360+offset; i++) {
		dash_counter--;
		if (dash_counter == 0) {
			glEnd();
		} else if (dash_counter < -dashed_arc_angle) {
			dash_counter = dashed_arc_angle;
			glBegin(GL_LINE_STRIP);
		} else if (dash_counter < 0) {
			continue;
		}
		
		float degInRad = DEGREE2RADIAN(i);
		glVertex2f(cos(degInRad)*radius, sin(degInRad)*radius);
	}
	glEnd();
}

void drawArc(float radius, float start_angle, float arc_angle)
{
	glBegin(GL_LINE_STRIP);
	
	for (int i=start_angle; i < start_angle+arc_angle; i++)
	{
		float degInRad = DEGREE2RADIAN(i);
		glVertex2f(cos(degInRad)*radius, sin(degInRad)*radius);
	}
	
	glEnd();
}



void drawArc(float radius, float start_angle, float arc_angle, int num_segments)
{
	//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
	float theta = arc_angle / float(num_segments - 1);
	float tangetial_factor = tanf(theta);
	float radial_factor = cosf(theta);
	
	//we now start at the start angle
	float x = radius * cosf(start_angle);
	float y = radius * sinf(start_angle); 
    
	glBegin(GL_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
	for (int i = 0; i < num_segments; i++) { 
		glVertex2f(x, y);
		
		float tx = -y;
		float ty = x;
		
		x += tx * tangetial_factor;
		y += ty * tangetial_factor;
		
		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
}



void drawString(string& str)
{
	glPushMatrix();
	renderBitmapString(5,30,0,GLUT_BITMAP_HELVETICA_18, str.c_str() );
	glPopMatrix();
}


void drawBox(float scale)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(-scale, -scale);
	glVertex2f(-scale, +scale);
	glVertex2f(+scale, +scale);
	glVertex2f(+scale, -scale);
	glEnd();
}


void drawBoxFilled(float scale)
{
	glBegin(GL_QUADS);
	glVertex2f(-scale, -scale);
	glVertex2f(-scale, +scale);
	glVertex2f(+scale, +scale);
	glVertex2f(+scale, -scale);
	glEnd();
}


void drawCross(float scale)
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(-scale, -scale);
	glVertex2f(+scale, +scale);
	glVertex2f(+scale, -scale);
	glVertex2f(-scale, +scale);
	glEnd();
}


