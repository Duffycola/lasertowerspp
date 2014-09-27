//
//  Tower.h
//  LaserTowers
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 23.03.12.
//  Copyright 2012 Eduard Feicho. All rights reserved.
//



#ifndef __TOWER_H
#define __TOWER_H



#include "Sprite.h"
#include "Enemy.h"
#include <opencv2/core/core.hpp>

#include "CostValueModel.h"
#include "AttackController.h"

#include <vector>
using namespace std;


class Tower : virtual public Sprite, public CostValueModel, public AttackController
{
public:
	Tower()
	: _time_acc_anim(0)
	{
	}
	
	
	// Controller Logic
	virtual void move(float delta, cv::Vec3f direction = cv::Vec3f(1,0,0));
	virtual void animate(float delta);
	void attack(float delta, vector<Enemy*>* enemies);
	
	
	// InterfaceDrawable
	virtual void draw();
	
	
	// GameFigureModel
	virtual void attack_hit(float attack_power) {}
	
	
	
private:
	void attackNewEnemies(int guns_available, vector<Enemy*>* enemies);
	
	float _time_acc_anim;
};



#endif
