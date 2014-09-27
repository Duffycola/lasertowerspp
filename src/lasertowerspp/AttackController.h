//
//  AttackController.h
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

#ifndef lasertowerspp_AttackController_h
#define lasertowerspp_AttackController_h


#include "Attack.h"


/**
 * class AttackController contains the logic of an attack.
 * Basically, a figure can have more than one guns,
 * thus, the attack controller checks if there is a free slot for an attack
 * and controlls all of these.
 */
class AttackController
{
public:
	AttackController(int num_attacks = 1)
	: _attacks(NULL) {
		setNumAttacks( num_attacks );
	}
	
	
	Attack* getAttacks() {
		return _attacks;
	}
	
	/**
	 * Count the number of active attacks.
	 * An attack can be active more than a single moment, because
	 * the particle (like a canon) needs to reach the target and the
	 * moment an attack is over is when the energy of the attack has
	 * reduced the stamina of the target figure.
	 */
	int countActiveAttacks() {
		int activeAttacks = 0;
		for (int i=0; i<_num_attacks; i++) {
			Attack* attack = &_attacks[i];
			
			if (attack->_target == NULL) {
				continue;
			}
			activeAttacks++;
		}
		return activeAttacks;
	}
	
	
	void continueActiveAttacks(float delta)
	{
		for (int i=0; i<_num_attacks; i++) {
			Attack* attack = &_attacks[i];
			if (attack->_target == NULL) {
				continue;
			}
			
			attack->_ttl -= delta;
			if (attack->_ttl < 0) {
				attack->_target->attack_hit( attack->_power );
				attack->_target = NULL;
				attack->_ttl = -1;
			}
		}
	}
	
	
	Attack* createAttack(GameFigureModel* source, GameFigureModel* target, float target_distance)
	{
		for (int i=0; i<_num_attacks; i++) {
			Attack* attack = &_attacks[i];
			
			if (attack->_target != NULL) {
				continue;
			}
			
			attack->_target = NULL;
			// TODO calcualte correctly and find a good value for the fixed constant that
			// reflects the time the attack particle needs to arrive at the enemy
			attack->_ttl_total = 1000.0;// * dist_enemy * 1.0 / speed;
			attack->_ttl = attack->_ttl_total;
			attack->_speed = source->getSpeed();
			attack->_power = _attack_power;
			attack->_target = target;
			
			attack->_pos_source = cv::Vec3f(0,0,0);
			attack->_pos_target = target->getPosition() - source->getPosition();
			
			return attack;
		}
		
		return NULL;
	}
	
	
	
	void removeAttack( GameFigureModel* target )
	{
		for (int i=0; i<_num_attacks; i++) {
			Attack* state = &_attacks[i];
			
			if (state->_target == target) {
				state->_target = NULL;
			}
		}
	}
	
	
	
	unsigned int getAttackPower() {
		return _attack_power;
	}
	
	void setAttackPower(int attack_power) {
		_attack_power = attack_power;
	}
	
	
	
	unsigned int getNumAttacks() {
		return _num_attacks;
	}
	
	void setNumAttacks(int num_attacks) {
		_num_attacks = num_attacks;
		if (_num_attacks == 0) {
			_attacks = NULL;
			return;
		}
		
		if (_attacks != NULL) {
			delete[] _attacks;
		}
		_attacks = new Attack[_num_attacks];
	}
	
	
	
private:
	
	unsigned int _attack_power;
	Attack* _attacks;
	
	unsigned int _num_attacks;
	
};


#endif
