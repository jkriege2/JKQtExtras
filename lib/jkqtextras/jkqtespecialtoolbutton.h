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

#ifndef JKQTESPECIALTOOLBUTTON_H
#define JKQTESPECIALTOOLBUTTON_H
#include <QToolBar>
#include <QToolButton>
#include <QLineEdit>
#include <QUrl>
#include <QString>
#include <QDesktopServices>
#include <QFileDialog>
#include <QFileInfo>
#include <iostream>
#include "jkqtextras_imexport.h"




/** \brief specialized QToolButton which takes the contents of its buddy as webpage adress (URL) and opens
 *         it in the system's standard application
 *  \ingroup JKQtExtrasWidgetsButtons
 *
 *  \image html JKQTEURLOpenToolButton.png
 *
 *  Usage example:
 *
 *  \snippet jkqtextras_test/testmainwindow.cpp Example: JKQTEURLOpenToolButton
 */
class JKQTEXTRAS_LIB_EXPORT JKQTEURLOpenToolButton : public QToolButton {
        Q_OBJECT
    public:
        /** Default constructor */
        JKQTEURLOpenToolButton(QWidget* parent=nullptr);
        /** Default destructor */
        virtual ~JKQTEURLOpenToolButton();

        /** \brief buddy associated with this button */
        const QLineEdit* buddy() const;
        /** \brief buddy associated with this button */
        QLineEdit* buddy() ;
        /** \brief set the buddy widget, which provides the contents */
        void setBuddy(QLineEdit* b);
    protected slots:
        /** \brief opens the contents of the buddy() as URL
         *
         *  This internally calls \c QDesktopServices::openUrl(QUrl(buddyContents,QUrl::TolerantMode));
         */
        void openBuddyContents();
    private:
        QLineEdit* m_buddy;
};


/** \brief specialized QToolButton which allows to select a file and saves its path in the buddy
 *  \ingroup JKQtExtrasWidgetsButtons
 *
 *  \image html JKQTEFileSelectToolButton.png
 *
 *  Usage example:
 *
 *  \snippet jkqtextras_test/testmainwindow.cpp Example: JKQTEFileSelectToolButton
 */
class JKQTEXTRAS_LIB_EXPORT JKQTEFileSelectToolButton : public QToolButton {
    Q_OBJECT
public:
    /** Default constructor */
    JKQTEFileSelectToolButton(QWidget* parent=nullptr);
    /** Default destructor */
    virtual ~JKQTEFileSelectToolButton();

    /** \brief buddy associated with this button */
    const QLineEdit* buddy() const;
    /** \brief buddy associated with this button */
    QLineEdit* buddy() ;
    /** \brief set the buddy widget, which provides the contents */
    void setBuddy(QLineEdit* b);
    /** \brief returns a basedir in which files are searched for execution, if this is empty the current directory is used */
    QString getBaseDir() const;
    /** \brief returns the title label of the file select dialog*/
    QString getDialogTitle() const;
    /** \brief returns the file filter of the file select dialog*/
    QString getDialogFilter() const;
public slots:
    /** \brief sets the file filter of the file select dialog*/
    void setDialogFilter(const QString &b);
    /** \brief sets the title label of the file select dialog*/
    void setDialogTitle(const QString& b);
    /** \brief set a basedir in which files are searched for execution, if this is empty the current directory is used */
    void setBaseDir(const QString& b);
protected slots:
    void openBuddyContents();
private:
    QLineEdit* m_buddy;
    QString m_baseDir;
    QString m_dlgTitle;
    QString m_dlgFilter;
};


/** \brief specialized QToolButton which allows to select a directory and saves its path in the buddy
 *  \ingroup JKQtExtrasWidgetsButtons
 *
 *  \image html JKQTEDirectorySelectToolButton.png
 *
 *  Usage example:
 *
 *  \snippet jkqtextras_test/testmainwindow.cpp Example: JKQTEDirectorySelectToolButton
 */
class JKQTEXTRAS_LIB_EXPORT JKQTEDirectorySelectToolButton : public QToolButton {
    Q_OBJECT
public:
    /** Default constructor */
    JKQTEDirectorySelectToolButton(QWidget* parent=nullptr);
    /** Default destructor */
    virtual ~JKQTEDirectorySelectToolButton();

    /** \brief buddy associated with this button */
    const QLineEdit* buddy() const;
    /** \brief buddy associated with this button */
    QLineEdit* buddy() ;
    /** \brief set the buddy widget, which provides the contents */
    void setBuddy(QLineEdit* b);
    /** \brief returns a basedir in which files are searched for execution, if this is empty the current directory is used */
    QString getBaseDir() const;
    /** \brief returns the title label of the file select dialog*/
    QString getDialogTitle() const;
public slots:
    /** \brief sets the file filter of the file select dialog*/
    void setDialogFilter(const QString &b);
    /** \brief set a basedir in which files are searched for execution, if this is empty the current directory is used */
    void setBaseDir(const QString& b);
protected slots:
    void openBuddyContents();
private:
    QLineEdit* m_buddy;
    QString m_baseDir;
    QString m_dlgTitle;
    QString m_dlgFilter;
};


/** \brief specialized QToolButton which allows to open the file referenced by the buddy edit
 *  \ingroup JKQtExtrasWidgetsButtons
 *
 *  \image html JKQTEFileExecuteToolButton.png
 *
 *  Usage example:
 *
 *  \snippet jkqtextras_test/testmainwindow.cpp Example: JKQTEFileExecuteToolButton
 */
class JKQTEXTRAS_LIB_EXPORT JKQTEFileExecuteToolButton : public QToolButton {
        Q_OBJECT
    public:
        /** Default constructor */
        JKQTEFileExecuteToolButton(QWidget* parent=nullptr);
        /** Default destructor */
        virtual ~JKQTEFileExecuteToolButton();
        /** \brief buddy associated with this button */
        const QLineEdit* buddy() const;
        /** \brief buddy associated with this button */
        QLineEdit* buddy();
        /** \brief returns a basedir in which files are searched for execution, if this is empty the current directory is used */
        QString getBaseDir() const;
    public slots:
        /** \brief set the buddy widget, which provides the contents */
        void setBuddy(QLineEdit* b);
        /** \brief set a basedir in which files are searched for execution, if this is empty the current directory is used */
        void setBaseDir(const QString& b);
    protected slots:
        /** \brief executes the contents of the buddy()
         *
         *  This internally calls \c QDesktopServices::openUrl(QUrl("file:///"+buddyContents,QUrl::TolerantMode));
         *
         *  \see setBaseDir()
         */
        void openBuddyContents();

    private:
        QLineEdit* m_buddy;
        QString m_baseDir;
};

#endif // JKQTESPECIALTOOLBUTTON_H
