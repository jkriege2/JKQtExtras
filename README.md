# JKQtExtras - A Library of Useful Qt Widgets and Tools

This software is licensed under the term of the [GNU Lesser General Public License 2.1 
(LGPL 2.1)](./LICENSE) or above. 

[![License](https://img.shields.io/github/license/jkriege2/JKQtExtras)](https://github.com/jkriege2/JKQtExtras/blob/master/LICENSE)
![Language](https://img.shields.io/github/languages/top/jkriege2/JKQtExtras)
[![Qt 4&5](https://img.shields.io/badge/Qt-4%20%26%205-brightgreen)](https://doc.qt.io/qt-5/)
[![Documentation](https://img.shields.io/badge/documentation-online-blue)](http://jkriege2.github.io/JKQtExtras/index.html)

[![CI: Windows Build](https://img.shields.io/appveyor/ci/jkriege2/JKQtExtras/master?label=CI%20Windows%20Build)](https://ci.appveyor.com/project/jkriege2/jkqtextras/branch/master) 
[![CI: Documentation/Linux/MacOX Build](https://img.shields.io/travis/jkriege2/JKQtExtras/master?label=CI%3A%20Documentation%2FLinux%2FMacOX%20Build)](https://travis-ci.org/jkriege2/JKQtExtras)

[![Commit Activity](https://img.shields.io/github/commit-activity/m/jkriege2/JKQtExtras)](https://github.com/jkriege2/JKQtExtras/pulse)
[![Last Commit](https://img.shields.io/github/last-commit/jkriege2/JKQtExtras)](https://github.com/jkriege2/JKQtExtras/pulse)
[![Contributors](https://img.shields.io/github/contributors/jkriege2/JKQtExtras)](https://github.com/jkriege2/JKQtExtras/graphs/contributors)

[![Open Issues](https://img.shields.io/github/issues/jkriege2/JKQtExtras)](https://github.com/jkriege2/JKQtExtras/issues)
[![Closed Issues](https://img.shields.io/github/issues-closed/jkriege2/JKQtExtras)](https://github.com/jkriege2/JKQtExtras/issues?q=is%3Aissue+is%3Aclosed)

[![Open PRs](https://img.shields.io/github/issues-pr/jkriege2/JKQtExtras)](https://github.com/jkriege2/JKQtExtras/pulls)
[![Closed PRs](https://img.shields.io/github/issues-pr-closed/jkriege2/JKQtExtras)](https://github.com/jkriege2/JKQtExtras/pulls?q=is%3Apr+is%3Aclosed)

![EXAMPLES-Page](./screenshots/examplesbanner.png)

## Main Features

- CMake-based build system
- extensive set of [Examples/Tutorials](./examples/README.md)
- extensive doxygen-generated [Documentation](http://jkriege2.github.io/JKQtExtras/index.html)

## [Documentation](http://jkriege2.github.io/JKQtExtras/index.html)
A Documentation (auto-)generated with [doxygen](http://www.doxygen.nl/) from the trunk source code can be found here: 
**[http://jkriege2.github.io/JKQtExtras/index.html](http://jkriege2.github.io/JKQtExtras/index.html)**

Documentation is auto-generated after pushes by [Travis](https://travis-ci.org/jkriege2/JKQtExtras): [![Build Status](https://travis-ci.org/jkriege2/JKQtExtras.svg?branch=master)](https://travis-ci.org/jkriege2/JKQtExtras)

## [Examples](./examples/)
There is a [large set of usage examples (with explanations for each) and tutorials](./examples/) in the folder [`./examples/`](./examples).
All test-projects are Qt-projects that use qmake to build. You can load them into QtCreator easily.

## [Screenshots](./screenshots/)
The [Screenshots-page](./screenshots/) contains several screenshots, partly taken from the provided examples, but also from other software using this libarary (e.g. [QuickFit 3.0](https://github.com/jkriege2/QuickFit3))

[![EXAMPLES-Page](./screenshots/screenshotsbanner.png)](./screenshots/README.md)


## Building

JKQtExtras contains two different build systems: A modern [CMake](https://cmake.org/)-based build and an older (and deprecated!) QMake-based build (which works out of the box with Qt 5.x). Both systems are explained in detail in http://jkriege2.github.io/JKQtExtras/page_buildinstructions.html.


With [CMake](https://cmake.org/) you can easily build JKQtExtras and all its examples, by calling something like:
```
    $ mkdir build; cd build
    $ cmake .. -G "<cmake_generator>" "-DCMAKE_PREFIX_PATH=<path_to_your_qt_sources>"
    $ cmake --build . --config "Debug"
```
