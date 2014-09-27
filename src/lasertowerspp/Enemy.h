//
//  Enemy.h
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

#include "Sprite.h"

#ifndef __ENEMY_H
#define __ENEMY_H

#include <opencv2/core/core.hpp>
#include "CostValueModel.h"
#include "AttackController.h"

class Enemy : virtual public Sprite, public CostValueModel, public AttackController
{
	
public:
	Enemy() {
		_alive = true;
		setPosition( cv::Vec3f(0,0,-1) );
	}
	
	virtual void draw();
	virtual void move(float delta, cv::Vec3f direction = cv::Vec3f(1,0,0));
	virtual void animate(float delta);
	
	
	
	virtual void attack_hit(float strength) {
		setStamina( getStamina() - strength );
		if (getStamina() <= 0) {
			setAlive(false);
		}
	}
	
	
	bool isAlive() {
		return _alive;
	}
	
	void setAlive(bool alive) {
		if (alive) {
			_time_acc_path = 0;
		}
		_alive = alive;
	}
	
	static bool isDead(Enemy* &enemy) {
		return enemy->getStamina() <= 0;
	}
	
	static bool compare_path_distance(Enemy* i, Enemy* j) {
		return (i->_time_acc_path > j->_time_acc_path);
	}
	
	
private:
	bool _alive;
	
	int _time_acc_path;
};


#endif
