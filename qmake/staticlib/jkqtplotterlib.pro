TARGET = jkqtextraslib
CONFIG (debug, debug|release): TARGET = jkqtextraslib_debug

TEMPLATE = lib
CONFIG += staticlib
CONFIG += create_prl

include(../../lib/jkqtextras.pri)

win32-msvc*: DEFINES += _USE_MATH_DEFINES
win32-msvc*: DEFINES += NOMINMAX
