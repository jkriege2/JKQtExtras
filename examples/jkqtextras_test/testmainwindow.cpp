#include "testmainwindow.h"
#include "ui_testmainwindow.h"
#include "jkqtextras/jkqtevisiblehandlesplitter.h"
#include "jkqtextras/jkqteprogresslistwidget.h"
#include <QTextEdit>

TestMainWindow::TestMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestMainWindow)
{
    ui->setupUi(this);
    connect(ui->action_Close, &QAction::triggered, this, &TestMainWindow::close);

    ui->tabWidget->addTab(testVisibleHandleSplitter(), "JKQTEVisibleHandleSplitter");
    ui->tabWidget->addTab(testJKQTEProgressListWidget(), "JKQTEProgressListWidget");
}

TestMainWindow::~TestMainWindow()
{
    delete ui;
}

QWidget* TestMainWindow::testVisibleHandleSplitter()
{
//! [Example: JKQTEVisibleHandleSplitter]
    JKQTEVisibleHandleSplitter* splitV=new JKQTEVisibleHandleSplitter(Qt::Vertical, this);
    JKQTEVisibleHandleSplitter* splitH=new JKQTEVisibleHandleSplitter(Qt::Horizontal, this);

    QTextEdit* wid;
    splitV->addWidget(wid=new QTextEdit);
    wid->setPlainText("Move mouse over the splitter in between the widgets.\nThen you can move the splitter and see its highlighting effect.");
    splitH->addWidget(new QTextEdit);
    splitH->addWidget(new QTextEdit);
    splitV->addWidget(splitH);
//! [Example: JKQTEVisibleHandleSplitter]

    return splitV;
}

QWidget *TestMainWindow::testJKQTEProgressListWidget()
{
    //! [Example: JKQTEProgressListWidget]
    JKQTEProgressListWidget* progress=new JKQTEProgressListWidget(this);
    progress->addItem("item 1", JKQTEProgressListWidget::statusNotStarted);
    progress->addItem("item 2", JKQTEProgressListWidget::statusNotStarted);
    progress->addItem("item 3", JKQTEProgressListWidget::statusNotStarted);
    progress->addItem("item 4", JKQTEProgressListWidget::statusNotStarted);
    progress->addItem("item 5", JKQTEProgressListWidget::statusNotStarted);

    timJKQTEProgressListWidget=new QTimer(progress);
    stateJKQTEProgressListWidget=0;
    timJKQTEProgressListWidget->setInterval(500);
    connect(timJKQTEProgressListWidget, &QTimer::timeout, std::bind([progress](int& state){
        if (state==1) {
            for (int i=0; i<progress->count(); i++) {
                progress->setItemStatus(i, JKQTEProgressListWidget::statusNotStarted);
            }
            progress->start();
        } else if (state>10) {
            state=0;
        } else {
            progress->nextItem();
        }

        state++;
    }, std::ref(stateJKQTEProgressListWidget)));
    timJKQTEProgressListWidget->start();

    //! [Example: JKQTEProgressListWidget]

    return progress;
}
