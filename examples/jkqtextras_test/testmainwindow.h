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
private:
    Ui::TestMainWindow *ui;
    QTimer* timJKQTEProgressListWidget;
    int stateJKQTEProgressListWidget;
};

#endif // TESTMAINWINDOW_H
