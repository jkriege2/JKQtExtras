#include "testmainwindow.h"
#include "ui_testmainwindow.h"
#include "jkqtextras/jkqtevisiblehandlesplitter.h"
#include "jkqtextras/jkqteprogresslistwidget.h"
#include "jkqtextras/jkqtemodernprogress.h"
#include "jkqtextras/jkqtecolorslider.h"
#include "jkqtextras/jkqtecolorsampler.h"
#include <QTextEdit>
#include <QFormLayout>
#include <QSlider>
#include <QSpinBox>
#include <QGroupBox>

TestMainWindow::TestMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestMainWindow)
{
    ui->setupUi(this);
    connect(ui->action_Close, &QAction::triggered, this, &TestMainWindow::close);

    ui->tabWidget->addTab(testVisibleHandleSplitter(), "JKQTEVisibleHandleSplitter");
    ui->tabWidget->addTab(testJKQTEProgressListWidget(), "JKQTEProgressListWidget");
    ui->tabWidget->addTab(testJKQTEModernProgressWidget(), "JKQTEModernProgressWidget");
    ui->tabWidget->addTab(testJKQTEColorSlider(), "JKQTEColorSlider");
    ui->tabWidget->setCurrentIndex(2);
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
    QWidget* wid=new QWidget(this);
    QVBoxLayout* lay=new QVBoxLayout;
    wid->setLayout(lay);
    //! [Example: JKQTEProgressListWidget]
    JKQTEProgressListWidget* progress=new JKQTEProgressListWidget(wid);
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

    lay->addWidget(progress);
    lay->addStretch(1);

    return wid;
}

QWidget *TestMainWindow::testJKQTEColorSlider()
{
    QWidget* wid=new QWidget(this);
    QFormLayout* lay=new QFormLayout;
    wid->setLayout(lay);
    //! [Example: JKQTEColorSlider]

    JKQTEColorSlider* slider=new JKQTEColorSlider(Qt::Horizontal, wid);
    slider->setSliderMode(JKQTEColorSlider::HueSlider);
    slider->setIndicatorStyle(JKQTEColorSlider::FixedColorDoubleArrowIndicator);
    lay->addRow("JKQTEColorSlider, horizontal, HueSlider:", slider);

    //! [Example: JKQTEColorSlider]
    //slider->setIndicatorStyle(JKQTEColorSlider::FixedColorCircleIndicator);

    slider=new JKQTEColorSlider(Qt::Horizontal, wid);
    slider->setSliderMode(JKQTEColorSlider::SaturationSlider);
    lay->addRow("JKQTEColorSlider, horizontal, SaturationSlider:", slider);

    slider=new JKQTEColorSlider(Qt::Horizontal, wid);
    slider->setSliderMode(JKQTEColorSlider::ValueSlider);
    lay->addRow("JKQTEColorSlider, horizontal, ValueSlider:", slider);

    slider=new JKQTEColorSlider(Qt::Horizontal, wid);
    slider->setSliderMode(JKQTEColorSlider::TransparencySlider);
    slider->setBaseColor(QColor("blue"));
    lay->addRow("JKQTEColorSlider, horizontal, TransparencySlider:", slider);
    slider=new JKQTEColorSlider(Qt::Horizontal, wid);
    slider->setSliderMode(JKQTEColorSlider::GreySlider);
    lay->addRow("JKQTEColorSlider, horizontal, GreySlider:", slider);

    slider=new JKQTEColorSlider(Qt::Horizontal, wid);
    slider->setSliderMode(JKQTEColorSlider::RedSlider);
    lay->addRow("JKQTEColorSlider, horizontal, RedSlider:", slider);

    slider=new JKQTEColorSlider(Qt::Horizontal, wid);
    slider->setSliderMode(JKQTEColorSlider::GreenSlider);
    lay->addRow("JKQTEColorSlider, horizontal, GreenSlider:", slider);

    slider=new JKQTEColorSlider(Qt::Horizontal, wid);
    slider->setSliderMode(JKQTEColorSlider::BlueSlider);
    lay->addRow("JKQTEColorSlider, horizontal, BlueSlider:", slider);


    slider=new JKQTEColorSlider(Qt::Vertical, wid);
    slider->setSliderMode(JKQTEColorSlider::HueSlider);
    slider->setIndicatorStyle(JKQTEColorSlider::FixedColorCircleIndicator);
    lay->addRow("JKQTEColorSlider, vertical, HueSlider:", slider);

    //! [Example: JKQTEColorSliderRGBGroup]

    QGroupBox* grp=new QGroupBox("RGB chooser");
    QGridLayout* layGrp=new QGridLayout;
    grp->setLayout(layGrp);

    JKQTEColorSlider* sliderR=new JKQTEColorSlider(Qt::Horizontal, grp);
    sliderR->setSliderMode(JKQTEColorSlider::RedSlider);
    layGrp->addWidget(sliderR, 0,0);

    JKQTEColorSlider* sliderG=new JKQTEColorSlider(Qt::Horizontal, grp);
    sliderG->setSliderMode(JKQTEColorSlider::GreenSlider);
    layGrp->addWidget(sliderG, 1,0);

    JKQTEColorSlider* sliderB=new JKQTEColorSlider(Qt::Horizontal, grp);
    sliderB->setSliderMode(JKQTEColorSlider::BlueSlider);
    layGrp->addWidget(sliderB, 2,0);

    connect(sliderR, SIGNAL(colorChanged(QColor)), sliderG, SLOT(setBaseColor(QColor)));
    connect(sliderG, SIGNAL(colorChanged(QColor)), sliderB, SLOT(setBaseColor(QColor)));

    //! [Example: JKQTEColorSliderRGBGroup]


    //! [Example: JKQTEColorSampler]

    JKQTEColorSampler* sampler=new JKQTEColorSampler(grp);
    // set sampler mode
    sampler->setSamplerMode(JKQTEColorSampler::RectangleSampler);
    // set sampler color
    sampler->setColor(QColor("red"));

    //! [Example: JKQTEColorSampler]

    connect(sliderB, SIGNAL(colorChanged(QColor)), sampler, SLOT(setColor(QColor)));
    layGrp->addWidget(sampler, 2,1);
    layGrp->setColumnStretch(0,1);

    /*sampler=new JKQTEColorSampler(grp);
    sampler->setSamplerMode(JKQTEColorSampler::CircleSampler);
    sampler->setColor(QColor("red"));
    connect(sliderG, SIGNAL(colorChanged(QColor)), sampler, SLOT(setColor(QColor)));
    layGrp->addWidget(sampler, 1,1);*/

    sliderR->setValue(127);
    sliderG->setValue(50);
    sliderB->setValue(200);

    lay->addRow(tr("RGB Chooser"), grp);


    return wid;
}

#define ADDMODERNPROGRESSROW(row, type, name) \
    {\
        JKQTEModernProgressWidget* progress=new JKQTEModernProgressWidget(main); \
        progress->setMode(type); \
        progress->setTextDisplayMode(JKQTEModernProgressWidget::NoText); \
        connect(slider, &QSlider::valueChanged, progress, &JKQTEModernProgressWidget::setValue); \
        connect(spinItems, SIGNAL(valueChanged(int)), progress, SLOT(setItems(int))); \
         \
        JKQTEModernProgressWidget* progressPerc=new JKQTEModernProgressWidget(main); \
        progressPerc->setMode(type); \
        progressPerc->setTextDisplayMode(JKQTEModernProgressWidget::PercentText); \
        connect(slider, &QSlider::valueChanged, progressPerc, &JKQTEModernProgressWidget::setValue); \
        connect(spinItems, SIGNAL(valueChanged(int)), progressPerc, SLOT(setItems(int))); \
         \
        JKQTEModernProgressWidget* progressVal=new JKQTEModernProgressWidget(main); \
        progressVal->setMode(type); \
        progressVal->setTextDisplayMode(JKQTEModernProgressWidget::ValueText); \
        progressVal->setSuffix("/100"); \
        connect(slider, &QSlider::valueChanged, progressVal, &JKQTEModernProgressWidget::setValue); \
        connect(spinItems, SIGNAL(valueChanged(int)), progressVal, SLOT(setItems(int))); \
         \
        JKQTEModernProgressWidget* progressSpin=new JKQTEModernProgressWidget(main); \
        progressSpin->setMode(type); \
        progressSpin->setSpin(true); \
        connect(spinItems, SIGNAL(valueChanged(int)), progressSpin, SLOT(setItems(int))); \
         \
        JKQTEModernProgressWidget* progressSpinPerc=new JKQTEModernProgressWidget(main); \
        progressSpinPerc->setMode(type); \
        progressSpinPerc->setTextDisplayMode(JKQTEModernProgressWidget::PercentText); \
        progressSpinPerc->setSpin(true); \
        connect(slider, &QSlider::valueChanged, progressSpinPerc, &JKQTEModernProgressWidget::setValue); \
        connect(spinItems, SIGNAL(valueChanged(int)), progressSpinPerc, SLOT(setItems(int))); \
         \
        JKQTEModernProgressWidget* progressSpinPercProgBarH=new JKQTEModernProgressWidget(main); \
        progressSpinPercProgBarH->setMode(type); \
        progressSpinPercProgBarH->setTextDisplayMode(JKQTEModernProgressWidget::PercentText); \
        progressSpinPercProgBarH->setInnerProgressIndicatorMode(JKQTEModernProgressWidget::InnerProgressBarHorizontal); \
        progressSpinPercProgBarH->setSpin(true); \
        connect(slider, &QSlider::valueChanged, progressSpinPercProgBarH, &JKQTEModernProgressWidget::setValue); \
        connect(spinItems, SIGNAL(valueChanged(int)), progressSpinPercProgBarH, SLOT(setItems(int))); \
         \
        JKQTEModernProgressWidget* progressSpinPercProgFillH=new JKQTEModernProgressWidget(main); \
        progressSpinPercProgFillH->setMode(type); \
        progressSpinPercProgFillH->setTextDisplayMode(JKQTEModernProgressWidget::PercentText); \
        progressSpinPercProgFillH->setInnerProgressIndicatorMode(JKQTEModernProgressWidget::InnerProgressFillHorizontal); \
        progressSpinPercProgFillH->setSpin(true); \
        connect(slider, &QSlider::valueChanged, progressSpinPercProgFillH, &JKQTEModernProgressWidget::setValue); \
        connect(spinItems, SIGNAL(valueChanged(int)), progressSpinPercProgFillH, SLOT(setItems(int))); \
         \
        JKQTEModernProgressWidget* progressSpinPercProgFillV=new JKQTEModernProgressWidget(main); \
        progressSpinPercProgFillV->setMode(type); \
        progressSpinPercProgFillV->setTextDisplayMode(JKQTEModernProgressWidget::PercentText); \
        progressSpinPercProgFillV->setInnerProgressIndicatorMode(JKQTEModernProgressWidget::InnerProgressFillVertical); \
        progressSpinPercProgFillV->setSpin(true); \
        connect(slider, &QSlider::valueChanged, progressSpinPercProgFillV, &JKQTEModernProgressWidget::setValue); \
        connect(spinItems, SIGNAL(valueChanged(int)), progressSpinPercProgFillV, SLOT(setItems(int))); \
         \
        JKQTEModernProgressWidget* progressSpinProgBarH=new JKQTEModernProgressWidget(main); \
        progressSpinProgBarH->setMode(type); \
        progressSpinProgBarH->setTextDisplayMode(JKQTEModernProgressWidget::NoText); \
        progressSpinProgBarH->setInnerProgressIndicatorMode(JKQTEModernProgressWidget::InnerProgressBarHorizontal); \
        progressSpinProgBarH->setSpin(true); \
        connect(slider, &QSlider::valueChanged, progressSpinProgBarH, &JKQTEModernProgressWidget::setValue); \
        connect(spinItems, SIGNAL(valueChanged(int)), progressSpinProgBarH, SLOT(setItems(int))); \
         \
        lay->addWidget(new QLabel(name), row,0); \
        lay->addWidget(progress, row, 1); \
        lay->addWidget(progressPerc, row, 2); \
        lay->addWidget(progressVal, row, 3); \
        lay->addWidget(progressSpin, row, 4); \
        lay->addWidget(progressSpinPerc, row, 5); \
        lay->addWidget(progressSpinPercProgBarH, row, 6); \
        lay->addWidget(progressSpinPercProgFillH, row, 7); \
        lay->addWidget(progressSpinPercProgFillV, row, 8); \
        lay->addWidget(progressSpinProgBarH, row, 9); \
    }

QWidget *TestMainWindow::testJKQTEModernProgressWidget()
{
    QWidget* main=new QWidget(this);
    QGridLayout* lay=new QGridLayout;
    main->setLayout(lay);
    QSlider* slider=new QSlider(Qt::Horizontal, main);
    slider->setRange(0,100);
    QSpinBox* spinItems=new QSpinBox(main);
    spinItems->setRange(0,100);

    int row=0;
    lay->addWidget(new QLabel(tr("Progress:")), row,0);
    lay->addWidget(slider, row, 1,1,5);
    row++;
    lay->addWidget(new QLabel(tr("Parameetrs:")), row,0);
    lay->addWidget(new QLabel(tr("#items:")), row,1);
    lay->addWidget(spinItems, row, 2);
    row++;

    lay->addWidget(new QLabel(tr("default\nNoText\nspin=false")), row,1);
    lay->addWidget(new QLabel(tr("default\nPercentText\nspin=false")), row,2);
    lay->addWidget(new QLabel(tr("default\nValueText\nspin=false")), row,3);
    lay->addWidget(new QLabel(tr("default\nNoText\nspin=true")), row,4);
    lay->addWidget(new QLabel(tr("default\nPercentText\nspin=true")), row,5);
    lay->addWidget(new QLabel(tr("default\nPercentText\nspin=true\nprog=HBar")), row,6);
    lay->addWidget(new QLabel(tr("default\nPercentText\nspin=true\nprog=HFill")), row,7);
    lay->addWidget(new QLabel(tr("default\nPercentText\nspin=true\nprog=VFill")), row,8);
    lay->addWidget(new QLabel(tr("default\nNoText\nspin=true\nprog=HBar")), row,9);
    row++;


    ADDMODERNPROGRESSROW(row, JKQTEModernProgressWidget::Circles, tr("JKQTEProgressListWidget: mode=Circles:"))
    row++;

    ADDMODERNPROGRESSROW(row, JKQTEModernProgressWidget::Strokes, tr("JKQTEProgressListWidget: mode=Strokes:"))
    row++;

    ADDMODERNPROGRESSROW(row, JKQTEModernProgressWidget::Ring, tr("JKQTEProgressListWidget: mode=Ring:"))
    row++;

    ADDMODERNPROGRESSROW(row, JKQTEModernProgressWidget::RoundedStrokeRing, tr("JKQTEProgressListWidget: mode=RoundedStrokeRing:"))
    row++;

    ADDMODERNPROGRESSROW(row, JKQTEModernProgressWidget::GradientRing, tr("JKQTEProgressListWidget: mode=GradientRing:"))
    row++;

    ADDMODERNPROGRESSROW(row, JKQTEModernProgressWidget::Pie, tr("JKQTEProgressListWidget: mode=Pie:"))
    row++;




    slider->setValue(50);
    return main;
}
