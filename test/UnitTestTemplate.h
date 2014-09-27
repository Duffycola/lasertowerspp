//
//  UnitTestTemplate.h
//  lasertowerspp
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 28.05.12.
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

#ifndef lasertowerspp_UnitTestTemplate_h
#define lasertowerspp_UnitTestTemplate_h

#include <iostream>
#include <string>
using namespace std;



/**
 * class UnitTestTemplate serves as a template for unit tests.
 * The template calls executeTest() and prints a message if execution did succeed or not.
 * To that end, a subclass of UnitTestTemplate implements bool executeTest() and returns true on success.
 *
 * <Template pattern>
 */
class UnitTestTemplate
{
public:
	
	// The constructor needs a unit test name to be displayed to the user
	UnitTestTemplate(string name)
	: _name(name) {
	}
	
	// unit test execution template
	void run() {
		_success = false;
		try {
			_success = executeTest();
		} catch (...) {
			_success = false;
		}
		print();
	}
	
protected:
	
	// the actual code of the test.
	// each test has to implement it's own code and return if it succeeded or not.
	// all exceptions are treated as execution failure.
	virtual bool executeTest() = 0;
	
private:
	
	// print a message if test succeeded or failed
	void print() {
		const string s = (_success) ? "succeeded." : "FAILED!"; 
		cout << " * Unit test " << _name << " " << s << endl;
	}
	
private:
	
	// variable to store if the unit test was successfull or not.
	// it needs to be private so that the test cannot alter it.
	// only by returning a bool in executeTest() the test can modify it indirectly.
	bool _success;
	
	// name of the test to be displayed as an identifier to the user
	string _name;
};

#endif
