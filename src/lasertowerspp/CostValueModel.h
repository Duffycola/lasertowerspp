//
//  CostValueModel.h
//  lasertowerspp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 26.05.12.
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

#ifndef lasertowerspp_CostValueModel_h
#define lasertowerspp_CostValueModel_h


/**
 * class CostValueModel is a model for monetary items in the game that have a cost and value.
 * For example a tower costs money to be built and has a reduced value when sold again.
 * The value of an enemy is added to the player's money stock when an enemy is defeated.
 */
class CostValueModel
{
public:
	CostValueModel(int cost = 0, int value = 0)
	: _cost(cost), _value(value)
	{	
	}
	
	int getCost() {
		return _cost;
	}
	int getValue() {
		return _value;
	}
	
	void setCost(int cost) {
		_cost = cost;
	}
	void setValue(int value) {
		_value = value;
	}
	
private:
	
	unsigned int _cost;
	unsigned int _value;
	
};

#endif
