TEMPLATE = subdirs

SUBDIRS +=  jkqtextraslib jkqtextras_test

jkqtextraslib.file = ../../qmake/staticlib/jkqtextraslib/jkqtextraslib.pro

jkqtextras_test.file=$$PWD/jkqtextras_test.pro
jkqtextras_test.depends = jkqtextraslib
