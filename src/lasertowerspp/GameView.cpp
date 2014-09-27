//
//  GameView.cpp
//  lasertowerspp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 24.05.12.
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

#include "GameView.h"
#include "Tower.h"
#include "Enemy.h"

#include "globals.h"
#include "util.h"
#include "gl_util.h"

#include "Input.h"

#include <iostream>
#include <iomanip>
using namespace std;


void GameView::clear()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
	glColorBlack;
	
	glPushMatrix();
	glScalef(10,10,10);
	glBegin(GL_QUADS);
	glVertex3f(-1, -1, 0);
	glVertex3f(+1, -1, 0);
	glVertex3f(+1, +1, 0);
	glVertex3f(-1, +1, 0);
	glEnd();
	glPopMatrix();

}



void GameView::draw()
{
	clear();
	
	const int field_size = _model->getLevel()->getFieldSize();
	
	_levelView->draw();
	
	
	glPushMatrix();
	glScalef(field_size, field_size, field_size);
	glTranslatef( -_model->getLevel()->getWidth()/2.0, -_model->getLevel()->getHeight()/2.0, 0 );
	
	// draw all towers
	vector<Tower*>* towers = _model->getLevel()->getTowers();
	for (vector<Tower*>::iterator it = towers->begin(); it != towers->end(); it++) {
		(*it)->draw();
	}
	// draw all enemies
	vector<Enemy*>* enemies = _model->getLevel()->getEnemies();
	for (vector<Enemy*>::iterator it = enemies->begin(); it != enemies->end(); it++) {
		(*it)->draw();
	}
	glPopMatrix();
	
	
	for (vector<InterfaceDrawable*>::iterator it = _views.begin(); it != _views.end(); it++) {
		(*it)->draw();
	}
	
	
	drawHUD();
	
	if (game_over) {
		drawEndTitle("GAME OVER");
	} else if (game_won) {
		drawEndTitle("GAME WON");
	}
	
	glutSwapBuffers();
}



void GameView::drawHUD()
{
	ostringstream oss;
	oss.setf(ios::fixed, ios::floatfield);
	oss.setf(ios::showpoint);
	
	oss.clear(); oss.str("");
	int round = (_model->getEnemyGenerator()->getCurrentRound() > -1) ? _model->getEnemyGenerator()->getCurrentRound()+1 : _model->getEnemyGenerator()->getNumRounds();
	oss << "Round " << round << "/" << _model->getEnemyGenerator()->getNumRounds();
	string str_round = oss.str();
	
	oss.clear(); oss.str("");
	float time_remaining = (_model->getEnemyGenerator()->isRoundFinished() && _model->getLevel()->getEnemies()->size() == 0) ? 0 : (_model->getEnemyGenerator()->getTimeRemaining()/1000.0);
	oss << "Time remaining: " << setprecision(2) << time_remaining << "s";
	string str_round_time = oss.str();
	
	oss.clear(); oss.str("");
	oss << "FPS:" << setprecision(2) << fps;
	string str_fps = oss.str();
	
	
	oss.clear(); oss.str("");
	oss << "Money   " << _model->getPlayer()->getMoney();
	string str_money = oss.str();
	
	oss.clear(); oss.str("");
	oss << "Stamina " << _model->getPlayer()->getStamina() << "/" << _model->getPlayer()->getStaminaMax();
	string str_stamina = oss.str();
	
	
	glColorGreen;
	setOrthographicProjection();
	
	glPushMatrix();
	glLoadIdentity();
	drawString( str_fps );
	glTranslatef( 0, 25, 0 ); drawString( str_round );
	glTranslatef( 0, 25, 0 ); drawString( str_round_time );
	glTranslatef( 0, 25, 0 ); drawString( str_money );
	glTranslatef( 0, 25, 0 ); drawString( str_stamina );
	
	glTranslatef( 0, 25, 0 );
	glColorRed;
	
	int i = 1;
	vector<Enemy*>* enemies = _model->getLevel()->getEnemies();
	for (vector<Enemy*>::iterator it = enemies->begin(); it != enemies->end(); it++) {
		Enemy* enemy = (*it);
		
		oss.clear(); oss.str("");
		oss << "Enemy " << i << " (" << enemy->getStamina()  << "/" << enemy->getStaminaMax() << ")";
		string str_stamina_enemy = oss.str();
		
		glTranslatef( 0, 25, 0 ); drawString( str_stamina_enemy );
		i++;
	}
	
	glPopMatrix();
	
	restorePerspectiveProjection();
	
	glColorBlack;
}



void GameView::drawEndTitle( string title )
{
	glColorBackup;
	setOrthographicProjection();
	
	
	glColorBlack;
	drawBoxFilled();
	
	glColorWhite;
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(Input::screen_width/2, -Input::screen_height/2, 0);
	glScalef(10, 10, 10);
	drawString( title );
	glPopMatrix();
	
	restorePerspectiveProjection();
	glColorReset;
}



