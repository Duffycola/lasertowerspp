//
//  Attack.h
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




#ifndef lasertowerspp_Attack_h
#define lasertowerspp_Attack_h


#include "GameFigureModel.h"


/**
 * class Attack is a class used to control an attack from one game figure to another.
 * The basic idea is that an attack is not carried out immediately, but with delay,
 * because a bullet neesd time to arrive at its target for example.
 */
class Attack
{
public:
	
	Attack()
	: _target(NULL), _ttl(-1), _ttl_total(-1), _speed(-1), _power(-1)
	{}
	
	Attack(GameFigureModel* target, float time, int speed, int power)
	: _target(target), _ttl(time), _ttl_total(time), _speed(speed), _power(power)
	{}
	
	// variables to delay the time of impact on the attack
	float _ttl;
	float _ttl_total;
	int   _speed;
	
	// the power of the attack that will impact on the target
	int   _power;
	
	// positions of the source and target of the attack, at the time of creation
	cv::Vec3f _pos_source;
	cv::Vec3f _pos_target;
	
	// the target figure thatis attacked
	GameFigureModel* _target;
};


#endif
