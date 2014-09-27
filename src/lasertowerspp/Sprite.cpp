//
//  Sprite.m
//  LaserTowers
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 23.03.12.
//  Copyright 2012 Eduard Feicho. All rights reserved.
//

#include "Sprite.h"

#include <opengl/System.h>


void Sprite::move(float delta, cv::Vec3f direction)
{
	
}


void Sprite::animate(float delta)
{
	
}


void Sprite::draw()
{
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	cv::Vec3f position = getPosition();
	glTranslatef( position[0], position[1], position[2] );
	_texture->draw();
	glPopMatrix();
}







