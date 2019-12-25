/*
    Copyright (c) 2013-2019 Jan W. Krieger (<jan@jkrieger.de>)

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


#include "jkqtestarratingwidget.h"
#include <QPainter>
#include <iostream>

JKQTEStarRatingWidget::JKQTEStarRatingWidget(QWidget* parent):
    QFrame(parent)
{
    Q_INIT_RESOURCE(jkqtestarratingwidget);
    m_starImage=    QPixmap(":/jkqtestarratingwidget/star.png");
    m_darkStarImage=QPixmap(":/jkqtestarratingwidget/darkstar.png");
    m_noStarImage=  QPixmap(":/jkqtestarratingwidget/nostar.png");
    m_rating=0;
    m_maximum=5;
    setWidgetSizes();
    setFocusPolicy(Qt::ClickFocus);
    setFrameStyle(QFrame::Box | QFrame::Plain);
    setLineWidth(1);
    setMidLineWidth(0);
}

JKQTEStarRatingWidget::~JKQTEStarRatingWidget()
{
    //dtor
}

int JKQTEStarRatingWidget::rating() const {
    return m_rating;
}

void JKQTEStarRatingWidget::setRating(int value) {
    m_rating=qBound(0,value,m_maximum);
    setWidgetSizes();
    repaint();
    emit ratingChanged(rating());
}

int JKQTEStarRatingWidget::maximum() const {
    return m_maximum;
}

void JKQTEStarRatingWidget::setMaximum(int value) {
    m_maximum=value;
    m_rating=qBound(0,rating(),m_maximum);
    setWidgetSizes();
    repaint();
    emit ratingChanged(rating());
}

void JKQTEStarRatingWidget::setWidgetSizes() {
    QSize s((m_starImage.width()+2)*m_maximum+m_noStarImage.width()+4+2*frameWidth(), qMax(m_starImage.height(), m_noStarImage.height())+4+2*frameWidth());
    setMaximumSize(s);
    setMinimumSize(s);
    resize(s);
}

void JKQTEStarRatingWidget::paintEvent(QPaintEvent * event) {
    QFrame::paintEvent(event);
    QPainter painter(this);
    int startx=2+frameWidth();
    int starty=2+frameWidth();
    painter.drawPixmap(startx, starty,m_noStarImage);
    int x=m_noStarImage.width()+startx;
    //QPen p(palette().color(QPalette::Dark));
    //painter.setPen(p);
    //painter.drawRect(0,0,width()-1, height()-1);
    for (int i=1; i<=m_maximum; i++) {
        if (m_rating>=i) painter.drawPixmap(x+1,starty,m_starImage);
        else painter.drawPixmap(x+1,starty,m_darkStarImage);
        x=x+m_starImage.width()+2;
    }
    /*if (hasFocus()) {
        p.setStyle(Qt::DotLine);
        p.setColor(palette().color(QPalette::Light));
        painter.setPen(p);
        painter.drawRect(0,0,width()-1, height()-1);
    }*/
}

void JKQTEStarRatingWidget::mouseReleaseEvent(QMouseEvent * event) {
    if (event->button()==Qt::LeftButton) {
        int n_rating=0;
        //int startx=2+frameWidth();
        int starty=2+frameWidth();
        //std::cout<<"button(x="<<event->x()<<", "<<event->y()<<")\n";
        if (event->x()<=m_noStarImage.width()+starty) n_rating=0;
        else {
            int x=m_noStarImage.width()+starty;//+starImage.width()+1;
            n_rating=(event->x()-x)/(m_starImage.width()+2)+1;
        }
        event->accept();
        //std::cout<<"new rating="<<n_rating<<"\n";
        setRating(n_rating);
    }

}


void JKQTEStarRatingWidget::setFrameStyle(int value) {
    QFrame::setFrameStyle(value);
    setWidgetSizes();
    repaint();
}

void JKQTEStarRatingWidget::setFrameShape(Shape value) {
    QFrame::setFrameShape(value);
    setWidgetSizes();
    repaint();
}

void JKQTEStarRatingWidget::setFrameShadow(Shadow value) {
    QFrame::setFrameShadow(value);
    setWidgetSizes();
    repaint();
}

void JKQTEStarRatingWidget::setLineWidth(int value) {
    QFrame::setLineWidth(value);
    setWidgetSizes();
    repaint();
}

void JKQTEStarRatingWidget::setMidLineWidth(int value) {
    QFrame::setMidLineWidth(value);
    setWidgetSizes();
    repaint();
}

void JKQTEStarRatingWidget::setFrameRect(const QRect & value) {
    QFrame::setFrameRect(value);
    setWidgetSizes();
    repaint();
}

QPixmap JKQTEStarRatingWidget::darkStarImage() const
{
    return m_darkStarImage;
}

void JKQTEStarRatingWidget::setDarkStarImage(const QPixmap &darkStarImage)
{
    m_darkStarImage = darkStarImage;
    setWidgetSizes();
    repaint();
}

QPixmap JKQTEStarRatingWidget::noStarImage() const
{
    return m_noStarImage;
}

void JKQTEStarRatingWidget::setNoStarImage(const QPixmap &noStarImage)
{
    m_noStarImage = noStarImage;
    setWidgetSizes();
    repaint();
}

QPixmap JKQTEStarRatingWidget::starImage() const
{
    return m_starImage;
}

void JKQTEStarRatingWidget::setStarImage(const QPixmap &starImage)
{
    m_starImage = starImage;
    setWidgetSizes();
    repaint();
}



