//
//  GameModel.h
//  lasertowerspp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 24.05.12.
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

#ifndef lasertowerspp_GameModel_h
#define lasertowerspp_GameModel_h


#include "Player.h"
#include "LevelModel.h"
#include "EnemyGenerator.h"


class GameModel
{
public:
	
	GameModel()
	: _player(NULL), _level(NULL), _enemy_generator(NULL) {
	}
	
	~GameModel() {
		if (_player != NULL) {
			delete _player;
		}
		if (_level != NULL) {
			delete _level;
		}
		if (_enemy_generator != NULL) {
			delete _enemy_generator;
		}
	}
	
	inline void setLevel(LevelModel* level) {
		_level = level;
	}
	
	inline void setPlayer(Player* player) {
		_player = player;
	}
	
	inline LevelModel* getLevel() {
		return _level;
	}
	
	inline Player* getPlayer() {
		return _player;
	}
	
	inline EnemyGenerator* getEnemyGenerator() {
		return _enemy_generator;
	}
	
	inline void setEnemyGenerator(EnemyGenerator* enemy_generator) {
		_enemy_generator = enemy_generator;
	}
	
private:
	
	Player* _player;
	LevelModel* _level;
	EnemyGenerator* _enemy_generator;
	
};



#endif
