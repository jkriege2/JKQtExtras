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

#include "jkqtevisiblehandlesplitter.h"
#include <QtGui>
#include <QtCore>

JKQTEVisibleHandleSplitterHandle::JKQTEVisibleHandleSplitterHandle(Qt::Orientation orientation, QSplitter * parent) :
    QSplitterHandle(orientation, parent)
{
    m_gripHeight=96;
    m_inside=false;
    m_lightup=true;
    m_drawGrip=true;
    setMouseTracking(true);
}


void JKQTEVisibleHandleSplitterHandle::paintEvent(QPaintEvent *event)
{

    QBrush back=QBrush(palette().brush(QPalette::Light));
    QPen lines=palette().color(QPalette::Mid);
    if (m_lightup && m_inside) {
        QPainter painter(this);
        back= QBrush(palette().brush(QPalette::Highlight));
        painter.fillRect(event->rect(), back);
        back.setColor(back.color().lighter());
        lines.setColor(back.color().darker());
    } else {
        //painter.fillRect(event->rect(), QBrush(palette().brush(QPalette::Window)));
        QSplitterHandle::paintEvent(event);
    }
    QPainter painter(this);
    if (m_drawGrip) {
        if (orientation() == Qt::Horizontal) {// WIDGET | WIDGET | WIDGET
            QRect r=event->rect();
            QRect grip=QRect(r.left(), r.center().y()-m_gripHeight/2, r.width(), m_gripHeight);
            painter.fillRect(grip, back);
            painter.setPen(lines);
            for (int i=grip.top(); i<grip.bottom(); i+=2) {
                painter.drawLine(grip.left(), i, grip.right(), i);
            }
        } else {
            // WIDGET
            // ------
            // WIDGET
            // ------
            // WIDGET
            QRect r=event->rect();
            QRect grip=QRect(r.center().x()-m_gripHeight/2, r.top(), m_gripHeight, r.height());
            painter.fillRect(grip, back);
            painter.setPen(lines);
            for (int i=grip.left(); i<grip.right(); i+=2) {
                painter.drawLine(i, grip.top(), i, grip.bottom());
            }
        }
    }
}

void JKQTEVisibleHandleSplitterHandle::leaveEvent(QEvent* /*event*/) {
    m_inside=false;
    repaint();
}

void JKQTEVisibleHandleSplitterHandle::enterEvent(QEvent* /*event*/) {
    m_inside=true;
    repaint();
}







JKQTEVisibleHandleSplitter::JKQTEVisibleHandleSplitter(Qt::Orientation orientation, QWidget *parent) :
    QSplitter(orientation, parent)
{
    setChildrenCollapsible(false);
}

JKQTEVisibleHandleSplitter::JKQTEVisibleHandleSplitter(QWidget *parent) :
    QSplitter(parent)
{
}

bool JKQTEVisibleHandleSplitter::decorated() const
{
    for (int i=0;i<count(); i++) {
        JKQTEVisibleHandleSplitterHandle* h=qobject_cast<JKQTEVisibleHandleSplitterHandle*>(handle(i));
        if (h) return h->decorated();
    }
    return false;
}

bool JKQTEVisibleHandleSplitter::hoverEffect() const
{
    for (int i=0;i<count(); i++) {
        JKQTEVisibleHandleSplitterHandle* h=qobject_cast<JKQTEVisibleHandleSplitterHandle*>(handle(i));
        if (h) return h->hoverEffect();
    }
    return false;
}

int JKQTEVisibleHandleSplitter::gripWidth() const
{
    for (int i=0;i<count(); i++) {
        JKQTEVisibleHandleSplitterHandle* h=qobject_cast<JKQTEVisibleHandleSplitterHandle*>(handle(i));
        if (h) return h->gripWidth();
    }
    return 0;
}

QSplitterHandle* JKQTEVisibleHandleSplitter::createHandle() {
    return new JKQTEVisibleHandleSplitterHandle(orientation(), this);
}

void JKQTEVisibleHandleSplitter::setDecorated(bool enabled) {
    for (int i=0;i<count(); i++) {
        JKQTEVisibleHandleSplitterHandle* h=qobject_cast<JKQTEVisibleHandleSplitterHandle*>(handle(i));
        if (h) h->setDecorated(enabled);
    }
}

void JKQTEVisibleHandleSplitter::setHoverEffect(bool enabled) {
    for (int i=0;i<count(); i++) {
        JKQTEVisibleHandleSplitterHandle* h=qobject_cast<JKQTEVisibleHandleSplitterHandle*>(handle(i));
        if (h) h->setHoverEffect(enabled);
    }
}
void JKQTEVisibleHandleSplitter::setGripWidth(int width) {
    for (int i=0;i<count(); i++) {
        JKQTEVisibleHandleSplitterHandle* h=qobject_cast<JKQTEVisibleHandleSplitterHandle*>(handle(i));
        if (h) h->setGripWidth(width);
    }
}

void JKQTEVisibleHandleSplitterHandle::setDecorated(bool enabled) { m_drawGrip=enabled; }

bool JKQTEVisibleHandleSplitterHandle::decorated() const { return m_drawGrip; }

void JKQTEVisibleHandleSplitterHandle::setHoverEffect(bool enabled) { m_lightup=enabled; }

void JKQTEVisibleHandleSplitterHandle::setGripWidth(int width) { m_gripHeight=width; }

int JKQTEVisibleHandleSplitterHandle::gripWidth() const { return m_gripHeight; }

bool JKQTEVisibleHandleSplitterHandle::hoverEffect() const { return m_lightup; }
