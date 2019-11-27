#include "testmainwindow.h"
#include "ui_testmainwindow.h"
#include "jkqtextras/jkqtevisiblehandlesplitter.h"
#include <QTextEdit>

TestMainWindow::TestMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestMainWindow)
{
    ui->setupUi(this);
    connect(ui->action_Close, &QAction::triggered, this, &TestMainWindow::close);

    ui->tabWidget->addTab(testVisibleHandleSplitter(), "JKQTEVisibleHandleSplitter");
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
