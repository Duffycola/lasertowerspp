//
//  GameFigureModel.h
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

#ifndef lasertowerspp_GameFigureModel_h
#define lasertowerspp_GameFigureModel_h


class GameFigureModel
{
public:
	
	virtual void attack_hit(float attack_power) = 0;
	
	GameFigureModel()
	: _speed(0),
	_radius(0),
	_stamina(-1),
	_stamina_max(-1)
	{
	}
	
	
	unsigned int getID() {
		return _id;
	}
	void setID(unsigned int ID) {
		_id = ID;
	}
	
	
	float getStamina() {
		return _stamina;
	}
	void setStamina(float stamina) {
		_stamina = stamina;
	}
	
	
	float getStaminaMax() {
		return _stamina;
	}
	void setStaminaMax(float stamina_max) {
		_stamina_max = stamina_max;
	}
	
	
	unsigned int getRadius() {
		return _radius;
	}
	void setRadius(int radius) {
		_radius = radius;
	}
	
	
	unsigned int getSpeed() {
		return _speed;
	}
	void setSpeed(int speed) {
		_speed = speed;
	}
	
	
	cv::Vec3f& getPosition() {
		return _position;
	}
	void setPosition(cv::Vec3f position) {
		_position = position;
	}
	
	
	cv::Vec3f& getPathPosition() {
		return _position_path;
	}
	void setPathPosition(cv::Vec3f& position) {
		_position_path = position;
	}
	
private:
	
	unsigned int _id;
	
	cv::Vec3f _position;
	cv::Vec3f _position_path;
	
	unsigned int _speed;
	unsigned int _radius;
	
	float _stamina_max;
	float _stamina;
};

#endif
