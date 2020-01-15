/*
    Copyright (c) 2008-2019 Jan W. Krieger (<jan@jkrieger.de>)

    This software is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License (LGPL) as published by
    the Free Software Foundation, either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License (LGPL) for more details.

    You should have received a copy of the GNU Lesser General Public License (LGPL)
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "jkqteprogresslistwidget.h"
#include <QApplication>

JKQTEProgressListWidget::JKQTEProgressListWidget(QWidget *parent) :
    QWidget(parent)
{
    Q_INIT_RESOURCE(jkqteprogresslistwidget);
    m_icons[JKQTEProgressListWidget::statusNone]=QIcon(":/jkqteprogresslistwidget/statusNone.png");
    m_icons[JKQTEProgressListWidget::statusDone]=QIcon(":/jkqteprogresslistwidget/statusDone.png");
    m_icons[JKQTEProgressListWidget::statusFailed]=QIcon(":/jkqteprogresslistwidget/statusFailed.png");
    m_icons[JKQTEProgressListWidget::statusNotStarted]=QIcon(":/jkqteprogresslistwidget/statusNotStarted.png");
    m_icons[JKQTEProgressListWidget::statusInProgress]=QIcon(":/jkqteprogresslistwidget/statusInProgress.png");
    m_iconSize=QSize(16,16);

    m_centered=true;
    layout=new QGridLayout(this);
    setLayout(layout);
}

void JKQTEProgressListWidget::defineIcon(int status, QIcon icon) {
    m_icons[status]=icon;
}

QIcon JKQTEProgressListWidget::getIcon(int status) const {
    return m_icons.value(status, QIcon());
}

int JKQTEProgressListWidget::getStatus(int item) const {
    return m_status.value(item, JKQTEProgressListWidget::statusNone);
}

QString JKQTEProgressListWidget::getText(int item) const {
    return m_items.value(item, "");
}

void JKQTEProgressListWidget::deleteItem(int item) {
    m_items.removeAt(item);
    m_status.removeAt(item);
    updateWidgets();
}

int JKQTEProgressListWidget::count() const {
    return qMin(m_items.size(), m_status.size());
}

void JKQTEProgressListWidget::addItem(const QString &text, int status) {
    m_items.append(text);
    m_status.append(status);
    updateWidgets();
}

QSize JKQTEProgressListWidget::getIconSize() const {
    return m_iconSize;
}

void JKQTEProgressListWidget::setIconSize(QSize size) {
    m_iconSize=size;
    updateWidgets();
}

void JKQTEProgressListWidget::setIconSize(int size)
{
    setIconSize(QSize(size,size));
}

bool JKQTEProgressListWidget::isCentered() const {
    return m_centered;
}

void JKQTEProgressListWidget::setCentered(bool centered) {
    m_centered=centered;
    updateWidgets();
}

void JKQTEProgressListWidget::start() {
    for (int i=0; i<count(); i++) {
        if (m_status[i]==JKQTEProgressListWidget::statusNotStarted) {
            m_status[i]=JKQTEProgressListWidget::statusInProgress;
            break;
        }
    }
    updateWidgets();
}

void JKQTEProgressListWidget::nextItem(int newStatusLast) {
    bool findNext=false;
    for (int i=0; i<count(); i++) {
        if (findNext) {
            if (m_status[i]==JKQTEProgressListWidget::statusNotStarted) {
                m_status[i]=JKQTEProgressListWidget::statusInProgress;
                break;
            }
        } else if (m_status[i]==JKQTEProgressListWidget::statusInProgress) {
            m_status[i]=newStatusLast;
            findNext=true;
        }
    }
    updateWidgets();
}

void JKQTEProgressListWidget::updateWidgets() {
    int newCount=count();
    int oldCount=m_widgets.size();

    if (newCount<oldCount) {
        for (int i=oldCount-1; i>=newCount; i--) {
            layout->removeWidget(m_widgets[i].labIcon);
            layout->removeWidget(m_widgets[i].labText);
            delete m_widgets[i].labIcon;
            delete m_widgets[i].labText;
            m_widgets.removeAt(i);
        }
    } else if (newCount>oldCount) {
        for (int i=oldCount; i<newCount; i++) {
            JKQTEProgressListWidget::widgetstruct w;
            w.labIcon=new QLabel(this);
            w.labIcon->setAlignment(Qt::AlignTop|Qt::AlignRight);
            w.labText=new QLabel(this);
            w.labText->setAlignment(Qt::AlignTop|Qt::AlignLeft);
            int row=layout->rowCount();
            layout->addWidget(w.labIcon, row, 0);
            layout->addWidget(w.labText, row, 1);
            m_widgets.append(w);
        }
    }
    for (int i=0; i<newCount; i++) {
        m_widgets[i].labIcon->setPixmap(m_icons.value(m_status.value(i, JKQTEProgressListWidget::statusNone), QIcon()).pixmap(m_iconSize));
        m_widgets[i].labText->setText(m_items.value(i, ""));
    }
    if (layout->columnCount()>1) {
        layout->setColumnStretch(0,0);
        layout->setColumnStretch(1,1);
    }
}

void JKQTEProgressListWidget::setItemStatus(int item, int status)
{
    m_status[item]=status;
    updateWidgets();
}

void JKQTEProgressListWidget::setItemText(int item, const QString& text) {
    m_items[item]=text;
    updateWidgets();
}

JKQTEProgressListDialog::JKQTEProgressListDialog(QWidget *parent, Qt::WindowFlags f):
    QDialog(parent, f)
{
    m_cancelRejects=false;
    m_wasCanceled=false;

    createWidgets();
}

JKQTEProgressListDialog::JKQTEProgressListDialog(const QString &labelText, const QString &cancelButtonText, int minimum, int maximum, QWidget *parent, Qt::WindowFlags f):
    QDialog(parent, f)
{
    m_cancelRejects=false;
    m_wasCanceled=false;
    m_hasProgressBar=true;

    createWidgets();
    setHasProgressBar(true);
    setRange(minimum, maximum);
    btnCancel->setText(cancelButtonText);
    setProgressText(labelText);

}

void JKQTEProgressListDialog::cancel() {
    m_wasCanceled=true;
    emit canceled();
    if (m_cancelRejects) reject();
}

void JKQTEProgressListDialog::showEvent(QShowEvent *event) {
    m_wasCanceled=false;
    QDialog::showEvent(event);
}

void JKQTEProgressListDialog::createWidgets() {

    QGridLayout* layout=new QGridLayout(this);
    setLayout(layout);
    list=new JKQTEProgressListWidget(this);
    layout->addWidget(list, 0,0,1,2);
    progressLine=new QFrame(this);
    progressLine->setVisible(false);
    //progressLine->setFrameStyle(QFrame::HLine);
    layout->addWidget(progressLine, 1,0,1,2);
    progress=new QProgressBar(this);
    progress->setVisible(false);
    layout->addWidget(progress, 1,0,1,2);
    labProgress=new QLabel(this);
    labProgress->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    labProgress->setVisible(false);
    layout->addWidget(labProgress, 2,0,1,2);

    btnCancel=new QPushButton(tr("&Cancel"), this);
    layout->addWidget(btnCancel, 3,1);
    layout->addItem(new QSpacerItem(5,5,QSizePolicy::Expanding),1,0);

    connect(btnCancel, SIGNAL(pressed()), this, SLOT(cancel()));
}

void JKQTEProgressListDialog::defineIcon(int status, QIcon icon)
{
    list->defineIcon(status, icon);
}

void JKQTEProgressListDialog::nextItem(int newStatusLast)
{
    list->nextItem(newStatusLast);
    QApplication::processEvents();
    QApplication::processEvents();

}

void JKQTEProgressListDialog::start()
{
    list->start();
    QApplication::processEvents();
    QApplication::processEvents();

}

void JKQTEProgressListDialog::setItemStatus(int item, int status)
{
    list->setItemStatus(item, status);
    repaint();
    QApplication::processEvents();
    QApplication::processEvents();
}

void JKQTEProgressListDialog::setItemText(int item, const QString &text)
{
    list->setItemText(item, text);
    repaint();
    QApplication::processEvents();
    QApplication::processEvents();
}

void JKQTEProgressListDialog::setRange(int min, int max)
{
    progress->setRange(min, max);
    repaint();
    QApplication::processEvents();
    QApplication::processEvents();
}

void JKQTEProgressListDialog::setMinimum(int min)
{
    progress->setMinimum(min);
    repaint();
    QApplication::processEvents();
    QApplication::processEvents();
}

void JKQTEProgressListDialog::setMaximum(int max)
{
    progress->setMaximum(max);
    repaint();
    QApplication::processEvents();
    QApplication::processEvents();
}

void JKQTEProgressListDialog::setValue(int value)
{
    progress->setValue(value);
    repaint();
    QApplication::processEvents();
    QApplication::processEvents();
}

void JKQTEProgressListDialog::setProgressText(const QString &text)
{
    labProgress->setText(text);
    repaint();
    QApplication::processEvents();
    QApplication::processEvents();
}

void JKQTEProgressListDialog::setLabelText(const QString &text)
{
    setProgressText(text);
}

void JKQTEProgressListDialog::setCancelButtonText(const QString &text)
{
    btnCancel->setText(text);
    repaint();
    QApplication::processEvents();
    QApplication::processEvents();
}

void JKQTEProgressListDialog::addItem(const QString &text, int status)
{
    list->addItem(text, status);
    repaint();
    QApplication::processEvents();
    QApplication::processEvents();
}

int JKQTEProgressListDialog::count() const
{
    return list->count();
}

void JKQTEProgressListDialog::setHasCancelButton(bool hasCancel, bool cancelRejects)
{
    btnCancel->setVisible(hasCancel);
    m_cancelRejects=cancelRejects;
}

void JKQTEProgressListDialog::setHasProgressBar(bool hasProg) {
    m_hasProgressBar=hasProg;
    labProgress->setVisible(m_hasProgressBar);
    progress->setVisible(m_hasProgressBar);
    progressLine->setVisible(m_hasProgressBar);
}

bool JKQTEProgressListDialog::wasCanceled() const
{
    return m_wasCanceled;
}

JKQTEProgressListWidget * JKQTEProgressListDialog::getProgressList() const
{
    return list;
}

void JKQTEProgressListDialog::reset()
{
    list->reset();
    QApplication::processEvents();
    QApplication::processEvents();
}

void JKQTEProgressListWidget::reset()
{
    for (int i=0; i<count(); i++) {
        if (m_status[i]>JKQTEProgressListWidget::statusNone && m_status[i]<JKQTEProgressListWidget::statusUser) {
            m_status[i]=JKQTEProgressListWidget::statusNotStarted;
        }
    }
    updateWidgets();
}

