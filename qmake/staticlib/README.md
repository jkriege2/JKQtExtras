# JKQTPlotter: Build as a STATIC library

This directory contains Projects that can be used to build a static library of JKQTPlotter (i.e. the contents of the directory [`../lib`](../lib)

## QMake

### Build shared libraries
There are several `.PRO`-files, that can be used to build the full library, or a limited subsets. They will produce a static link libraries that you can include into your projects, e.g. with the following QMake-snippet:

```.qmake
# include JKQTPlotter library
DEPENDPATH += <PATHTOJKQTEXTRASDIR>/qmake/staticlib/ <PATHTOJKQTEXTRASDIR>/lib
INCLUDEPATH += <PATHTOJKQTEXTRASDIR>/lib
CONFIG (debug, debug|release) {
    DEPENDPATH += <PATHTOJKQTEXTRASDIR>/qmake/staticlib/debug
    LIBS += -L<PATHTOJKQTEXTRASDIR>/qmake/staticlib/debug -ljkqtplotterlib_debug
} else {
    DEPENDPATH += <PATHTOJKQTEXTRASDIR>/qmake/staticlib/release
    LIBS += -L<PATHTOJKQTEXTRASDIR>/qmake/staticlib/release -ljkqtplotterlib
}
```

This snippet assumes that you built the libraries with the provided `.PRO`-files.



