//
//  GameController.cpp
//  lasertowerspp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 18.05.12.
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

#include "GameController.h"



GameController::GameController() {
	LevelModel* level = new LevelModel();
	LevelView* levelView = new LevelView(level);
	_levelController = new LevelController( level, levelView );
	
	_model = new GameModel();
	_model->setLevel( level );
	_model->setPlayer( new Player() );
	_model->setEnemyGenerator( new EnemyGenerator() );
	
	_view = new GameView(_model, levelView);
	
	NotificationCenter::defaultCenter()->addObserver(MOUSE_CLICK_NOTIFICATION, this);
}



GameController::GameController(LevelModel* level) {
	LevelView* levelView = new LevelView(level);
	_levelController = new LevelController( level, levelView );
	
	_model = new GameModel();
	_model->setLevel( level );
	_model->setPlayer( new Player() );
	_model->setEnemyGenerator( new EnemyGenerator() );
	
	_view = new GameView(_model, levelView);
	
	NotificationCenter::defaultCenter()->addObserver(MOUSE_CLICK_NOTIFICATION, this);
}



GameController::~GameController()
{
	NotificationCenter::defaultCenter()->removeObserver(MOUSE_CLICK_NOTIFICATION, this);
	
	delete _model;
	
	if (_view != NULL) {
		delete _view;
	}
	
	delete _levelController;
}



void GameController::initGame(void)
{
	GameControllerTemplate::initGame();
	
	// 2D means no depth tests are necessary
	glDisable(GL_DEPTH_TEST);
	
	// clear screen with white color
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}



void GameController::update(float delta)
{
	// if the game is paused, no need for update
	if (game_pause || game_over || game_won) {
		return;
	}
	
	updateGenerator(delta);       // generate new enemies and continue rounds
	updateMoveFigures(delta);     // move figures
	updateTowers(delta);          // make towers attack enemies
	updateEnemiesDead(delta);     // count dead enemies and add their monetary value
	updateEnemiesFinished(delta); // remove health of player for enemies at the exit
	updateCheckGameWon();         // check if game is won
}



// move figures along their paths
void GameController::updateMoveFigures(float delta)
{
	vector<Enemy*>* enemies = _model->getLevel()->getEnemies();
	
	// move all enemies along their path
	for (vector<Enemy*>::iterator it = enemies->begin(); it != enemies->end(); it++) {
		Enemy* enemy = *it;
		if (!enemy->isAlive()) {
			continue;
		}
		_levelController->moveSpriteAlongPath( enemy, delta );
	}
}



// generate new enemies and continue rounds
void GameController::updateGenerator(float delta)
{
	if (_model->getLevel()->getEnemies()->size() == 0 && _model->getEnemyGenerator()->isRoundFinished()) {
		_model->getEnemyGenerator()->nextRound();
	} else {
		vector<Enemy*> *new_enemies = _model->getEnemyGenerator()->generate( delta );
		_model->getLevel()->addEnemies( new_enemies );
		delete new_enemies;
		
		_model->getEnemyGenerator()->continueRound( delta );
	}
}



// update towers, make towers attack enemies
void GameController::updateTowers(float delta)
{
	vector<Enemy*>* enemies = _model->getLevel()->getEnemies();
	vector<Tower*>* towers = _model->getLevel()->getTowers();
	
	// Sort enemies such that the first one is the one most near to the exit
	// (most dangerous will be attacked first)
	sort(enemies->begin(), enemies->end(), Enemy::compare_path_distance);
	
	for (vector<Tower*>::iterator it = towers->begin(); it != towers->end(); it++) {
		Tower* tower = *it;
		tower->attack(delta, enemies);
	}
}

void GameController::updateEnemiesDead(float delta)
{
	vector<Enemy*>* enemies = _model->getLevel()->getEnemies();
	for (vector<Enemy*>::iterator it = enemies->begin(); it != enemies->end(); it++) {
		Enemy* enemy = *it;
		if (Enemy::isDead(enemy)) {
			_model->getPlayer()->addMoney( enemy->getValue() );
		}
	}
	// remove dead enemies
	_levelController->removeDeadEnemies();
}

void GameController::updateEnemiesFinished(float delta)
{
	vector<Enemy*>* enemies = _model->getLevel()->getEnemies();
	for (vector<Enemy*>::iterator it = enemies->begin(); it != enemies->end(); it++) {
		Enemy* enemy = *it;
		if (enemy->getPosition() == _model->getLevel()->getFinalPosition()) {
			_model->getPlayer()->removeStamina( enemy->getAttackPower() );
			enemy->setAlive(false);
			enemy->setStamina(0);
			
			// game is lost if player does not have health left
			if (_model->getPlayer()->getStamina() <= 0) {
				LOG("GAME OVER");
				game_over = true;
			}
		}
	}
	// remove enemies that reached the finish line which are now marked as dead
	_levelController->removeDeadEnemies();
}


void GameController::updateCheckGameWon()
{
	// game won if all last round is over, all enemies are dead and the player still has health
	if ( _model->getLevel()->getEnemies()->size() == 0
		&& _model->getEnemyGenerator()->isRoundFinished()
		&& _model->getEnemyGenerator()->getCurrentRound() == -1
		&& !game_over )
	{
		LOG("GAME WON");
		game_won = true;
	}
}


void GameController::animate(float delta)
{
	if (_view == NULL) {
		return;
	}
		
	// animate all enemies
	vector<Enemy*>* enemies = _model->getLevel()->getEnemies();
	for (vector<Enemy*>::iterator it = enemies->begin(); it != enemies->end(); it++) {
		Enemy* enemy = *it;
		enemy->animate(delta);
	}
	
	// animate all towers
	vector<Tower*>* towers = _model->getLevel()->getTowers();
	for (vector<Tower*>::iterator it = towers->begin(); it != towers->end(); it++) {
		Tower* tower = *it;
		tower->animate(delta);
	}
}


void GameController::paint()
{
	if (_view == NULL) {
		return;
	}
	
	// draw the view
	_view->draw();
}









void GameController::notify(Notification notification)
{
	if (notification.getObject() == NULL) {
		return;
	}
	
	// Mouse click event
	if (notification.getID() == MOUSE_CLICK_NOTIFICATION) {
		// A 2D vector of (x,y) coordinate is expected where the click happened
		cv::Vec3f* v = (cv::Vec3f*)notification.getObject();
		
		// Translate window coordinates to level field coordinats
		int x;
		int y;
		
		const int field_size = _model->getLevel()->getFieldSize();
		cv::Vec3f coord_relative_to_board = cv::Vec3f(
													(*v)[0] + _model->getLevel()->getWidth()  / 2*field_size,
													(*v)[1] + _model->getLevel()->getHeight() / 2*field_size,
													0
		);
		
		x = coord_relative_to_board[0] / field_size;
		y = coord_relative_to_board[1] / field_size;
		y = _model->getLevel()->getHeight()-y-1;
		
		if (_model->getLevel()->isEmpty(x,y)) {
			SpriteFactoryAbstract* factory = new SpriteFactory();
			
			Tower* tower = factory->createTower(1);
			if (_model->getPlayer()->getMoney() >= tower->getCost()) {
				_model->getPlayer()->removeMoney( tower->getCost() );
				_levelController->buildTower(x,y,tower);
			} else {
				delete tower;
			}
			delete factory;
		}
		
		_levelController->selectField(x,y);
	}
}

