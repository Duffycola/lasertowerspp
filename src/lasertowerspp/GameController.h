//
//  MotionManager.h
//  lasertowerspp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 15.05.12.
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

#ifndef __GAMECONTROLLER_H
#define __GAMECONTROLLER_H



#include <vector>
using namespace std;


#include "NotificationCenter.h"


#include "Player.h"
#include "LevelModel.h"
#include "Enemy.h"
#include "Tower.h"
#include "EnemyGenerator.h"

#include "gl_util.h"
#include "globals.h"
#include "util.h"

#include "Input.h"

#include "GameControllerTemplate.h"
#include "GameModel.h"
#include "GameView.h"

#include "LevelController.h"


#include "LevelController.h"
#include "LevelModel.h"
#include "LevelView.h"


/**
 * class GameController implements the GameControllerTemplate, thus controlls the game actions.
 * These include updating positions and drawing, all relative to the update delta.
 *
 * <Model-View-Controller pattern>
 */
class GameController : public GameControllerTemplate, public NotificationObserver
{
	// NotificationObserver
public:
	virtual void notify(Notification notification);
	
public:
	
	GameController();
	GameController(LevelModel* level);
	~GameController();
	
	// GameControllerTemplate
	virtual void initGame();
	
	// update game model, for example move figures
	virtual void update(float delta);
	// update animation model, for example update sprite textures
	virtual void animate(float delta);
	// paint/render the scene
	virtual void paint();
	
	
	GameModel* getModel() {
		return _model;
	};
	
private:
	
	void updateMoveFigures(float delta);
	void updateGenerator(float delta);
	void updateTowers(float delta);
	void updateEnemiesDead(float delta);
	void updateEnemiesFinished(float delta);
	void updateCheckGameWon();
	
private:
	// model-view-controller principle: view
	GameView* _view;
	
	// model-view-controller principle: model
	GameModel* _model;
	
	// reference to level controller
	LevelController* _levelController;
	
	
	
	// for testing purposes (unit tests) no view is set up
public:
	void setTestmode() {
		if (_view != NULL) {
			delete _view;
		}
		_view = NULL;
	}
};


#endif
