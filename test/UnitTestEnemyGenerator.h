//
//  UnitTestEnemyGenerator.h
//  lasertowerspp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 05.06.12.
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

#ifndef lasertowerspp_UnitTestEnemyGenerator_h
#define lasertowerspp_UnitTestEnemyGenerator_h

#include "UnitTestTemplate.h"

#include "GameController.h"
#include "LevelModel.h"
#include "Enemy.h"



class UnitTestEnemyGenerator : public UnitTestTemplate
{
public:
	
	UnitTestEnemyGenerator()
	: UnitTestTemplate("UnitTestEnemyGenerator") {
	}
	
protected:
	
	virtual bool executeTest() {
		
		// Generate enemies and check if the correct ones were generated using only ID
		
		LevelModel* level = new LevelModel();
		GameController* game = new GameController(level);
		game->setTestmode();
		LevelController* levelController = new LevelController(level, NULL);
		
		// execute generator
		float time_steps = 1000.0/60.0;
		float time_accumulator = time_steps * 10000;
		while (time_accumulator > 0) {
			
			// generate and add enemies
			vector<Enemy*> *new_enemies = game->getModel()->getEnemyGenerator()->generate( time_steps );
			game->getModel()->getLevel()->addEnemies( new_enemies );
			delete new_enemies;
			
			game->getModel()->getEnemyGenerator()->continueRound( time_steps );
			
			time_accumulator -= time_steps;
		}
		
		// compare IDs of generated enemies with expected IDs
		int expected_enemies[] = {
			ENEMYID_LASER,  ENEMYID_LASER,  ENEMYID_LASER2, ENEMYID_LASER2,
			ENEMYID_LASER2, ENEMYID_LASER2, ENEMYID_LASER3, ENEMYID_LASER3,
			ENEMYID_LASER3, ENEMYID_LASER3, ENEMYID_LASER3, ENEMYID_LASER3, ENEMYID_LASER3, ENEMYID_LASER3, ENEMYID_LASER3, ENEMYID_LASER3
		};
		
		int i=0;
		bool success = true;
		for (vector<Enemy*>::iterator it = game->getModel()->getLevel()->getEnemies()->begin(); it != game->getModel()->getLevel()->getEnemies()->end(); it++) {
			success = success && (expected_enemies[i++] == (*it)->getID());
		}
		
		delete game;
		delete levelController;
		
		return success;
	}
};

#endif
