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

#ifndef JKQTEVISIBLEHANDLESPLITTER_H
#define JKQTEVISIBLEHANDLESPLITTER_H

#include <QSplitter>
#include <QSplitterHandle>
#include "jkqtextras_imexport.h"

/*! \brief a QSplitter that has a really visible Splitter handle
    \ingroup JKQtExtrasWidgetsLayout

    This is a simple replacement for <a href="https://doc.qt.io/qt-5/qsplitter.html">QSplitter</a>,
    which only adds sime visual tweaks:
      - a better visible handle
      - a highlighting/hover effect
      - a changeable grip width
    .

    The splitter looks like this:
    \image html JKQTEVisibleHandleSplitter.png
    \image html JKQTEVisibleHandleSplitterHover.png

    Usage is simple:

    \snippet jkqtextras_test/testmainwindow.cpp Example: JKQTEVisibleHandleSplitter

 */
class JKQTEXTRAS_LIB_EXPORT JKQTEVisibleHandleSplitter : public QSplitter {
        Q_OBJECT
        Q_PROPERTY(bool decorated READ decorated WRITE setDecorated USER true)
        Q_PROPERTY(bool hoverEffect READ hoverEffect WRITE setHoverEffect USER true)
        Q_PROPERTY(int gripWidth READ gripWidth WRITE setGripWidth USER true)
    public:
        explicit JKQTEVisibleHandleSplitter(Qt::Orientation orientation, QWidget *parent = nullptr);
        explicit JKQTEVisibleHandleSplitter(QWidget *parent = nullptr);
        /** \brief indicates whether the decoration of the handle is on or off (decoration is a roughed up surface area) */
        bool decorated() const;
        /** \brief indicates whether the hover effect of the handle is on or off (hover effect highlights the handle when the mouse hovers over it) */
        bool hoverEffect() const;
        /** \brief the width of the handle */
        int gripWidth() const;
    public slots:
        /** \brief switches the decoration of the handle on or off (decoration is a roughed up surface area) */
        void setDecorated(bool enabled);
        /** \brief switches the hover effect of the handle on or off (hover effect highlights the handle when the mouse hovers over it) */
        void setHoverEffect(bool enabled);
        /** \brief sets the width of the handle */
        void setGripWidth(int width);
    signals:

    public slots:

    protected:
        QSplitterHandle *createHandle();

};



/*! \brief a QSplitterHandle that is really visible Splitter handle (used by JKQTEVisibleHandleSplitter)
    \ingroup JKQtExtrasWidgetsLayout

    \see JKQTEVisibleHandleSplitter

 */
class JKQTEXTRAS_LIB_EXPORT JKQTEVisibleHandleSplitterHandle: public QSplitterHandle {
        Q_OBJECT
    public:
        JKQTEVisibleHandleSplitterHandle(Qt::Orientation orientation, QSplitter * parent=nullptr);
        /** \brief switches the decoration of the handle on or off (decoration is a roughed up surface area) */
        void setDecorated(bool enabled);
        /** \brief indicates whether the decoration of the handle is on or off (decoration is a roughed up surface area) */
        bool decorated() const;
        /** \brief switches the hover effect of the handle on or off (hover effect highlights the handle when the mouse hovers over it) */
        void setHoverEffect(bool enabled);
        /** \brief indicates whether the hover effect of the handle is on or off (hover effect highlights the handle when the mouse hovers over it) */
        bool hoverEffect() const;
        /** \brief sets the width of the handle */
        void setGripWidth(int width);
        /** \brief the width of the handle */
        int gripWidth() const;
    protected:
        virtual void leaveEvent(QEvent* event);
        virtual void enterEvent(QEvent* event);
        virtual void paintEvent(QPaintEvent* event);
        int m_gripHeight;
        bool m_inside;
        bool m_lightup;
        bool m_drawGrip;
};

#endif // JKQTEVISIBLEHANDLESPLITTER_H
