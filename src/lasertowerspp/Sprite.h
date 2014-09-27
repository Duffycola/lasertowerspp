//
//  Sprite.h
//  LaserTowers
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 23.03.12.
//  Copyright 2012 Eduard Feicho. All rights reserved.
//


#ifndef __SPRITE_H
#define __SPRITE_H

#include <iostream>
using namespace std;


#include <opencv2/core/core.hpp>
using namespace cv;


#include <opengl/System.h>
#include "Texture2D.h"

#include "InterfaceDrawable.h"
#include "GameFigureModel.h"



#define TOWERID_LASER  1
#define TOWERID_LASER2 2
#define TOWERID_LASER3 3

#define ENEMYID_LASER   4
#define ENEMYID_LASER2  5
#define ENEMYID_LASER3  6


/**
 * The Sprite class is a model for an animatable, texture-based 2D image.
 * Usually, in 2D games a sprite is rendered using a texture containing 
 * animation frames that are used to render a 2D rectangle.
 */
class Sprite : public InterfaceDrawable, public GameFigureModel
{
public:
	
	Sprite(string filename = "") {
		_texture = new Texture2D(filename);
	}
	
	~Sprite() {
		delete _texture;
	}
	
	
	virtual void draw();
	virtual void move(float delta, cv::Vec3f direction = cv::Vec3f(1,0,0)) = 0;
	virtual void animate(float delta) = 0;
	
	
	// GameFigureModel
	virtual void attack_hit(float attack_power) = 0;
	
	
	void reset() {
		_time_creation = glutGet(GLUT_ELAPSED_TIME);
	}
	
	void setSelected(bool selected) {
		_selected = selected;
	}
	bool isSelected() {
		return _selected;
	}
	
	
	
protected:
	
	unsigned int _id;
	Texture2D *_texture;
	
	bool _selected;
	int _time_creation;
	float _time_since_start;
	
	cv::Vec3f _color;
};

#endif
