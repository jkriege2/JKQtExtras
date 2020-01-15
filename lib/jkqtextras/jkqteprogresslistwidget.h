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

#ifndef JKQTEPROGRESSLISTWIDGET_H
#define JKQTEPROGRESSLISTWIDGET_H

#include <QWidget>
#include <QStringList>
#include <QMap>
#include <QIcon>
#include <QList>
#include "jkqtextras_imexport.h"
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QDialog>
#include <QProgressBar>


/*! \brief displays a list of items with an icon next to each which indicates the current task performed on the item (e.g. not started, in progress, success, failed, ...)
   \ingroup JKQtExtrasWidgetsProgress

   \image html JKQTEProgressListWidget.png

   Usage example:

   \snippet jkqtextras_test/testmainwindow.cpp Example: JKQTEProgressListWidget

   There are two types of APIs that allow to modify the items:
     - You can use setItemStatus() to explicitly set a status for an item
     - you can use start() to set the first item in state JKQTEProgressListWidget::statusNotStarted
       to go to JKQTEProgressListWidget::statusInProgress. Then you can call nextItem(newState)
       to set the status of the item currently in JKQTEProgressListWidget::statusInProgress to the
       give \c newState and set the next item to JKQTEProgressListWidget::statusInProgress .
   .
 */
class JKQTEXTRAS_LIB_EXPORT JKQTEProgressListWidget : public QWidget {
        Q_OBJECT
    public:
        enum {            
            statusNone=0,
            statusNotStarted=1,
            statusDone=2,
            statusFailed=3,
            statusInProgress=4,
            statusUser=5
        };

        explicit JKQTEProgressListWidget(QWidget *parent = nullptr);

        /** \brief define an icon to be used for a given status.
         *
         *  \note The widget pre-defines default icons for the states JKQTEProgressListWidget::statusNone, JKQTEProgressListWidget::statusNotStarted, JKQTEProgressListWidget::statusDone, JKQTEProgressListWidget::statusFailed, JKQTEProgressListWidget::statusInProgress. */
        void defineIcon(int status, QIcon icon);
        /** \brief returns the icon used for a given \a status */
        QIcon getIcon(int status) const;

        /** \brief returns the status of a given \a item */
        int getStatus(int item) const;
        /** \brief returns the text of a given \a item */
        QString getText(int item) const;
        /** \brief deletes a given \a item */
        void deleteItem(int item);
        /** \brief returns the number of items in the list */
        int count() const;
        /** \brief add an item to the list */
        void addItem(const QString& text, int status=statusNotStarted);
        /** \brief returns currently used icon size for status icons */
        QSize getIconSize() const;
        /** \brief inidctaes whether to center the display */
        bool isCentered() const;

    public slots:
        /** \brief searches for the first item with status statusInProgress and switches it's status to \a newStatusLast The next item with status  statusNotStarted is switched to statusInProgress */
        void nextItem(int newStatusLast=statusDone);
        /** \brief searched for the first item with status statusNotStarted and sets it to statusInProgress */
        void start();
        /** \brief reset the list, i.e. set all items to JKQTEProgressListWidget::statusNotStarted */
        void reset();

        /** \brief set the status of the \a item -th item (allowed values: JKQTEProgressListWidget::statusNone, JKQTEProgressListWidget::statusNotStarted, JKQTEProgressListWidget::statusDone, JKQTEProgressListWidget::statusFailed, JKQTEProgressListWidget::statusInProgress, JKQTEProgressListWidget::statusUser ...) */
        void setItemStatus(int item, int status);
        /** \brief set the text of the \a item -th item */
        void setItemText(int item, const QString& text);

        /** \brief inidctaes whether to center the display */
        void setCentered(bool centered);
        /** \brief sets the currently used icon size for status icons */
        void setIconSize(QSize size);
        /** \brief sets the currently used icon size for status icons */
        void setIconSize(int size);

    protected:
        struct widgetstruct  {
            QLabel* labIcon;
            QLabel* labText;
        };

        bool m_centered;

        QStringList m_items;
        QList<int> m_status;
        QMap<int, QIcon> m_icons;
        QList<widgetstruct> m_widgets;
        QSize m_iconSize;
        QGridLayout* layout;

        void updateWidgets();
};


/** \brief a dialog with a JKQTEProgressListWidget and a cancel button (optional)
 *  \ingroup JKQtExtrasWidgetsProgress
 *
 * \image html JKQTEProgressListDialog.png
 *
 * Usage example:
 *
 *   \snippet jkqtextras_test/testmainwindow.cpp Example: JKQTEProgressListDialog
 *
 * \see JKQTEProgressListWidget
 */
class JKQTEXTRAS_LIB_EXPORT JKQTEProgressListDialog : public QDialog {
        Q_OBJECT
    public:
        JKQTEProgressListDialog(QWidget * parent = nullptr, Qt::WindowFlags f = nullptr);
        JKQTEProgressListDialog(const QString & labelText, const QString & cancelButtonText, int minimum, int maximum, QWidget * parent = 0, Qt::WindowFlags f = 0);
        JKQTEProgressListWidget* getProgressList() const;

        /** \brief switch visibility of cancel button (\a hasCancel \c =true ) and whether pressing it causes the dialog to be rejected. */
        void setHasCancelButton(bool hasCancel, bool cancelRejects=false);
        /** \brief switch additional progress indicator on or off */
        void setHasProgressBar(bool hasProg=true);
        /** \brief indicates whether the dialog was canceled (via the cancel button or calling cancel() ) */
        bool wasCanceled() const;
        /** \copydoc JKQTEProgressListWidget::defineIcon() */
        void defineIcon(int status, QIcon icon);
        /** \copydoc JKQTEProgressListWidget::addItem() */
        void addItem(const QString& text, int status=JKQTEProgressListWidget::statusNotStarted);
        /** \copydoc JKQTEProgressListWidget::count() */
        int count() const;
    public slots:
        /** \brief cancel the dialog  */
        void cancel();
        /** \brief searches for the first item with status statusInProgress and switches it's status to \a newStatusLast The next item with status  statusNotStarted is switched to statusInProgress */
        void nextItem(int newStatusLast=JKQTEProgressListWidget::statusDone);
        /** \copydoc JKQTEProgressListWidget::start() */
        void start();
        /** \copydoc JKQTEProgressListWidget::reset() */
        void reset();

        /** \copydoc JKQTEProgressListWidget::setItemStatus() */
        void setItemStatus(int item, int status);
        /** \copydoc JKQTEProgressListWidget::setItemText() */
        void setItemText(int item, const QString& text);
        /** \brief set the range of the progress indicator */
        void setRange(int min, int max);
        /** \brief set the range minimum of the progress indicator */
        void setMinimum(int min);
        /** \brief set the range maximum of the progress indicator */
        void setMaximum(int max);
        /** \brief set the value of the progress indicator */
        void setValue(int value);
        /** \brief set the text on the progress indicator*/
        void setProgressText(const QString& text);
        /** \brief set the text on the label */
        void setLabelText(const QString& text);
        /** \brief set the text on the cancel button */
        void setCancelButtonText(const QString& text);
    signals:
        /** \brief emitted when the dialog is canceled */
        void canceled();
    protected:
        JKQTEProgressListWidget* list;
        QPushButton* btnCancel;
        bool m_wasCanceled;
        bool m_cancelRejects;
        bool m_hasProgressBar;
        QLabel* labProgress;
        QProgressBar* progress;
        QFrame* progressLine;

        virtual void showEvent(QShowEvent* event);
        void createWidgets();
};


#endif // JKQTEPROGRESSLISTWIDGET_H

