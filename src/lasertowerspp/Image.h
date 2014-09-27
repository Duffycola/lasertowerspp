//
//  Image.h
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

#ifndef lasertowerspp_Image_h
#define lasertowerspp_Image_h


#include <cv.h>
#include <highgui.h>
using namespace cv;




class Image {

public:
	Image()
	: w(0), h(0)
	{
		
	}
	
	Image(const string& filename)
	: w(0), h(0)
	{
		loadFile(filename);
	}
	
	
	void loadFile(const string& filename) {
		// read image using OpenCV
		image = imread(filename);
		if (image.data == NULL) {
			cerr << "Could not load image " << filename << endl;
			throw exception();
			return;
		}
		
		w = image.cols;
		h = image.rows;
		n = w*h;
	}
	
	
	int getGLType() {
		// TODO
		switch (image.type()) {
			case CV_8U:
				// TODO
				return GL_RGB;
				break;
			case CV_32FC3:
				return GL_RGB;
			case CV_32FC4:
				return GL_RGBA;
			default:
				break;
		}
		return 0;
	}
	
	int getGLChannelSize() {
		switch (image.type()) {
			case CV_8U:
				return GL_UNSIGNED_BYTE;
				break;
			case CV_32FC3:
				return GL_UNSIGNED_INT;
				break;
			default:
				break;
		}
	}
	int getWidth() {
		return w;
	}
	
	int getHeight() {
		return h;
	}
	
	int getNumPixel() {
		return n;
	}
	
	uchar* getData() {
		return image.data;
	}
	
private:
	Mat image;
	int w;
	int h;
	int n;
};

#endif
