//
//  Texture2D.cpp
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

#include "Texture2D.h"



Texture2D::Texture2D(string texture_file)
: _filename(texture_file)
{
	static const GLfloat squareVertices[] = {
		-1, -1,
		+1, -1,
		-1, +1,
		+1, +1,
	};
	
	static const GLfloat squareTexCoords[] = {
		0, 1,
		1, 1,
		0, 0,
		1, 0,
	};
	
	static const GLubyte squareColors[] = {
		0,   0, 255, 255,
		0,   0, 255, 255,
		0,   0, 255, 255,
		0,   0, 255, 255,
	};
	
	static const unsigned short squareTriangleIndices[] = {
		0, 2, 1,
		2, 3, 1,
	};
	
	_num_vertices = 4;
	_vertices  = new GLfloat[_num_vertices*2];
	_texCoords = new GLfloat[_num_vertices*2];
	_colors    = new GLubyte[_num_vertices*4];
	_indices   = new unsigned short[2*3];
	
	memcpy( _vertices, squareVertices, sizeof(GLfloat)*_num_vertices*2 );
	memcpy( _texCoords, squareTexCoords, sizeof(GLfloat)*_num_vertices*2 );
	memcpy( _colors, squareColors, sizeof(GLubyte)*_num_vertices*4 );
	memcpy( _indices, squareTriangleIndices, sizeof(unsigned short)*2*3 );
}




void Texture2D::draw()
{
#if USE_OPENGL1
	glDisable(GL_LIGHTING);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	
	// texture transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif
	
	glVertexPointer(2, GL_FLOAT, 0, _vertices);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, _colors);
	
#if USE_OPENGL1
	// Render using the appropriate version of OpenGL
	
	//	glScalef(kObjectScale, kObjectScale, kObjectScale);
	
	// Draw object
	glTranslatef(_position[0], _position[1], 0.0);
	//glRotatef(-obj3D.rotation, 0, 0, 1);
	//glScalef(obj3D.scale, obj3D.scale, 1.0);
	
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glVertexPointer(2, GL_FLOAT, 0, (const GLvoid*)vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, (const GLvoid*)texCoords);
	//	glNormalPointer(GL_FLOAT, 0, (const GLvoid*)obj3D.normals);
	glDrawElements(GL_TRIANGLES, obj3D.numIndices, GL_UNSIGNED_SHORT, (const GLvoid*)obj3D.indices);
	
#else
	
	
	// OpenGL 2
	
	glUseProgram(_shaderProgramID);
	glVertexAttribPointer(_vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)_vertices);
//	glVertexAttribPointer(_normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)_normals);
	glVertexAttribPointer(_textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)_indices);
	glEnableVertexAttribArray(_vertexHandle);
//	glEnableVertexAttribArray(_normalHandle);
	glEnableVertexAttribArray(_textureCoordHandle);
	
	/*
	 TODO
	 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	 
	 // TODO
	 glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (const GLfloat*)&modelViewProjection.data[0]);
	 
	 glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (const GLvoid*)squareIndices);
	 */
#endif
	
	
	
	glDisable(GL_BLEND);
	
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    
#if USE_OPENGL1
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#else
	glDisableVertexAttribArray( _vertexHandle );
	glDisableVertexAttribArray( _normalHandle );
	glDisableVertexAttribArray( _textureCoordHandle );
#endif
}

