//
//  LevelController.h
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

#ifndef lasertowerspp_LevelController_h
#define lasertowerspp_LevelController_h

#include "InterfaceDrawable.h"

#include "LevelView.h"


class LevelController
{
public:
	
	LevelController(LevelModel* model, LevelView* view)
	: _model(model), _view(view), height(model->getHeight()), width(model->getWidth()) {
	}
	
	
	// build a tower at field coordinates (x,y)
	void buildTower(int x, int y, Tower* tower) {
		if ( x < 0 || y >= height || x < 0 || x >= width ) {
			return;
		}
		
		_model->setSprite(x,y,tower);
		_model->setFieldFlag(x, y, _model->getFieldFlag(x, y) | FLAG_TOWER);
		tower->setPosition( cv::Vec3f(x,y,0) );
		
		_model->getTowers()->push_back(tower);
	}
	
	
	void addEnemies(vector<Enemy*>* new_enemies) {
		// add enemies to list of all alive enemies
		_model->addEnemies(new_enemies);
		
		// update position to initial position(s) and set alive
		for (vector<Enemy*>::iterator it = new_enemies->begin(); it != new_enemies->end(); it++) {
			(*it)->setPosition( _model->getInitialPosition() );
			(*it)->setPathPosition( _model->getInitialPosition() );
			(*it)->setAlive(true);
		}
	}
	
	
	
	void moveSpriteAlongPath(Sprite* sprite, float delta) {
		
		cv::Vec3f oldPosPath = sprite->getPathPosition();
		
		cv::Vec3f* path = _model->getPath(oldPosPath[0], oldPosPath[1]);
		if (path == NULL) {
			cout << "ERROR: cannot move sprite, no path available at (" << oldPosPath[0] << "," << oldPosPath[1] << ")" << endl;
			return;
		}
		sprite->move(delta, *path);
		
		cv::Vec3f newPos = sprite->getPosition();
		
		float dx = newPos[0]-oldPosPath[0];
		float dy = newPos[1]-oldPosPath[1];
		
		// make sure sprite does not exceed a field
		if (sqrtf(dx*dx+dy*dy) > 1.0) {
			cv::Vec3f newPosPath = oldPosPath + (*path);
			sprite->setPosition( newPosPath );
			sprite->setPathPosition( newPosPath );
		}
	}
	
	
	void removeDeadEnemies() {
		vector<Enemy*> alive_enemies;
		
		vector<Enemy*>* enemies = _model->getEnemies();
		for (vector<Enemy*>::iterator it = enemies->begin(); it != enemies->end(); it++) {
			Enemy* enemy = *it;
			
			if (Enemy::isDead(*it)) {
				LOG("Enemy " << (*it)->getID() << " is dead");
				
				// clear all attack references to the enemy or else
				// the attack is continued the game main loop on a deleted object
				vector<Tower*>* towers = _model->getTowers();
				for (vector<Tower*>::iterator it_t = towers->begin(); it_t != towers->end(); it_t++) {
					Tower* tower = *it_t;
					tower->removeAttack( enemy );
				}
				delete *it;
			} else {
				alive_enemies.push_back( *it );
			}
		}
		*enemies = alive_enemies;
	}
	
	
	void selectField(int x, int y) {
		LOG("select field " << x << "," << y << endl);
		
		if (x < 0 || y >= height || x < 0 || x >= width) {
			return;
		}
		
		Sprite* sprite = _model->getSprite(x, y);
		if (sprite == NULL) {
			return;
		}
		bool select = !sprite->isSelected();
		
		vector<Tower*>* towers = _model->getTowers();
		for (vector<Tower*>::iterator it = towers->begin(); it != towers->end(); it++) {
			(*it)->setSelected(false);
		}
		sprite->setSelected( select );
	}
	
	
	void setView(LevelView* view) {
		_view = view;
	}
	LevelView* getView() {
		return _view;
	}
	
	
private:
	
	LevelModel* _model;
	LevelView* _view;
	
	
	const int width;
	const int height;
};


#endif
