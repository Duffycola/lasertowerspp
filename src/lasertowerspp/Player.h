//
//  Player.h
//  lasertowerspp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 21.05.12.
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

#ifndef lasertowerspp_Player_h
#define lasertowerspp_Player_h

#include <iostream>
using namespace std;

#include "util.h"

class Player {
public:
	
	Player()
	: _money(100), _stamina(100), _stamina_max(100)
	{
	}
	
	unsigned int getMoney() {
		return _money;
	}
	
	int getStamina() {
		return _stamina;
	}
	
	int getStaminaMax() {
		return _stamina_max;
	}
	
	void addMoney(unsigned int money) {
		_money += money;
	}
	
	void removeMoney(unsigned int money) {
		_money -= money;
	}
	
	void setMoney(unsigned int money) {
		_money = money;
	}
	
	void setStamina(int stamina) {
		_stamina = stamina;
	}
	
	void setStaminaMax(int stamina_max) {
		_stamina_max = stamina_max;
	}
	
	void removeStamina(unsigned int stamina) {
		_stamina -= stamina;
		LOG("Remove " << stamina << " stamina ... stamina left: " << _stamina << endl);
	}
	
private:
	unsigned int _money;
	int _stamina;
	int _stamina_max;
};



#endif
