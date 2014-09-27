//
//  EnemyGenerator.h
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

#ifndef lasertowerspp_EnemyGenerator_h
#define lasertowerspp_EnemyGenerator_h

#include <vector>
using namespace std;

#include "Enemy.h"
#include "SpriteFactory.h"


/**
 * Generates waves of enemies
 */
class EnemyGenerator
{
public:
	EnemyGenerator()
	: current_round(0), num_rounds(3), time_round_duration(10000) {
		factory = new SpriteFactory();
	}
	
	~EnemyGenerator() {
		delete factory;
	}
	
	// increase round counter or finish after last round
	void nextRound();
	
	// generate enemies, given time delta
	virtual vector<Enemy*>* generate(float delta);

	// continue round timer, given time delta
	virtual void continueRound(float delta);
	
	
	
	/*
	 * Getters and Setters
	 */
	
	int getCurrentRound() {
		return current_round;
	}
	int getNumRounds() {
		return num_rounds;
	}
	float getTimeRemaining() {
		return time_round_duration - time_acc;
	}
	bool isRoundFinished() {
		return round_finished;
	}
	
private:
	
	inline bool intervalCheck(float t) {
		return (time_acc <= t && t <= time_next);
	}
	
	
	// accumulator of time
	float time_acc;
	float time_next;
	
	bool round_finished;
	int num_rounds;
	int current_round;
	
	int time_round_duration;
	int time_pause;
	
	SpriteFactoryAbstract* factory;
};

#endif
