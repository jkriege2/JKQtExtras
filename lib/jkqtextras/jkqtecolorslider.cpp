/*
    Copyright (c) 2019 Jan W. Krieger (<jan@jkrieger.de>)

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

#include "jkqtecolorslider.h"
#include <QtGui>
#include <QtCore>


JKQTEColorSlider::JKQTEColorSlider(QWidget *parent):
    QSlider(parent)
{
    setColorMode(HueSlider);
}

JKQTEColorSlider::JKQTEColorSlider(Qt::Orientation orientation, QWidget *parent):
    QSlider(parent)
{
    setOrientation(orientation);
}

JKQTEColorSlider::SliderMode JKQTEColorSlider::colorMode() const
{
    return m_mode;
}

QColor JKQTEColorSlider::modifiedColor(QColor colorIn) const
{
    QColor color=colorIn;
    switch(m_mode) {
    case HueSlider:
        {
            int h,s,v;
            colorIn.getHsv(&h,&s,&v);
            color.setHsv(value(), s, v);
        }
        break;
    case RedSlider:
        color.setRed(value());
        break;
    case GreenSlider:
        color.setGreen(value());
        break;
    case BlueSlider:
        color.setBlue(value());
        break;
    case GreySlider:
        color.setRgb(value(), value(), value());
        break;
    }
    return color;
}

QSize JKQTEColorSlider::minimumSizeHint() const
{
    return QSlider::minimumSizeHint();
}

QSize JKQTEColorSlider::sizeHint() const
{
    return QSlider::sizeHint();
}

void JKQTEColorSlider::setColorMode(JKQTEColorSlider::SliderMode mode)
{
    m_mode=mode;
    switch(mode) {
    case HueSlider:
        setRange(0,360);
        break;
    default:
        setRange(0,255);
        break;
    }

    update();
}

void JKQTEColorSlider::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    QImage img;

    switch(m_mode) {
        case HueSlider:
            {
                int h,s,v;
                img=QImage(361, 1, QImage::Format_ARGB32);
                QColor("red").getHsv(&h,&s,&v);
                qDebug()<<h<<s<<v;
                QColor color("red");
                for (int i=0; i<img.width(); i++) {
                    color.setHsv(i, s, v);
                    img.setPixel(i, 0, color.rgba());
                }
            }
            break;
        case RedSlider:
            {
                img=QImage(255, 1, QImage::Format_ARGB32);
                QColor color("black");
                for (int i=0; i<img.width(); i++) {
                    color.setRed(i);
                    img.setPixel(i, 0, color.rgba());
                }
            }
            break;
        case GreenSlider:
            {
                img=QImage(255, 1, QImage::Format_ARGB32);
                QColor color("black");
                for (int i=0; i<img.width(); i++) {
                    color.setGreen(i);
                    img.setPixel(i, 0, color.rgba());
                }
            }
            break;
        case BlueSlider:
            {
                img=QImage(255, 1, QImage::Format_ARGB32);
                QColor color("black");
                for (int i=0; i<img.width(); i++) {
                    color.setBlue(i);
                    img.setPixel(i, 0, color.rgba());
                }
            }
            break;
        case GreySlider:
            {
                img=QImage(255, 1, QImage::Format_ARGB32);
                QColor color("black");
                for (int i=0; i<img.width(); i++) {
                    color.setRgb(i,i,i);
                    img.setPixel(i, 0, color.rgba());
                }
            }
            break;
    }

    const int markerSize=qMax(10, qMin(10, height()/3));
    if (orientation()==Qt::Horizontal) {
        const int sliderPos=(value()-minimum())*width()/(maximum()-minimum());
        QPainterPath path;
        path.moveTo(sliderPos-markerSize/2, 0);
        path.lineTo(sliderPos+markerSize/2, 0);
        path.lineTo(sliderPos, markerSize/2);
        path.lineTo(sliderPos, height()-markerSize/2);
        path.lineTo(sliderPos+markerSize/2, height());
        path.lineTo(sliderPos-markerSize/2, height());
        path.lineTo(sliderPos, height()-markerSize/2);
        path.lineTo(sliderPos, markerSize/2);
        path.closeSubpath();
        painter.drawImage(QRect(0,0,width(),height()), img);
        painter.fillPath(path, QBrush("black"));
    } else {
        QTransform transform;
        transform.rotate(90);
        painter.drawImage(QRect(0,0,width(),height()), img.transformed(transform));
        const int sliderPos=height()-(value()-minimum())*height()/(maximum()-minimum());
        QPainterPath path;
        path.moveTo(0, sliderPos-markerSize/2);
        path.lineTo(0, sliderPos+markerSize/2);
        path.lineTo(markerSize/2, sliderPos);
        path.lineTo(width()-markerSize/2, sliderPos);
        path.lineTo(width(), sliderPos+markerSize/2);
        path.lineTo(width(), sliderPos-markerSize/2);
        path.lineTo(width()-markerSize/2, sliderPos);
        path.lineTo(markerSize/2, sliderPos);
        path.closeSubpath();
        painter.fillPath(path, QBrush("black"));
    }

    ev->accept();
}
