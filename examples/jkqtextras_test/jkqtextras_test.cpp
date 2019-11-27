/** \example jkqtextras_test.cpp
 * Showcases the widgets in JKQtExtras
 *
 * \ref JKQTExtrasTest
 */
 
#include <QApplication>
#include "testmainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    TestMainWindow win;

    win.show();

    return app.exec();
}
