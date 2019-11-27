TEMPLATE = subdirs

SUBDIRS +=  jkqtextraslib \
            jkqtextraslib_sharedlib


jkqtextraslib.file = qmake/staticlib/jkqtextraslib/jkqtextraslib.pro
jkqtextraslib_sharedlib.file = qmake/sharedlib/jkqtextraslib/jkqtextraslib.pro

jkqtextras_test.file = examples/jkqtextras_test/jkqtextras_test.pro
jkqtextras_test.depends = jkqtextraslib
