//
//  Texture2D.h
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

#ifndef lasertowerspp_Texture2D_h
#define lasertowerspp_Texture2D_h

#include <opengl/System.h>
#include <string>
using namespace std;


#include "InterfaceDrawable.h"


/**
 * Texture2D renders a 2D image texture on a unit rectangle.
 */
class Texture2D : public InterfaceDrawable
{
public:
	
	Texture2D(string texture_file = "");
	virtual void draw();
	
private:
	string _filename;
	int _num_vertices;
	
	GLfloat *_vertices;
	GLfloat *_texCoords;
	GLubyte *_colors;
	unsigned short *_indices;
	
	GLuint _shaderProgramID;
    GLint  _vertexHandle;
    GLint  _normalHandle;
    GLint  _textureCoordHandle;
};

#endif


