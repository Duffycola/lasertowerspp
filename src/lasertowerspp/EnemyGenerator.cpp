//
//  EnemyGenerator.cpp
//  lasertowerspp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 20.05.12.
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

#include <iostream>

#include "EnemyGenerator.h"

#include "util.h"

vector<Enemy*>* EnemyGenerator::generate(float delta)
{
	time_next = time_acc + delta;
	
	vector<Enemy*>* new_enemies = new vector<Enemy*>();
	
	switch (current_round) {
		case 0:
			if (intervalCheck(1000)) {
				new_enemies->push_back( factory->createEnemy(1) );
			} else if (intervalCheck(2000)) {
				new_enemies->push_back( factory->createEnemy(1) );
			} else if (intervalCheck(3000)) {
				new_enemies->push_back( factory->createEnemy(2) );
			} else if (intervalCheck(4000)) {
				new_enemies->push_back( factory->createEnemy(2) );
			} else if (time_acc > 4000) {
				round_finished = true;
			}
			break;
		case 1:
			if (intervalCheck(1000)) {
				new_enemies->push_back( factory->createEnemy(2) );
			} else if (intervalCheck(2000)) {
				new_enemies->push_back( factory->createEnemy(2) );
			} else if (intervalCheck(3000)) {
				new_enemies->push_back( factory->createEnemy(3) );
			} else if (intervalCheck(4000)) {
				new_enemies->push_back( factory->createEnemy(3) );
			} else if (time_acc > 4000) {
				round_finished = true;
			}
			break;
		case 2:
			if (intervalCheck(1000)) {
				new_enemies->push_back( factory->createEnemy(3) );
			} else if (intervalCheck(2000)) {
				new_enemies->push_back( factory->createEnemy(3) );
			} else if (intervalCheck(2400)) {
				new_enemies->push_back( factory->createEnemy(3) );
			} else if (intervalCheck(3000)) {
				new_enemies->push_back( factory->createEnemy(3) );
			} else if (intervalCheck(3200)) {
				new_enemies->push_back( factory->createEnemy(3) );
			} else if (intervalCheck(3400)) {
				new_enemies->push_back( factory->createEnemy(3) );
			} else if (intervalCheck(8000)) {
				new_enemies->push_back( factory->createEnemy(3) );
			} else if (intervalCheck(8100)) {
				new_enemies->push_back( factory->createEnemy(3) );
			} else if (time_acc > 8100) {
				round_finished = true;
			}
			break;
		default:
			break;
	}
	
	time_acc = time_next;
	
	return new_enemies;
}


void EnemyGenerator::continueRound(float delta)
{
	if (time_acc > time_round_duration) {
		nextRound();
	}
}


void EnemyGenerator::nextRound()
{
	if (current_round == -1) {
		return;
	}
	
	current_round++;
	round_finished = false;
	time_acc = 0;
	
	if (current_round >= num_rounds) {
		current_round = -1;
		round_finished = true;
	}
}
