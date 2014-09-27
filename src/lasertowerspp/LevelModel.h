//
//  LevelModel.h
//  lasertowerspp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 15.05.12.
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

#ifndef __LEVEL_H
#define __LEVEL_H


#include "globals.h"
#include <opencv2/core/core.hpp>
#include "InterfaceDrawable.h"
#include "SpriteFactoryAbstract.h"





#define IS_FLAG(flags, bit) (((flags) & (bit)) == (bit))

#define FLAG_EMPTY    0
#define FLAG_OCCUPIED 1
#define FLAG_TOWER    2
#define FLAG_ENEMY    4
#define FLAG_INITIAL  8
#define FLAG_FINAL    16
#define FLAG_PATH     32




class LevelModel
{
public:
	
	LevelModel();
	
	~LevelModel() {
		delete spriteFactory;
		delete[] field_flags;
		delete[] field_sprites;
		for (int i=0; i<width*height; i++) {
			if (paths[i] != NULL) {
				delete paths[i];
			}
		}
	}
	
	
	
	void addEnemies(vector<Enemy*>* new_enemies) {
		// add enemies to list of all alive enemies
		
		vector<Enemy*> tmp;
		tmp.resize(enemies.size()+new_enemies->size());
		merge(enemies.begin(), enemies.end(), new_enemies->begin(), new_enemies->end(), tmp.begin());
		enemies = tmp;
		
		// update position to initial position(s) and set alive
		for (vector<Enemy*>::iterator it = new_enemies->begin(); it != new_enemies->end(); it++) {
			(*it)->setPosition( initial_position );
			(*it)->setPathPosition( initial_position );
			(*it)->setAlive( true );
		}
		
		/* TODO alternative?
		 enemies.resize(enemies.size()+new_enemies.size());
		 copy(new_enemies.begin(), new_enemies.end(), enemies.end());
		 */
	}
	
	
	void loadXML(string filename) {
		// TODO tinyxml or alike
	}
	
	
	vector<Enemy*>* getEnemies() {
		return &enemies;
	}
	
	vector<Tower*>* getTowers() {
		return &towers;
	}
	
	int getHeight() {
		return height;
	}
	int getWidth() {
		return width;
	}
	
	
	cv::Vec3f& getInitialPosition() {
		return initial_position;
	}
	cv::Vec3f& getFinalPosition() {
		return final_position;
	}
	
	
	cv::Vec3f* getPath(int x, int y) {
		if (x < 0 || y >= height || x < 0 || x >= width) {
			return NULL;
		}
		return paths[y * width + x];
	}
	
	
	inline int getFieldSize() {
		return _field_size;
	}
	
	unsigned int getFieldFlag(int x, int y) {
		if (x < 0 || y >= height || x < 0 || x >= width) {
			return 0;
		}
		return field_flags[y*width+x];
	}
	void setFieldFlag(int x, int y, unsigned int flag) {
		if (x < 0 || y >= height || x < 0 || x >= width) {
			return;
		}
		field_flags[y*width+x] = flag;
	}
	
	Sprite* getSprite(int x, int y) {
		if (x < 0 || y >= height || x < 0 || x >= width) {
			return NULL;
		}
		return field_sprites[ y*width+x ];
	}
	void setSprite(int x, int y, Sprite* sprite) {
		if (x < 0 || y >= height || x < 0 || x >= width) {
			return;
		}
		field_sprites[ y*width+x ] = sprite;
	}
	
	bool isEmpty(int x, int y) {
		if (x < 0 || y >= height || x < 0 || x >= width) {
			return false;
		}
		return field_flags[ y*width+x ] == 0;
	}
	
	bool isTower(int x, int y) {
		if (x < 0 || y >= height || x < 0 || x >= width) {
			return false;
		}
		return IS_FLAG(field_flags[ y*width+x ], FLAG_TOWER);
	}
	
	bool isInitial(int x, int y) {
		if (x < 0 || y >= height || x < 0 || x >= width) {
			return false;
		}
		return IS_FLAG(field_flags[ y*width+x ], FLAG_INITIAL);
	}
	
	bool isFinal(int x, int y) {
		if (x < 0 || y >= height || x < 0 || x >= width) {
			return false;
		}
		return IS_FLAG(field_flags[ y*width+x ], FLAG_FINAL);
	}
	
private:
	
	vector<Enemy*> enemies;
	vector<Tower*> towers;
	
	int width;
	int height;
	
	int _field_size;
	int* field_flags;
	Sprite** field_sprites;
	
	cv::Vec3f initial_position;
	cv::Vec3f final_position;
	
	cv::Vec3f** paths;
	
	string xml;
	
	SpriteFactoryAbstract* spriteFactory;
};

#endif
