TARGET = jkqtextraslib
CONFIG (debug, debug|release): TARGET = jkqtextraslib_debug

TEMPLATE = lib
CONFIG += dll
CONFIG += create_prl

win32 {
    DEFINES += JKQTEXTRAS_LIB_IN_DLL
    DEFINES += JKQTEXTRAS_LIB_EXPORT_LIBRARY
}

win32-msvc*: DEFINES += _USE_MATH_DEFINES
win32-msvc*: DEFINES += NOMINMAX


include(../../lib/jkqtextras.pri)
