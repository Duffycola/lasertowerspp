//
//  Enemy.m
//  LaserTowers
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 23.03.12.
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

#include "Enemy.h"
#include "globals.h"
#include "gl_util.h"


void Enemy::move(float delta, cv::Vec3f direction)
{
	if (_alive) {
		setPosition( getPosition() + direction*(delta/500.0f) );
		_time_acc_path += delta;
	}
}



void Enemy::animate(float delta)
{
	
}



void Enemy::draw()
{
	glPushMatrix();
	glColorBackup;
	glColorRed;
	
	cv::Vec3f& position = getPosition();
	
	glTranslatef( position[0]+0.5, position[1]+0.5, position[2] );
	glScalef( 0.5*0.9, 0.5*0.9, 0 );
	drawBox();
	drawCross();
	
	glColorReset;
	glPopMatrix();
}

