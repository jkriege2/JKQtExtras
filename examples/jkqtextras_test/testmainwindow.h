#ifndef TESTMAINWINDOW_H
#define TESTMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class TestMainWindow;
}

class TestMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestMainWindow(QWidget *parent = nullptr);
    ~TestMainWindow();
protected:
    QWidget *testVisibleHandleSplitter();
    QWidget *testJKQTEProgressListWidget();
    QWidget *testJKQTEModernProgressWidget();
    QWidget *testJKQTEColorSlider();
    QWidget *testMiscellanious();
    QWidget *testJKQTEDoubleEdit();
private:
    Ui::TestMainWindow *ui;
    QTimer* timJKQTEProgressListWidget;
    int stateJKQTEProgressListWidget;
    QTimer* timJKQTEProgressListDialog;
    int stateJKQTEProgressListDialog;
};

#endif // TESTMAINWINDOW_H
