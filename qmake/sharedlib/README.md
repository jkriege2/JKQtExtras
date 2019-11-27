# JKQtExtras: Build as a SHARED library

This directory contains Projects that can be used to build a shared library of JKQtExtras (i.e. the contents of the directory [`../lib`](../lib)

## QMake

### Build shared libraries
There are several `.PRO`-files, that can be used to build the full library, or a limited subsets. They will produce a dynamic link library that you can include into your projects, e.g. with the following QMake-snippet:

```.qmake
# include JKQtExtras library
DEPENDPATH += <PATHTOJKQtExtrasDIR>/lib <PATHTOJKQtExtrasDIR>/qmake/sharedlib/JKQtExtraslib
INCLUDEPATH += <PATHTOJKQtExtrasDIR>/lib
CONFIG (debug, debug|release) {
    # ensure that DLLs are copied to the output directory
    install_JKQtExtras_dll.files = <PATHTOJKQtExtrasDIR>/qmake/sharedlib/JKQtExtraslib/debug/JKQtExtraslib_debug.*
    install_JKQtExtras_dll.path = $$OUT_PWD
    INSTALLS += install_JKQtExtras_dll
    # link agains DLLs
    DEPENDPATH += <PATHTOJKQtExtrasDIR>/qmake/sharedlib/JKQtExtraslib/debug
    LIBS += -L<PATHTOJKQtExtrasDIR>/qmake/sharedlib/JKQtExtraslib/debug -lJKQtExtraslib_debug
} else {
    # ensure that DLLs are copied to the output directory
    install_JKQtExtras_dll.files = <PATHTOJKQtExtrasDIR>/qmake/sharedlib/JKQtExtraslib/release/JKQtExtraslib.*
    install_JKQtExtras_dll.path = $$OUT_PWD
    INSTALLS += install_JKQtExtras_dll
    DEPENDPATH += <PATHTOJKQtExtrasDIR>/qmake/sharedlib/JKQtExtraslib/release
    # link agains DLLs
    LIBS += -L<PATHTOJKQtExtrasDIR>/qmake/sharedlib/JKQtExtraslib/release -lJKQtExtraslib
}
```

This snippet assumes that you built the libraries with the provided `.PRO`-files.

*Note* that you will have to run a deployment step `make install` before running your executable, so the shared libararies are actually copied to the output directory (see `INSTALLS + ...` above).



