/*
    Copyright (c) 2008-2020 Jan W. Krieger (<jan@jkrieger.de>)

    This software is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License (LGPL) as
    published by the Free Software Foundation, either version 2.1 of the License,
    or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License (LGPL) for more details.

    You should have received a copy of the GNU Lesser General Public License
    (LGPL) along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "jkqtespecialtoolbutton.h"

JKQTEURLOpenToolButton::JKQTEURLOpenToolButton(QWidget* parent):
    QToolButton(parent)
{
    Q_INIT_RESOURCE(jkqtespecialtoolbutton);
    this->connect(this, SIGNAL(clicked()), this, SLOT(openBuddyContents()));
    setIcon(QIcon(tr(":/jkqtespecialtoolbutton/urltoolbutton.png")));
}

JKQTEURLOpenToolButton::~JKQTEURLOpenToolButton()
{
    disconnect(this, SIGNAL(clicked()), this, SLOT(openBuddyContents()));
}

const QLineEdit *JKQTEURLOpenToolButton::buddy() const {
    return m_buddy;
}

QLineEdit *JKQTEURLOpenToolButton::buddy() {
    return m_buddy;
}

void JKQTEURLOpenToolButton::setBuddy(QLineEdit *b)
{
    m_buddy=b;
}

void JKQTEURLOpenToolButton::openBuddyContents() {
    if (m_buddy==NULL) return;
    QString a=m_buddy->text();
    QDesktopServices::openUrl(QUrl(a, QUrl::TolerantMode));
}



JKQTEDirectorySelectToolButton::JKQTEDirectorySelectToolButton(QWidget* parent):
    QToolButton(parent),
    m_buddy(nullptr),
    m_baseDir(),
    m_dlgTitle(tr("Select Directory ..."))
{
    Q_INIT_RESOURCE(jkqtespecialtoolbutton);
    Q_INIT_RESOURCE(jkqtespecialtoolbutton);
    this->connect(this, SIGNAL(clicked()), this, SLOT(openBuddyContents()));
    setIcon(QIcon(tr(":jkqtespecialtoolbutton/dirselecttoolbutton.png")));
}

JKQTEDirectorySelectToolButton::~JKQTEDirectorySelectToolButton()
{
    disconnect(this, SIGNAL(clicked()), this, SLOT(openBuddyContents()));
}

const QLineEdit *JKQTEDirectorySelectToolButton::buddy() const {
    return m_buddy;
}

QLineEdit *JKQTEDirectorySelectToolButton::buddy()  {
    return m_buddy;
}

void JKQTEDirectorySelectToolButton::setBuddy(QLineEdit *b)
{
    m_buddy=b;
}

void JKQTEDirectorySelectToolButton::setBaseDir(const QString &b) {
    m_baseDir=b;
}

QString JKQTEDirectorySelectToolButton::getBaseDir() const
{
    return m_baseDir;
}

QString JKQTEDirectorySelectToolButton::getDialogTitle() const
{
    return m_dlgTitle;
}

void JKQTEDirectorySelectToolButton::setDialogFilter(const QString &b)
{
    m_dlgFilter=b;
}


void JKQTEDirectorySelectToolButton::openBuddyContents() {
    if (m_buddy==NULL) return;
    static QString dir="";
    QString dirName = QFileDialog::getExistingDirectory(this, m_dlgTitle, dir, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!dirName.isEmpty()) {
        dir=QDir(dirName).absolutePath();

        m_buddy->setText(QDir((m_baseDir.isEmpty())?QDir::currentPath():m_baseDir).relativeFilePath( dirName));
        m_buddy->setFocus(Qt::MouseFocusReason);
    }
}




JKQTEFileSelectToolButton::JKQTEFileSelectToolButton(QWidget* parent):
    QToolButton(parent),
    m_buddy(nullptr),
    m_baseDir(),
    m_dlgTitle(tr("Select File ...")),
    m_dlgFilter(tr("All Files (*.*)"))
{
    Q_INIT_RESOURCE(jkqtespecialtoolbutton);
    this->connect(this, SIGNAL(clicked()), this, SLOT(openBuddyContents()));
    setIcon(QIcon(tr(":/jkqtespecialtoolbutton/fileselecttoolbutton.png")));
}

JKQTEFileSelectToolButton::~JKQTEFileSelectToolButton()
{
    disconnect(this, SIGNAL(clicked()), this, SLOT(openBuddyContents()));
}

const QLineEdit *JKQTEFileSelectToolButton::buddy() const {
    return m_buddy;
}

QLineEdit *JKQTEFileSelectToolButton::buddy()  {
    return m_buddy;
}

void JKQTEFileSelectToolButton::setBuddy(QLineEdit *b)
{
    m_buddy=b;
}

void JKQTEFileSelectToolButton::setBaseDir(const QString &b) {
    m_baseDir=b;
}

QString JKQTEFileSelectToolButton::getBaseDir() const
{
    return m_baseDir;
}

void JKQTEFileSelectToolButton::setDialogTitle(const QString &b)
{
    m_dlgTitle=b;
}

QString JKQTEFileSelectToolButton::getDialogTitle() const
{
    return m_dlgTitle;
}

void JKQTEFileSelectToolButton::setDialogFilter(const QString &b)
{
    m_dlgFilter=b;
}

QString JKQTEFileSelectToolButton::getDialogFilter() const
{
    return m_dlgFilter;
}

void JKQTEFileSelectToolButton::openBuddyContents() {
    if (m_buddy==NULL) return;
    static QString dir="";
    QString fileName = QFileDialog::getOpenFileName(this, m_dlgTitle, dir, m_dlgFilter);
    if (!fileName.isEmpty()) {
        dir=QFileInfo(fileName).dir().absolutePath();

        m_buddy->setText(QDir((m_baseDir.isEmpty())?QDir::currentPath():m_baseDir).relativeFilePath( fileName));
        m_buddy->setFocus(Qt::MouseFocusReason);
    }
}



JKQTEFileExecuteToolButton::JKQTEFileExecuteToolButton(QWidget* parent):
    QToolButton(parent),
    m_buddy(nullptr),
    m_baseDir()
{
    this->connect(this, SIGNAL(clicked()), this, SLOT(openBuddyContents()));
    setIcon(QIcon(tr(":/jkqtespecialtoolbutton/executetoolbutton.png")));
}

JKQTEFileExecuteToolButton::~JKQTEFileExecuteToolButton()
{
    disconnect(this, SIGNAL(clicked()), this, SLOT(openBuddyContents()));
}

const QLineEdit *JKQTEFileExecuteToolButton::buddy() const {
    return m_buddy;
}

QLineEdit *JKQTEFileExecuteToolButton::buddy() {
    return m_buddy;
}

void JKQTEFileExecuteToolButton::setBuddy(QLineEdit *b) {
    m_buddy=b;
}

void JKQTEFileExecuteToolButton::setBaseDir(const QString &b) {
    m_baseDir=b;
}

QString JKQTEFileExecuteToolButton::getBaseDir() const
{
    return m_baseDir;
}

void JKQTEFileExecuteToolButton::openBuddyContents() {
    if (m_buddy==NULL) return;
    QString a=QDir::cleanPath (QDir((m_baseDir.isEmpty())?QDir::currentPath():m_baseDir).absoluteFilePath( m_buddy->text()));
    //std::cout<<"executing: "<<a.toStdString()<<std::endl;
    QDesktopServices::openUrl(QUrl("file:///"+a, QUrl::TolerantMode));
}

