lasertowerspp
=============

A simple tower-defense game using C++ / OpenGL / GLUT

Depends on OpenGL and GLUT

==================
Build instructions
==================

On Mac, open and compile the XCode project.

Also on Mac and all other systems, use CMake:

$ mkdir build
$ cd build && cmake .. && make -j8
$ ./lasertowerspp

==================
# TODOs
==================

Software patterns (+ideas):
	* Model-View-Controller
	* Notifications (singleton + observer)
	* Enemy / Tower factory
	* Template method for basic game layout
	- Decorator to enhance tower functionality (+view)
	- Command pattern for executing special bombs (and cancel option?)

* Particle generator for nice effects
* Be able to interact with fields
        sell towers
        increase towers

* Upgrade system for more powerful towers
* Heads-Up display:
* * Toggle debugging info
* * Display ressources
* * Display Points (# enemies destroyed / # enemies total per game)
* Continuous paths using B-Splines
* Level Editor / find open source tool and file format
	create the board
	create paths (bsplines)
	configure enemies / enemygenerator
	configure towers available
