//
//  GameTemplate.h
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

#ifndef lasertowerspp_GameTemplate_h
#define lasertowerspp_GameTemplate_h

#include <opengl/System.h>
#include "util.h"

/**
 * class GameControllerTemplate provides a template for a basic game layout.
 * This includes a game main loop that can be used as an idle function.
 * Timing variables control the framerate. The update() function is called with
 * fixed timesteps for each frame.
 * 
 * Fixed timesteps have benefits in collision detection, because the fixed update
 * gives an upper bound on the move in an update step. This way, one can assume
 * (or asure) that collisions don't recurse.
 * 
 * <Template Pattern>
 *
 */
class GameControllerTemplate
{
public:
	
	GameControllerTemplate();
	
	// initialize the game
	virtual void initGame();
	
	// basic main loop for a game, using fixed timesteps
	void mainLoop();
	
	// The following functions are called from within the main loop.
	// These have to be implemented by an actual game.
	
	// update game model, for example move figures
	virtual void update(float delta) = 0;
	// update animation model, for example update sprite textures
	virtual void animate(float delta) = 0;
	// paint/render the scene
	virtual void paint() = 0;
	
	
private:
	
	// current timestamp
	int time_current;
	
	// timestamp of last frame
	int time_lastframe;
	
	// timestamp when fps was rendered last time
	int time_last_fps;
	
	// counter for frames per second
	int frames;
	
	// minimum frame duration
	int min_time;
	
	// fixed time steps used for fixed delta update
	float time_step;
	
	// accumulator vriable used to count fixed timesteps
	float accumulator;
};

#endif
