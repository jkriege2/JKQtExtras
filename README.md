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

[![Code Quality](https://www.code-inspector.com/project/12237/score/svg) ![Code Grade](https://www.code-inspector.com/project/12237/status/svg)](https://frontend.code-inspector.com/public/project/12237/JKQtExtras/dashboard)

## Main Features
- [Widget Gallery](https://jkriege2.github.io/JKQtExtras/_widget_gallery.html)
- CMake-based build system
- extensive set of [Examples/Tutorials](./examples/README.md)
- extensive doxygen-generated [Documentation](http://jkriege2.github.io/JKQtExtras/index.html)

## [Documentation](http://jkriege2.github.io/JKQtExtras/index.html)
A Documentation (auto-)generated with [doxygen](http://www.doxygen.nl/) from the trunk source code can be found here: 
**[http://jkriege2.github.io/JKQtExtras/index.html](http://jkriege2.github.io/JKQtExtras/index.html)**

Documentation is auto-generated after pushes by [Travis](https://travis-ci.org/jkriege2/JKQtExtras): [![Build Status](https://travis-ci.org/jkriege2/JKQtExtras.svg?branch=master)](https://travis-ci.org/jkriege2/JKQtExtras)

## [Examples](./examples/)
[Examples and tutorials](./examples/) are available in the folder [`./examples/`](./examples).


## Building

JKQtExtras contains two different build systems: A modern [CMake](https://cmake.org/)-based build and an older (and deprecated!) QMake-based build (which works out of the box with Qt 5.x). Both systems are explained in detail in http://jkriege2.github.io/JKQtExtras/page_buildinstructions.html.


With [CMake](https://cmake.org/) you can easily build JKQtExtras and all its examples, by calling something like:
```
    $ mkdir build; cd build
    $ cmake .. -G "<cmake_generator>" "-DCMAKE_PREFIX_PATH=<path_to_your_qt_sources>"
    $ cmake --build . --config "Debug"
```

