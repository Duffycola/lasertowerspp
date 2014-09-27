//
//  LevelView.h
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

#ifndef lasertowerspp_LevelView_h
#define lasertowerspp_LevelView_h



#include "LevelModel.h"



class LevelView : public InterfaceDrawable
{
public:
	// InterfaceDrawable
	virtual void draw();
	
	
public:
	LevelView(LevelModel* model)
	: _model(model) {
		_height = _model->getHeight();
		_width = _model->getWidth();
	}
	
	
	cv::Vec3f field2vector(int x, int y) {
		const int field_size = _model->getFieldSize();
		return cv::Vec3f( (- _width  /2.0 + x) * field_size,
						 (  _height /2.0 -1 -y) * field_size,
						 0
		);
	}
	
	cv::Vec3f vector2field(cv::Vec3f v) {
		const int field_size = _model->getFieldSize();
		
		return cv::Vec3f( v[0]/field_size + _width /2.0,
						(v[1]/field_size - _height /2.0 +1)*(-1),
						0
		);
	}
	
private:
	LevelModel* _model;
	
	int _height;
	int _width;
};

#endif
