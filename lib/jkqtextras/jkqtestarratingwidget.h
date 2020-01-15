/*
    Copyright (c) 2013-2020 Jan W. Krieger (<jan@jkrieger.de>)

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

#ifndef JKQTESTARRATINGWIDGET_H
#define JKQTESTARRATINGWIDGET_H

#include <QWidget>
#include <QIcon>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QFrame>
#include "jkqtextras_imexport.h"

/*! \brief a rating widget which displays five stars where the user may select how many are selected
    \ingroup JKQtExtrasWidgetsLabels

    Screenshot:
    \image html JKQTEStarRatingWidget.png

    Basic usage is simple:

    \snippet jkqtextras_test/testmainwindow.cpp Example: JKQTEStarRatingWidget

    You can set the images/icons to be used for present/unpresent stars and the limiter to the
    left that allows to set rating 0 when clicked:
        - setStarImage()
        - setDarkStarImage()
        - setNoStarImage()
    .

*/
class JKQTEXTRAS_LIB_EXPORT JKQTEStarRatingWidget : public QFrame {
        Q_OBJECT
        Q_PROPERTY(int data READ rating WRITE setRating )
        Q_PROPERTY(int rating READ rating WRITE setRating USER true)
        Q_PROPERTY(QPixmap darkStarImage READ darkStarImage WRITE setDarkStarImage USER true)
        Q_PROPERTY(QPixmap starImage READ starImage WRITE setStarImage USER true)
        Q_PROPERTY(QPixmap noStarImage READ noStarImage WRITE setNoStarImage USER true)
    public:
        /** Default constructor */
        JKQTEStarRatingWidget(QWidget* parent=NULL);
        /** Default destructor */
        virtual ~JKQTEStarRatingWidget();
        /** \brief returns the current rating (between 0 and maximum() ) */
        int rating() const;
        /** \brief returns the current maximum rating */
        int maximum() const;
        /** \brief the pixmap to use for a selected star */
        QPixmap starImage() const;
        /** \brief the pixmap to use for no stars at all (rating() \c ==0 ) */
        QPixmap noStarImage() const;
        /** \brief the pixmap to use for an unselected star */
        QPixmap darkStarImage() const;

    public slots:
        /** \brief sets the pixmap to use for a selected star */
        void setStarImage(const QPixmap &starImage);
        /** \brief sets the pixmap to use for no stars at all (rating() \c ==0 ) */
        void setNoStarImage(const QPixmap &noStarImage);
        /** \brief sets the pixmap to use for an unselected star */
        void setDarkStarImage(const QPixmap &darkStarImage);
        /** \brief sets the current rating (between 0 and maximum() ) */
        void setRating(int value);
        /** \brief sets the current maximum rating */
        void setMaximum(int value);
        /** \brief sets the frame style of the widget (see <a href="https://doc.qt.io/qt-5/qframe.html#setFrameStyle">QFrame::setFrameStyle()</a>) */
        void setFrameStyle(int);
        /** \brief sets the frame shape of the widget (see <a href="https://doc.qt.io/qt-5/qframe.html#setFrameShape">QFrame::setFrameShape()</a>) */
        void setFrameShape(Shape);
        /** \brief sets the frame shadow of the widget (see <a href="https://doc.qt.io/qt-5/qframe.html#setFrameShadow">QFrame::setFrameShadow()</a>) */
        void setFrameShadow(Shadow);
        /** \brief sets the frame line width of the widget (see <a href="https://doc.qt.io/qt-5/qframe.html#setLineWidth">QFrame::setLineWidth()</a>) */
        void setLineWidth(int);
        /** \brief sets the frame mid line width of the widget (see <a href="https://doc.qt.io/qt-5/qframe.html#setMidLineWidth">QFrame::setMidLineWidth()</a>) */
        void setMidLineWidth(int);
        /** \brief sets the frame rectangle of the widget (see <a href="https://doc.qt.io/qt-5/qframe.html#setFrameRect">QFrame::setFrameRect()</a>) */
        void setFrameRect(const QRect &);
    signals:
        /** \brief signal emitted when the rating changes */
        void ratingChanged(int rating);
    protected:
        QPixmap m_starImage;
        QPixmap m_noStarImage;
        QPixmap m_darkStarImage;
        int m_rating;
        int m_maximum;
        void setWidgetSizes();
        virtual void paintEvent ( QPaintEvent * event );
        virtual void mouseReleaseEvent ( QMouseEvent * event );
    private:
};

#endif // JKQTESTARRATINGWIDGET_H
