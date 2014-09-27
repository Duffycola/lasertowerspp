//
//  Tower.m
//  LaserTowers
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 23.03.12.
//  Copyright 2012 Eduard Feicho. All rights reserved.
//

#include "Tower.h"

#include <opengl/System.h>


#include <math.h>


#include "globals.h"
#include "gl_util.h"


void Tower::draw()
{
	int alpha = ((int) (_time_acc_anim/10.0)) % 360;
	int arcdeg = 90;
	
	
	glPushMatrix();
	glColorBackup;
	
	cv::Vec3f& pos = getPosition();
	glTranslatef( pos[0]+0.5, pos[1]+0.5, pos[2] );
	
	// draw an animated circle to indicate the tower
	glColorGreen;
	drawArc( 0.4, alpha, arcdeg );
	glColorBlue;
	drawArc( 0.4, alpha+arcdeg, 360-arcdeg );
	
	// draw a dashed circle to indicate the tower's attack radius
	if (_selected) {
		glColorBlue;
		drawDashedCircle( getRadius(), 20, alpha/1.5 );
	}
	
	for (int i=0; i<getNumAttacks(); i++) {
		Attack* state = &getAttacks()[i];
		if (state->_target == NULL) {
			continue;
		}
		if (state->_ttl / state->_ttl_total > 0.5) {
			glBegin(GL_LINES);
			glVertex2f( 0, 0 );
			glVertex2f( state->_pos_target[0], state->_pos_target[1] );
			glEnd();
		}
	}
	
	glColorReset;
	glPopMatrix();
}



void Tower::move(float delta, cv::Vec3f direction)
{
#if VERBOSE
	cout << "Tower move" << endl;
#endif
}



void Tower::animate(float delta)
{
	_time_acc_anim += delta;
}



void Tower::attack(float delta, vector<Enemy*>* enemies)
{
	// Continue active attacks
	continueActiveAttacks(delta);
	
	int guns_available = getNumAttacks() - countActiveAttacks();
	if (guns_available <= 0) {
		return;
	}
	
	// Attack new enemies with remaining guns
	attackNewEnemies(guns_available, enemies);
}



void Tower::attackNewEnemies(int guns_available, vector<Enemy*>* enemies)
{
	// Attack new enemies
	// TODO: maybe only attack enemies that are not already being attacked?
	for (vector<Enemy*>::iterator it = enemies->begin(); it != enemies->end(); it++) {
		Enemy* enemy = *it;
		cv::Vec3f pos_enemy = enemy->getPosition();
		
		float distx = pos_enemy[0] - getPosition()[0];
		float disty = pos_enemy[1] - getPosition()[1];
		float dist_enemy = sqrtf( distx*distx + disty*disty );
		
		if (dist_enemy <= getRadius()) {
			createAttack(this, enemy, dist_enemy);
			if (--guns_available == 0) {
				return;
			}
		}
	}
}


