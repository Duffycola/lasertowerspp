//
//  UnitTestGameWin.h
//  lasertowerspp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 28.05.12.
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

#ifndef lasertowerspp_UnitTestGameWin_h
#define lasertowerspp_UnitTestGameWin_h

#include "UnitTestTemplate.h"
#include "GameController.h"

#include "LevelModel.h"
#include "Enemy.h"

#include "SpriteFactory.h"



class UnitTestGameWin : public UnitTestTemplate
{
public:
	
	UnitTestGameWin()
	: UnitTestTemplate("UnitTestGameWin") {
	}
	
protected:
	
	virtual bool executeTest() {
		// Execute the game update loop thousand times with the default game,
		// except that more than enough towers have been built before,
		// which should result in game win.
				
		game_pause = false;
		game_over = false;
		game_won = false;
		
		// create game
		LevelModel* level = new LevelModel();
		GameController* game = new GameController(level);
		game->setTestmode();
		LevelController* levelController = new LevelController(level, NULL);
		
		// create more than enough powerful towers
		SpriteFactoryAbstract* spriteFactory = new SpriteFactory();
		levelController->buildTower( 3, 4, spriteFactory->createTower(3) );
		levelController->buildTower( 4, 4, spriteFactory->createTower(3) );
		levelController->buildTower( 5, 4, spriteFactory->createTower(3) );
		levelController->buildTower( 6, 4, spriteFactory->createTower(3) );
		levelController->buildTower( 3, 5, spriteFactory->createTower(3) );
		levelController->buildTower( 4, 5, spriteFactory->createTower(3) );
		levelController->buildTower( 5, 5, spriteFactory->createTower(3) );
		levelController->buildTower( 6, 5, spriteFactory->createTower(3) );
		
		// execute game
		float time_steps = 1000.0/60.0;
		float time_accumulator = time_steps * 10000;
		while (time_accumulator > 0) {
			game->update(time_steps);
			time_accumulator -= time_steps;
		}
		
		delete game;
		delete levelController;
		delete spriteFactory;
		
		return game_won;
	}
};

#endif
