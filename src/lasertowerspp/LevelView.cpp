//
//  LevelView.cpp
//  lasertowerspp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 27.05.12.
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

#include "LevelView.h"
#include "gl_util.h"


void LevelView::draw()
{
	glColorBackup;
	
	const int field_size = _model->getFieldSize();
	glPushMatrix();
	glScalef(field_size, field_size, 0);
	glTranslatef(-_width/2.0, -_height/2.0, 0);
	
	
	// TODO render level map
	for (int y=0; y<_height; y++) {
		for (int x=0; x<_width; x++) {
			glPushMatrix();
			
			glTranslatef(x, y, 0);
			
			int flag = _model->getFieldFlag(x,y);
			
			if (IS_FLAG(flag, FLAG_INITIAL)) {
				glColorRed;
			} else if (IS_FLAG(flag, FLAG_FINAL)) {
				glColorOrange;
			} else if (IS_FLAG(flag, FLAG_OCCUPIED)) {
				glColorDarkGreen;
			} else if (IS_FLAG(flag, FLAG_PATH)) {
				glColorWhite;
			} else {
				glColorLightGreen;
			}
			
			glBegin(GL_QUADS);
			glVertex2f(0,0);
			glVertex2f(1,0);
			glVertex2f(1,1);
			glVertex2f(0,1);
			glEnd();
			
			glPopMatrix();
		}
	}
	glPopMatrix();
	
	
	// render a grid (TODO this is only interesting for debugging purposes)
	
	glColorYellow;
	
	glPushMatrix();
	glScalef(field_size, field_size, 0);
	glTranslatef(-_width/2.0, -_height/2.0, 0);
	
	glPushMatrix();
	for (int y = 0; y < _height; y++) {
		glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(_width, 0);
		glEnd();
		glTranslatef(0, 1, 0);
	}
	glPopMatrix();
	
	glPushMatrix();
	for (int x = 0; x < _width; x++) {
		glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(0, _height);
		glEnd();
		glTranslatef(1, 0, 0);
	}
	glPopMatrix();
	
	glPopMatrix();
	
	
	glLineWidth(1.0);
	
	glColorReset;
}

