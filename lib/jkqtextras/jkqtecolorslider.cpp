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
    QSlider(parent),
    m_baseColor(defaultBaseColor(HueSlider)),
    m_indicatorBrush(QColor("black")),
    m_indicatorPen(QColor("white")),
    m_indicatorStyle(DoubleArrowIndicator)
{
    setSliderMode(HueSlider);
    connect(this, &QSlider::valueChanged, this, &JKQTEColorSlider::baseSliderChanged);
}

JKQTEColorSlider::JKQTEColorSlider(Qt::Orientation orientation, QWidget *parent):
    JKQTEColorSlider(parent)
{
    setOrientation(orientation);
}

JKQTEColorSlider::JKQTEColorSlider(JKQTEColorSlider::SliderMode mode, QWidget *parent):
    JKQTEColorSlider(parent)
{
    setSliderMode(mode);
}

JKQTEColorSlider::JKQTEColorSlider(JKQTEColorSlider::SliderMode mode, Qt::Orientation orientation, QWidget *parent):
    JKQTEColorSlider(orientation, parent)
{
    setSliderMode(mode);
}

JKQTEColorSlider::SliderMode JKQTEColorSlider::sliderMode() const
{
    return m_mode;
}

JKQTEColorSlider::IndicatorStyle JKQTEColorSlider::indicatorStyle() const
{
    return m_indicatorStyle;
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
    case SaturationSlider:
        {
            int h,s,v;
            colorIn.getHsv(&h,&s,&v);
            color.setHsv(h, value(), v);
        }
        break;
    case ValueSlider:
        {
            int h,s,v;
            colorIn.getHsv(&h,&s,&v);
            color.setHsv(h, s, value());
        }
        break;
    case TransparencySlider:
        color.setAlpha(value());
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

QColor JKQTEColorSlider::modifiedColor() const
{
    return modifiedColor(baseColor());
}

QColor JKQTEColorSlider::baseColor() const
{
    return m_baseColor;
}

const QBrush &JKQTEColorSlider::indicatorBrush() const
{
    return m_indicatorBrush;
}

const QPen &JKQTEColorSlider::indicatorPen() const
{
    return m_indicatorPen;
}

QBrush &JKQTEColorSlider::indicatorBrush()
{
    return m_indicatorBrush;
}

QPen &JKQTEColorSlider::indicatorPen()
{
    return m_indicatorPen;
}

void JKQTEColorSlider::setIndicatorBrush(const QBrush &b)
{
    m_indicatorBrush=b;
    update();
}

void JKQTEColorSlider::setIndicatorPen(const QPen &p)
{
    m_indicatorPen=p;
    update();
}

void JKQTEColorSlider::setIndicatorStyle(JKQTEColorSlider::IndicatorStyle s)
{
    m_indicatorStyle=s;
    update();
}

QSize JKQTEColorSlider::minimumSizeHint() const
{
    return QSlider::minimumSizeHint();
}

QSize JKQTEColorSlider::sizeHint() const
{
    return QSlider::sizeHint();
}

void JKQTEColorSlider::setSliderMode(JKQTEColorSlider::SliderMode mode)
{
    const bool hadDefaultBaseColor=(baseColor()==defaultBaseColor(m_mode));
    m_mode=mode;
    switch(mode) {
    case HueSlider:
        setRange(0,360);
        break;
    default:
        setRange(0,255);
        break;
    }
    if (hadDefaultBaseColor) setBaseColor(defaultBaseColor(m_mode));

    update();
    setValue(value());
    baseSliderChanged(value());
}

void JKQTEColorSlider::setBaseColor(QColor baseColor)
{
    m_baseColor=baseColor;
    update();
    baseSliderChanged(value());
}

void JKQTEColorSlider::baseSliderChanged(int /*value*/)
{
    emit colorChanged(modifiedColor());
}

QColor JKQTEColorSlider::defaultBaseColor(JKQTEColorSlider::SliderMode mode)
{
    switch(mode) {
    case HueSlider:
    case SaturationSlider:
    case ValueSlider:
        return QColor("red");
    case RedSlider:
    case GreenSlider:
    case BlueSlider:
    case GreySlider:
        return QColor("black");
    case TransparencySlider:
        return QColor("white");
    }
}

void JKQTEColorSlider::paintEvent(QPaintEvent *ev)
{
    static QImage imgBack(16,16,QImage::Format_ARGB32);
    static bool hasImgBack=false;
    if (!hasImgBack) {
        imgBack.fill(QColor("transparent"));
        const int sqSize=8;
        for (int y=0; y<imgBack.height(); y++) {
            for (int x=0; x<imgBack.width(); x++) {
                if (y%sqSize<sqSize/2) {
                    if (x%sqSize<sqSize/2) imgBack.setPixel(x,y,QColor("black").rgb());
                } else {
                    if (x%sqSize>=sqSize/2) imgBack.setPixel(x,y,QColor("black").rgb());
                }
            }
        }
        hasImgBack=true;
    }

    QPainter painter(this);
    QBrush bback;
    bback.setTexture(QPixmap::fromImage(imgBack));
    bback.setStyle(Qt::TexturePattern);
    painter.fillRect(QRect(0,0,width(),height()), bback);

    QImage img;

    switch(m_mode) {
        case HueSlider:
            {
                int h,s,v;
                img=QImage(361, 1, QImage::Format_ARGB32);
                baseColor().getHsv(&h,&s,&v);
                QColor color(baseColor());
                for (int i=0; i<img.width(); i++) {
                    color.setHsv(i, s, v);
                    img.setPixel(i, 0, color.rgba());
                }
            }
            break;
        case SaturationSlider:
            {
                int h,s,v;
                img=QImage(256, 1, QImage::Format_ARGB32);
                baseColor().getHsv(&h,&s,&v);
                QColor color(baseColor());
                for (int i=0; i<img.width(); i++) {
                    color.setHsv(h, i, v);
                    img.setPixel(i, 0, color.rgba());
                }
            }
            break;
        case ValueSlider:
            {
                int h,s,v;
                img=QImage(256, 1, QImage::Format_ARGB32);
                baseColor().getHsv(&h,&s,&v);
                QColor color(baseColor());
                for (int i=0; i<img.width(); i++) {
                    color.setHsv(h, s, i);
                    img.setPixel(i, 0, color.rgba());
                }
            }
            break;
        case RedSlider:
            {
                img=QImage(256, 1, QImage::Format_ARGB32);
                QColor color(baseColor());
                for (int i=0; i<img.width(); i++) {
                    color.setRed(i);
                    img.setPixel(i, 0, color.rgba());
                }
            }
            break;
        case GreenSlider:
            {
                img=QImage(256, 1, QImage::Format_ARGB32);
                QColor color(baseColor());
                for (int i=0; i<img.width(); i++) {
                    color.setGreen(i);
                    img.setPixel(i, 0, color.rgba());
                }
            }
            break;
        case BlueSlider:
            {
                img=QImage(256, 1, QImage::Format_ARGB32);
                QColor color(baseColor());
                for (int i=0; i<img.width(); i++) {
                    color.setBlue(i);
                    img.setPixel(i, 0, color.rgba());
                }
            }
            break;
        case GreySlider:
            {
                img=QImage(255, 1, QImage::Format_ARGB32);
                QColor color(baseColor());
                for (int i=0; i<img.width(); i++) {
                    color.setRgb(i,i,i);
                    img.setPixel(i, 0, color.rgba());
                }
            }
            break;
        case TransparencySlider:
            {
                img=QImage(255, 1, QImage::Format_ARGB32);
                QColor color(baseColor());
                for (int i=0; i<img.width(); i++) {
                    color.setAlpha(i);
                    img.setPixel(i, 0, color.rgba());
                }
            }
            break;
    }

    const int markerSize=qMax(10, qMin(10, height()/3));
    if (orientation()==Qt::Horizontal) {
        const int sliderPos=(value()-minimum())*width()/(maximum()-minimum());
        QPainterPath path;
        if (indicatorStyle()==DoubleArrowIndicator) {
            path.moveTo(sliderPos-markerSize/2, 0);
            path.lineTo(sliderPos+markerSize/2, 0);
            path.lineTo(sliderPos, markerSize/2);
            path.lineTo(sliderPos, height()-markerSize/2);
            path.lineTo(sliderPos+markerSize/2, height());
            path.lineTo(sliderPos-markerSize/2, height());
            path.lineTo(sliderPos, height()-markerSize/2);
            path.lineTo(sliderPos, markerSize/2);
            path.closeSubpath();
        } else if (indicatorStyle()==CircleIndicator) {
            const int d=qMin(16, qMin(width(), height())/2);
            path.addEllipse(QPointF(sliderPos, height()/2), d/2, d/2);
        }
        painter.drawImage(QRect(0,0,width(),height()), img);
        painter.fillPath(path, m_indicatorBrush);
        painter.setPen(m_indicatorPen);
        painter.drawPath(path);
    } else {
        QTransform transform;
        transform.rotate(90);
        painter.drawImage(QRect(0,0,width(),height()), img.transformed(transform));
        const int sliderPos=height()-(value()-minimum())*height()/(maximum()-minimum());
        QPainterPath path;
        if (indicatorStyle()==DoubleArrowIndicator) {
            path.moveTo(0, sliderPos-markerSize/2);
            path.lineTo(0, sliderPos+markerSize/2);
            path.lineTo(markerSize/2, sliderPos);
            path.lineTo(width()-markerSize/2, sliderPos);
            path.lineTo(width(), sliderPos+markerSize/2);
            path.lineTo(width(), sliderPos-markerSize/2);
            path.lineTo(width()-markerSize/2, sliderPos);
            path.lineTo(markerSize/2, sliderPos);
            path.closeSubpath();
        } else if (indicatorStyle()==CircleIndicator) {
            const int d=qMin(16, qMin(width(), height())/2);
            path.addEllipse(QPointF(width()/2, sliderPos), d/2, d/2);
        }
        painter.fillPath(path, m_indicatorBrush);
        painter.setPen(m_indicatorPen);
        painter.drawPath(path);
    }

    ev->accept();
}
