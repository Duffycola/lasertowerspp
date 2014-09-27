//
//  GameControllerTemplate.cpp
//  lasertowerspp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 30.05.12.
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

#include "GameControllerTemplate.h"
#include "Input.h"




GameControllerTemplate::GameControllerTemplate()
{
	time_current = 0;
	time_lastframe = 0;
	time_last_fps = 1.0;
	frames = 0;
	min_time = 1000.0f/60.0f;     // aiming for 60 frames per second (1000ms) 
	time_step = 1000.0f/60.0f;
	accumulator = 0;
	fps = 0;
}




void GameControllerTemplate::initGame()
{
	time_lastframe = glutGet(GLUT_ELAPSED_TIME);
	time_last_fps = time_lastframe;
}



void GameControllerTemplate::mainLoop()
{
	time_current = glutGet(GLUT_ELAPSED_TIME);
	
	int time_deltaframe = time_current - time_lastframe;
	Input::keyOperations(time_deltaframe);
	
	// idle until a minimum time interval is reached (frame duration)
	if (time_deltaframe < min_time) {
		return;
	}
	time_lastframe = time_current;
	
	// count number of frames per second
	frames++;
	if (time_current-time_last_fps > 1000.0) {
		fps = frames * 1000.0 / (time_current-time_last_fps);
		time_last_fps = time_current;
		frames = 0.0;
	}
	
	// use an accumulator that accumulates the time passed since last update.
	// the number of how many times the time_step fits into the accumulator
	// represents the number of updates that need to be made with fixed time_step.
	accumulator += time_deltaframe * game_speed_factor;
	
	// render using fixed time delta
	while (accumulator >= time_step) {
		update(time_step);
		animate(time_step);
		paint();
		accumulator -= time_step;
	}
}
