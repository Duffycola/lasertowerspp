lasertowerspp
==============

A simple tower-defense game using C++ / OpenGL / GLUT with a simple 2D projection camera (birds-eye view).

![Screenshot](https://github.com/Duffycola/lasertowerspp/blob/master/screenshot.png)


Dependencies
------------

* (CMake)
* OpenGL
* GLUT


Build instructions
------------------

CMake (all systems, example for OS X):

    brew install cmake

    mkdir build
    cd build && cmake .. && make -j8
    ./lasertowerspp


Alternatively, on Mac, open and compile the XCode project.




TODOs
-----

- [ ] Software patterns (+ideas):
  - [x] Model-View-Controller
  - [x] Notifications (singleton + observer)
  - [x] Enemy / Tower factory
  - [x] Template method for basic game layout
  - [ ] Decorator to enhance tower functionality (+view)
  - [ ] Command pattern for executing special bombs (and cancel option?)

- [ ] Particle generator for nice effects
- [ ] Be able to interact with fields
  - [ ] sell towers
  - [ ] upgrade towers

- [ ] Upgrade system for more powerful towers
- [ ] Heads-Up display:
  - [ ] Toggle debugging info
  - [x] Display ressources
  - [x] Display Points (# enemies destroyed / # enemies total per game)
  - [ ] Continuous paths using B-Splines
- [ ] Level Editor / find open source tool and file format
  - [ ] create the map
  - [ ] create paths (+bsplines)
  - [ ] configure enemies / enemygenerator
  - [ ] configure towers available
