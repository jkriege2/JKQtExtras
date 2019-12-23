#include "jkqtecolorsampler.h"
#include <QPainter>

JKQTEColorSampler::JKQTEColorSampler(QWidget *parent) :
    QWidget(parent),
    m_color("black"),
    m_samplerMode(RectangleSampler)
{

}

QColor JKQTEColorSampler::color() const
{
    return m_color;
}

JKQTEColorSampler::SamplerMode JKQTEColorSampler::samplerMode() const
{
    return m_samplerMode;
}

QSize JKQTEColorSampler::minimumSizeHint() const
{
    return QSize(4,4);
}

QSize JKQTEColorSampler::sizeHint() const
{
    return QSize(16,16);
}

void JKQTEColorSampler::setColor(QColor col)
{
    m_color=col;
    update();
}

void JKQTEColorSampler::setSamplerMode(JKQTEColorSampler::SamplerMode m)
{
    m_samplerMode=m;
    update();
}

void JKQTEColorSampler::paintEvent(QPaintEvent */*ev*/)
{
    QPainter p(this);
    QPainterPath path;
    if (m_samplerMode==RectangleSampler) {
        path.addRect(QRect(0,0,width()-1,height()-1));
    } else if (m_samplerMode==CircleSampler) {
        int d=qMin(width(),height());
        path.addEllipse((width()-d)/2,(height()-d)/2,d-1,d-1);
    }
    p.fillPath(path, QBrush(m_color));
    p.setPen(palette().windowText().color());
    p.drawPath(path);
}
