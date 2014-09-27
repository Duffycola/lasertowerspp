//
//  GameView.h
//  lasertowerspp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 23.05.12.
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

#ifndef lasertowerspp_GameView_h
#define lasertowerspp_GameView_h


#include "GameModel.h"
#include "InterfaceDrawable.h"


/**
 * class GameView provides the game view.
 * Here, the game drawing methods are seen.
 * 
 * <Model-View-Controller pattern>
 */
class GameView : public InterfaceDrawable
{
public:
	
	/* InterfaceDrawable */
	virtual void draw();
	
public:
	
	// The game view gets its data mainly from the model.
	GameView(GameModel* model, InterfaceDrawable* levelView)
	: _model(model), _levelView(levelView) {
		// nothing to be done here
	}
	
	void addSubview(InterfaceDrawable* view) {
		_views.push_back(view);
	}
	
	// reset the canvas
	void clear();
	
	// draw a heads-up display
	// draws information about the game state, such as player money, points, current round, etc.
	void drawHUD();
	
	// draw an end title when game is finished (like Game over or Game won)
	void drawEndTitle( string title );
	
	
private:
	GameModel* _model;
	InterfaceDrawable* _levelView;
	
	vector<InterfaceDrawable*> _views;
};

#endif
