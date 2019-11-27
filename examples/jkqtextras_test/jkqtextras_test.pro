# source code for this simple demo
SOURCES = barchart.cpp 

# configure Qt
CONFIG += link_prl qt
QT += core gui xml svg
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

# output executable name
TARGET = barchart

# include jkqtextras source code
DEPENDPATH += ../../lib  ../../qmake/staticlib/jkqtextraslib
INCLUDEPATH += ../../lib
CONFIG (debug, debug|release) {
    LIBS += -L../../qmake/staticlib/jkqtextraslib/debug -ljkqtextraslib_debug
} else {
    LIBS += -L../../qmake/staticlib/jkqtextraslib/release -ljkqtextraslib
}
message("LIBS = $$LIBS")


win32-msvc*: DEFINES += _USE_MATH_DEFINES
win32-msvc*: DEFINES += NOMINMAX



