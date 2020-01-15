/*
    Copyright (c) 2008-2020 Jan W. Krieger (<jan@jkrieger.de>)

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

#ifndef JKTEDOUBLEEDIT_H
#define JKTEDOUBLEEDIT_H

#include "jkqtextras_imexport.h"
#include <QLineEdit>
#include <QRegExpValidator>
#include <QRegExp>
#include <QToolButton>
#include <cmath>
#include <QList>
#include <QAction>
#include <QPair>

/*! \brief this QLineEdit descendent implements a validating edit field that allows to enter floating point numbers
           with a possibly defined range
    \ingroup JKQtExtrasWidgetsEdits

    This widget supports this set of features:
        - This widget accepts input in standard and scientific notation.
        - The widget can optionally check (and correct) the edit range. Checking can be switched for
          the upper and lower bound indepently!
        - The maximal number of decimals may be set using setDecimals(). \note Note that trailing 0s are deleted from the string.
        - This widget accepts comma and point as decimal separator and transforms them to the systems decimal separator,
          set in the current locale.
        - This widget colors the background of the widget if the number you entered exceeds the range.
          In that case the edit corrects the value when it looses its focus. The error background color may be set
          by setErrorBackgroundColor().
        - It is also possible to extend the default context menu with new QAction's by calling addContextmenuAction(),
          deleteContextmenuAction() and clearContextmenuActions().
        - This widget may also be used to catch key events. You will have to register each event using addKeyEvent().
          If a key event matches, the keyEvent() signal will be emitted.
    .

    Screenshot:
    \image html JKQTEDoubleEdit.png

    Basic usage is simple:
    \snippet jkqtextras_test/testmainwindow.cpp Example: JKQTEDoubleEdit

 */
class JKQTEXTRAS_LIB_EXPORT JKQTEDoubleEdit : public QLineEdit {
        Q_OBJECT
        Q_PROPERTY(int decimals READ decimals WRITE setDecimals USER true )
        Q_PROPERTY(double value READ value WRITE setValue USER true )
        Q_PROPERTY(double increment READ increment WRITE setIncrement USER true )
        Q_PROPERTY(double maximum READ maximum WRITE setMaximum USER true )
        Q_PROPERTY(double minimum READ minimum WRITE setMinimum USER true )
        Q_PROPERTY(bool checkMaximum READ checkMaximum WRITE setCheckMaximum USER true )
        Q_PROPERTY(bool checkMinimum READ checkMinimum WRITE setCheckMinimum USER true )
        Q_PROPERTY(bool showUpDown READ showUpDown WRITE setShowUpDown USER true )
        Q_PROPERTY(bool integerWidget READ isIntegerWidget WRITE setIntegerWidget USER true )
        Q_PROPERTY(QColor errorBackgroundColor READ errorBackgroundColor WRITE setErrorBackgroundColor USER true )
        Q_PROPERTY(QColor noIntegerBackgroundColor READ noIntegerBackgroundColor WRITE setNoIntegerBackgroundColor USER true )
        Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor USER true )
    public:
        /** \brief class constructor */
        JKQTEDoubleEdit(QWidget* parent);
        /** \brief class destructor */
        virtual ~JKQTEDoubleEdit();
        /** \brief return the value entered in this widget */
        double value() const;
        /** \brief add a new QAction to the default context menu (append after a seprator) */
        void addContextmenuAction(QAction* menuAction);
        /** \brief remove a given QAction from the default context menu (added with addContextmenuAction() ) */
        void deleteContextmenuAction(QAction* menuAction);
        /** \brief remove all additional context menu QAction s */
        void clearContextmenuActions();
        /** \brief add a new Key Event */
        void addKeyEvent(int key, Qt::KeyboardModifiers modifiers);
        /** \brief maximum of the value range */
        double maximum() const;
        /** \brief minimum of the value range */
        double minimum() const;
        /** \brief returns whether the range maximum is checked */
        bool checkMaximum() const;
        /** \brief returns whether the range minimum is checked */
        bool checkMinimum() const;
        /** \brief returns the number of displayed decimals */
        int decimals() const;
        /** \brief background color used when an entry error occured (unparseable string) */
        QColor errorBackgroundColor() const;
        /** \brief color for the widget's background */
        QColor backgroundColor() const;
        /** \brief background color used when an setIntegerWidget(true), but the entered number is no integer */
        QColor noIntegerBackgroundColor() const;
        /** \brief increment, when using the buttons or up/down keys */
        double increment() const;
        /** \brief are the up/down buttons shown? */
        bool showUpDown() const;
        /** \brief is integer edit mode en-/disable (only integer numbers are allowed, i.e. no decimals!) */
        bool isIntegerWidget() const;

    public slots:
        /** \brief background color used when an setIntegerWidget(true), but the entered number is no integer */
        void setNoIntegerBackgroundColor(const QColor &noIntegerBackgroundColor);
        /** \brief background color used when an entry error occured (unparseable string) */
        void setErrorBackgroundColor(const QColor& color);
        /** \brief color for the widget's background */
        void setBackgroundColor(const QColor& color);
        /** \brief sets whether the range maximum is checked */
        void setCheckMaximum(bool check);
        /** \brief sets whether the range minimum is checked */
        void setCheckMinimum(bool check);
        /** \brief sets which bounds of the range to checked */
        void setCheckBounds(bool min, bool max);
        /** \brief en-/disable integer edit mode (only integer numbers are allowed, i.e. no decimals!) */
        void setIntegerWidget(bool intWidget);
        /** \brief set the value entered in this widget */
        void setValue(double value);
        /** \brief maximum of the value range, also calls setCheckMaximum(true) */
        void setMaximum(double value);
        /** \brief minimum of the value range, also calls setCheckMinimum(true) */
        void setMinimum(double value);
        /** \brief set the value range, also calls setCheckMaximum(true) and setCheckMinimum(true) */
        void setRange(double min, double max);
        /** \brief set the number of displayed decimals */
        void setDecimals(int decimals);
        /** \brief increase value by increment() */
        void stepUp();
        /** \brief decrease value by increment() */
        void stepDown();
        /** \brief increment, when using the buttons or up/down keys */
        void setIncrement(double inc);
        /** \brief sets the single step increment (equivalent to setIncrement(inc) ) */
        void setSingleStep(double inc);
        /** \brief sets whether up/down buttons are shown */
        void setShowUpDown(bool showUpDown);
    signals:
        /** \brief emited whenever a entered value changed */
        void valueChanged(double value);
        /** \brief emitted when the widget looses focus */
        void focusOut(double value);
        /** \brief emitted when a key event matches */
        void keyEventMatches(int key, Qt::KeyboardModifiers modifiers);
    protected:
        /** \brief used to store the key events */
        QList<QPair<int, Qt::KeyboardModifiers> > m_keyEvents;
        /** \brief list of additional actions for context menu */
        QList<QAction*> m_contextmenuActions;
        /** \brief regular expression used to match floating point numbers */
        QRegExp m_regexp;
        /** \brief RegExp validator for this widget */
        QRegExpValidator* m_validator;
        /** \brief hidden setValidator() method */
        void setValidator(const QValidator* validator);
        /** \brief error color */
        QColor m_errorColor;
        QColor m_background;
        QColor m_noIntegerBackgroundColor;
        double m_maximum;
        double m_minimum;
        double m_increment;
        bool m_checkMaximum;
        bool m_checkMinimum;
        int m_decimals;
        QString JKDoubleEdit_BASIC_REGEXP;
        bool m_Integer;
        bool m_showUpDown;
        QToolButton* m_btnUp;
        QToolButton* m_btnDown;
        double m_current;
        virtual void contextMenuEvent(QContextMenuEvent* event);
    protected slots:
        void updateWidget(const QString & text);
        virtual void focusOutEvent ( QFocusEvent * event ) ;
        virtual void keyPressEvent ( QKeyEvent * event ) ;
        virtual void resizeEvent ( QResizeEvent * event ) ;
        virtual void wheelEvent(QWheelEvent *event);
};

#endif // JKTEDOUBLEEDIT_H
