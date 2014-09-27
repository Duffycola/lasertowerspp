//
//  LevelModel.cpp
//  lasertowerspp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 18.05.12.
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


#include "LevelModel.h"
#include "SpriteFactory.h"
#include <opengl/System.h>

#include "gl_util.h"


#include "SpriteFactory.h"


LevelModel::LevelModel()
: _field_size(40)
{
	spriteFactory = new SpriteFactory();
	
	// TODO load XML or something
	
	width = 10;
	height = 10;
	
	const char* levelmap = \
	"XX.IXXXXXX" \
	"XX.-.XXXXX" \
	"XX.-.....X" \
	"XX.-----.X" \
	"XX.....-.." \
	".......-.X" \
	".-------.X" \
	".-......XX" \
	"X----.XXXX" \
	"XXXXFXXXXX";
	
	
	paths = new cv::Vec3f*[width*height];
	for (int i=0; i<width*height; i++) {
		paths[i] = NULL;
	}
	
	paths[0 *width + 3] = new cv::Vec3f(0,1,0);
	paths[1 *width + 3] = new cv::Vec3f(0,1,0);
	paths[2 *width + 3] = new cv::Vec3f(0,1,0);
	
	paths[3 *width + 3] = new cv::Vec3f(1,0,0);
	paths[3 *width + 4] = new cv::Vec3f(1,0,0);
	paths[3 *width + 5] = new cv::Vec3f(1,0,0);
	paths[3 *width + 6] = new cv::Vec3f(1,0,0);
	
	paths[3 *width + 7] = new cv::Vec3f(0,1,0);
	paths[4 *width + 7] = new cv::Vec3f(0,1,0);
	paths[5 *width + 7] = new cv::Vec3f(0,1,0);
	
	paths[6 *width + 7] = new cv::Vec3f(-1,0,0);
	paths[6 *width + 6] = new cv::Vec3f(-1,0,0);
	paths[6 *width + 5] = new cv::Vec3f(-1,0,0);
	paths[6 *width + 4] = new cv::Vec3f(-1,0,0);
	paths[6 *width + 3] = new cv::Vec3f(-1,0,0);
	paths[6 *width + 2] = new cv::Vec3f(-1,0,0);
	
	paths[6 *width + 1] = new cv::Vec3f(0,1,0);
	paths[7 *width + 1] = new cv::Vec3f(0,1,0);
	
	paths[8 *width + 1] = new cv::Vec3f(1,0,0);
	paths[8 *width + 2] = new cv::Vec3f(1,0,0);
	paths[8 *width + 3] = new cv::Vec3f(1,0,0);
	
	paths[8 *width + 4] = new cv::Vec3f(0,1,0);
	paths[9 *width + 4] = new cv::Vec3f(0,0,0);
	
	
	field_flags = new int[height*width];
	field_sprites = new Sprite*[height*width];
	
	Tower* tower;
	
	for (int y=0; y<height; y++) {
		for (int x=0; x<width; x++) {
			int flag = FLAG_EMPTY;
			field_sprites[y*width+x] = NULL;
			
			switch (levelmap[y*width+x]) {
				case 'I':
					flag |= FLAG_INITIAL;
					initial_position = cv::Vec3f(x, y, 0);
					break;
				case 'F':
					flag |= FLAG_FINAL;
					final_position = cv::Vec3f(x, y, 0);
					break;
				case 'X':
					flag |= FLAG_OCCUPIED;
					break;
				case 'T':
					tower = spriteFactory->createTower(1);
					towers.push_back( tower );
					tower->setPosition( cv::Vec3f(x, y, 0) );
					tower->setPathPosition( tower->getPosition() );
					field_sprites[y*width+x] = tower;
					flag |= FLAG_TOWER;
					
//					flag |= FLAG_OCCUPIED;
					break;
				case '-':
					flag |= FLAG_PATH;
					break;
				case '.':
				default:
					break;
			}
			
			field_flags[y*width+x] = flag;
		}
	}
}
