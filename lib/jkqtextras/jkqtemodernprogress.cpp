/*
    Copyright (c) 2008-2019 Jan W. Krieger (<jan@jkrieger.de>)

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

#include "jkqtemodernprogress.h"

#include <QPainter>
#include <QtGlobal>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtWidgets>
#else
#include <QtGui>
#endif
#include <QDebug>
#include <iostream>

JKQTEModernProgressWidget::JKQTEModernProgressWidget(QWidget *parent)
    : QWidget(parent),
    m_textDisplayMode(JKQTEModernProgressWidget::TextDisplayMode::NoText),
    m_suffix(""),
    m_precision(0),
    m_rangeMin(0),
    m_rangeMax(100),
    m_value(50),
    m_outerRadius(0.9),
    m_innerRadius(0.55),
    m_items(15),
    m_spinItem(0),
    m_smoothItems(75),
    m_smoothSpinItem(0),
    m_startColor(parent->palette().window().color().darker(150)),
    m_stopColor(QColor("darkslateblue")),
    m_indicatorBackgroundColor(parent->palette().window().color().darker(150)),
    m_indicatorColor(QColor("darkslateblue")),
    m_textColor(parent->palette().text().color()),
    m_innerCircleBackgroundColor(parent->palette().window().color()),
    m_nonBackgroundRange(0.75),
    m_spin(false),
    m_spinInterval(20),
    m_doRepaint(true),
    m_darkCircleBorder(true),
    m_mode(JKQTEModernProgressWidget::Strokes)
{
  resize(64, 64);
  setSpin(false);
}

JKQTEModernProgressWidget::~JKQTEModernProgressWidget() {
}

QString JKQTEModernProgressWidget::suffix() const {
    return m_suffix;
}

int JKQTEModernProgressWidget::precision() const {
    return m_precision;
}

double JKQTEModernProgressWidget::minimum() const {
    return m_rangeMin;
}

double JKQTEModernProgressWidget::maximum() const {
    return m_rangeMax;
}

double JKQTEModernProgressWidget::value() const {
    return m_value;
}

double JKQTEModernProgressWidget::outerRadius() const {
    return m_outerRadius;
}

double JKQTEModernProgressWidget::innerRadius() const {
    return m_innerRadius;
}

QColor JKQTEModernProgressWidget::indicatorBackgroundColor() const {
    return m_indicatorBackgroundColor;
}

QColor JKQTEModernProgressWidget::innerCircleBackgroundColor() const
{
    return m_innerCircleBackgroundColor;
}

QColor JKQTEModernProgressWidget::startColor() const {
    return m_startColor;
}

QColor JKQTEModernProgressWidget::stopColor() const {
    return m_stopColor;
}

QColor JKQTEModernProgressWidget::indicatorColor() const {
  return m_indicatorColor;
}

double JKQTEModernProgressWidget::nonBackgroundRange() const {
  return m_nonBackgroundRange;
}

bool JKQTEModernProgressWidget::spin() const {
    return m_spin;
}

int JKQTEModernProgressWidget::spinInterval() const {
    return m_spinInterval;
}

int JKQTEModernProgressWidget::items() const {
    return m_items;
}

JKQTEModernProgressWidget::Mode JKQTEModernProgressWidget::mode() const {
  return m_mode;
}

QColor JKQTEModernProgressWidget::textColor() const {
    return m_textColor;
}

JKQTEModernProgressWidget::TextDisplayMode JKQTEModernProgressWidget::textDisplayMode() const {
  return m_textDisplayMode;
}

void JKQTEModernProgressWidget::setSuffix(QString s) {
  m_suffix = s;
  updateWidget();
}

void JKQTEModernProgressWidget::setPrecision(int p) {
  m_precision = p;
  updateWidget();
}

void JKQTEModernProgressWidget::setTextColor(QColor col) {
  m_textColor = col;
  updateWidget();
}

void JKQTEModernProgressWidget::setOuterRadius(int val) {
  m_outerRadius = val;
  updateWidget();
}

void JKQTEModernProgressWidget::setInnerRadius(int val) {
  m_innerRadius = val;
  updateWidget();
}

void JKQTEModernProgressWidget::setNonBackgroundRange(double val) {
  m_nonBackgroundRange = val;
  updateWidget();
}

void JKQTEModernProgressWidget::setStartColor(QColor col) {
  m_startColor = col;
  updateWidget();
}

void JKQTEModernProgressWidget::setStopColor(QColor col) {
  m_stopColor = col;
  updateWidget();
}

void JKQTEModernProgressWidget::setIndicatorColor(QColor col) {
  m_indicatorColor = col;
  updateWidget();
}

void JKQTEModernProgressWidget::setBackgroundColor(QColor col) {
  m_indicatorBackgroundColor = col;
  updateWidget();
}

void JKQTEModernProgressWidget::setInnerCircleBackgroundColor(QColor col)
{
  m_innerCircleBackgroundColor=col;
  updateWidget();
}

void JKQTEModernProgressWidget::updateWidget() {
  m_doRepaint = true;
  update();
}

int JKQTEModernProgressWidget::getSmoothItems(int items)
{
    if (items>50) {
        return items;
    } else {
        int res=items;
        while (res<50) res+=items;
        return res;
    }
}

void JKQTEModernProgressWidget::setSpin(bool enabled) {
  if (m_spin != enabled) {
    m_spin = enabled;
    if (enabled) {
      // timer.setInterval(m_spinInterval);
      // timer.start();
      m_spinItem = 0;
      m_smoothSpinItem=0;
      QTimer::singleShot(m_spinInterval, this, SLOT(doSpin()));
    } else {
      // timer.stop();
    }
  }
}

void JKQTEModernProgressWidget::setSpinInterval(int msec) {
  m_spinInterval = msec;
  timer.setInterval(msec);
}

void JKQTEModernProgressWidget::setItems(int i) {
  m_items = i;
  m_smoothItems=getSmoothItems(i);
  updateWidget();
}

void JKQTEModernProgressWidget::setMode(JKQTEModernProgressWidget::Mode m) {
  m_mode = m;
  updateWidget();
}

void JKQTEModernProgressWidget::setTextDisplayMode(
    JKQTEModernProgressWidget::TextDisplayMode m) {
  m_textDisplayMode = m;
  updateWidget();
}

void JKQTEModernProgressWidget::setMinimum(double val) {
  m_rangeMin = val;
  updateWidget();
}

void JKQTEModernProgressWidget::setMaximum(double val) {
  m_rangeMax = val;
  updateWidget();
}

void JKQTEModernProgressWidget::setValue(double val) {
  m_value = val;
  updateWidget();
}

void JKQTEModernProgressWidget::setRange(double min, double max) {
  m_rangeMin = min;
  m_rangeMax = max;
  updateWidget();
}

void JKQTEModernProgressWidget::doSpin() {
  bool doPaint=false;
  m_smoothSpinItem++;
  if (m_smoothSpinItem>=m_smoothItems) m_smoothSpinItem=0;
  if (m_smoothSpinItem%(m_smoothItems/m_items)==0) {
      m_spinItem++;
      if (m_spinItem >= m_items) m_spinItem = 0;
      doPaint=true;
  }
  if (doPaint || m_mode==Ring) {
      m_doRepaint = true;
      update();
  }
  if (m_spin) {
    QTimer::singleShot(m_spinInterval, this, SLOT(doSpin()));
  }
}

void JKQTEModernProgressWidget::resizeEvent(QResizeEvent *event) {
  m_doRepaint = true;
  QWidget::resizeEvent(event);
}

QColor linColor(QColor col1, QColor col2, double frac) {
  QColor cColor = col1;
  cColor.setRedF(col1.redF() + frac * (col2.redF() - col1.redF()));
  cColor.setGreenF(col1.greenF() + frac * (col2.greenF() - col1.greenF()));
  cColor.setBlueF(col1.blueF() + frac * (col2.blueF() - col1.blueF()));
  return cColor;
}

void JKQTEModernProgressWidget::paintEvent(QPaintEvent *event) {
  QWidget::paintEvent(event);
  QPixmap m_pix(width(), height());

  // if (m_doRepaint) {
  m_doRepaint = false;
  QPen pen;
  pen.setWidthF(1.0);

  double wid = qMin(height(), width());
  double displayFrac =
      (double)(m_value - m_rangeMin) / (double)(m_rangeMax - m_rangeMin);
  int currentItem =
      qMax(0, qMin(m_items, (int)round(displayFrac * (double)m_items)));
  int lastItem = round(m_nonBackgroundRange * (double)m_items);
  if (m_spin) {
    currentItem = m_spinItem;
  }
  if (!m_spin) {
    lastItem = currentItem;
  }

  QPointF center = QPointF(width() / 2.0, height() / 2.0);

  double rIn = wid / 2.0 * m_innerRadius;
  double rOut = wid / 2.0 * m_outerRadius;
  if (rIn > rOut)
    qSwap(rIn, rOut);

  //                           2*M_PI
  double strokeWidth = qMax(1.0, 6.283 * rIn / (1.75 * (double)m_items));
  double dAngle = 360.0 / (double)m_items;

  // m_pix.fill(this, 0, 0);
  m_pix.fill(Qt::transparent);

  QPainter painter(&m_pix);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.save();
  painter.setBrush(m_innerCircleBackgroundColor);
  painter.setPen(Qt::NoPen);
  painter.drawEllipse(center,rIn,rIn);
  painter.restore();

  if (m_mode == JKQTEModernProgressWidget::Strokes) {
    QPen strokePen = pen;
    strokePen.setWidthF(strokeWidth);
    strokePen.setCapStyle(Qt::RoundCap);
    strokePen.setJoinStyle(Qt::RoundJoin);
    painter.save();
    painter.translate(center);
    if (m_spin)
      painter.rotate(-dAngle * (double)currentItem);
    else
      painter.rotate(-180);
    for (int i = 0; i < m_items; i++) {
      strokePen.setColor(m_indicatorBackgroundColor);
      // double frac=(double)i/(double)(m_items-1.0);

      if (i < lastItem) {
        const double r = m_startColor.redF();
        const double g = m_startColor.greenF();
        const double b = m_startColor.blueF();
        const double re = m_stopColor.redF();
        const double ge = m_stopColor.greenF();
        const double be = m_stopColor.blueF();
        double f=1;
        if (m_spin) {
            f = (double)i / (m_nonBackgroundRange * (double)m_items);
            if (f > 1) f = 1.0;
            if (f < 0) f = 0;
            f = 1.0 - f;
        }
        QColor col;
        col.setRgbF(r + f * (re - r), g + f * (ge - g), b + f * (be - b));
        strokePen.setColor(col);
      }
      // if (fabs(frac-displayFrac)<=1.0/(double)m_items)
      // strokePen.setColor(m_indicatorColor);
      if (i == 0)
        strokePen.setColor(m_indicatorColor);
      painter.setPen(strokePen);
      painter.drawLine(QLineF(0, rIn, 0, rOut));
      painter.rotate(dAngle);
    }
    painter.restore();
  } else if (m_mode == JKQTEModernProgressWidget::Circles) {
    painter.save();
    painter.translate(center);
    if (m_spin)
      painter.rotate(-dAngle * (double)currentItem);
    else
      painter.rotate(-180);
    for (int i = 0; i < m_items; i++) {
      // double frac=(double)i/(double)(m_items-1.0);

      QColor col = m_indicatorBackgroundColor;

      if (i < lastItem) {
        const double r = m_startColor.redF();
        const double g = m_startColor.greenF();
        const double b = m_startColor.blueF();
        const double re = m_stopColor.redF();
        const double ge = m_stopColor.greenF();
        const double be = m_stopColor.blueF();
        double f=1;
        if (m_spin) {
            f = (double)i / (m_nonBackgroundRange * (double)m_items);
            if (f > 1) f = 1.0;
            if (f < 0) f = 0;
            f = 1.0 - f;
        }
        col.setRgbF(r + f * (re - r), g + f * (ge - g), b + f * (be - b));
      }
      // if (fabs(frac-displayFrac)<=1.0/(double)m_items)
      // strokePen.setColor(m_indicatorColor);
      if (i == 0)
        col = m_indicatorColor;
      QBrush circleBrush(col);
      QPen circlePen = QPen(col.darker(150));
      painter.setBrush(circleBrush);
      if (m_darkCircleBorder) {
        painter.setPen(circlePen);
      } else {
        painter.setPen(QColor(Qt::transparent));
      }
      double d = (rOut - rIn) / 3.0;
      painter.drawEllipse(QPointF(0, (rIn + rOut) / 2.0), d, d);
      painter.rotate(dAngle);
    }
    painter.restore();
  } else if (m_mode == JKQTEModernProgressWidget::Ring) {
    painter.save();
    QPainterPath pathBack;
    pathBack.setFillRule(Qt::OddEvenFill);
    pathBack.addEllipse(QPointF(0, 0), rOut, rOut);
    pathBack.addEllipse(QPointF(0, 0), rIn, rIn);

    QPainterPath path, path1, path2;
    path1.moveTo(QPointF(0, 0));
    if (m_spin) {
        const double a1=fmod(360.0 * (double)m_smoothSpinItem/(double)m_smoothItems*1.0, 360.0);
        const double a2=fmod(360.0 * (double)m_smoothSpinItem/(double)m_smoothItems*2.0, 360.0);
        path1.arcTo(-rOut, -rOut, 2.0*rOut, 2.0*rOut,a1,a2);
    } else {
        path1.arcTo(-rOut, -rOut, 2.0*rOut, 2.0*rOut,0, -1.0*displayFrac*360.0);
    }
    path2.setFillRule(Qt::OddEvenFill);
    path2.addEllipse(QPointF(0, 0),rOut,rOut);
    path2.addEllipse(QPointF(0, 0),rIn,rIn);
    path=path1.intersected(path2);

    painter.translate(center);
    if (m_spin) {
      //painter.rotate(-dAngle * (double)currentItem);
    } else {
      painter.rotate(-90);
    }

    // Draw the ring background
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_indicatorBackgroundColor);
    painter.drawPath(pathBack);

    // Draw the ring foreground
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_indicatorColor);
    painter.drawPath(path);

    painter.restore();
  } else if (m_mode == JKQTEModernProgressWidget::RoundedStrokeRing) {
      painter.save();
      QPainterPath pathBack;
      pathBack.setFillRule(Qt::OddEvenFill);
      pathBack.addEllipse(QPointF(0, 0), rOut, rOut);
      pathBack.addEllipse(QPointF(0, 0), rIn, rIn);

      const double rMid=(rIn+rOut)/2.0;
      QPainterPath path;

      if (m_spin) {
          const double a1=0;//;
          const double a2=fmod(360.0 * (double)m_smoothSpinItem/(double)m_smoothItems*1.0, 360.0);
          path.moveTo(QPointF(rMid, 0));
          path.arcTo(-rMid, -rMid, 2.0*rMid, 2.0*rMid,a1,a2);
      } else {
          path.moveTo(QPointF(rMid, 0));
          path.arcTo(-rMid, -rMid, 2.0*rMid, 2.0*rMid,0, -1.0*displayFrac*360.0);
      }

      painter.translate(center);
      if (m_spin) {
          painter.rotate(-fmod(360.0 * (double)m_smoothSpinItem/(double)m_smoothItems*1.0, 360.0));
      } else {
          painter.rotate(-90);
      }

      // Draw the ring background
      painter.setPen(Qt::NoPen);
      painter.setBrush(m_indicatorBackgroundColor);
      painter.drawEllipse(QPointF(0, 0), rOut, rOut);
      painter.setBrush(m_innerCircleBackgroundColor);
      painter.drawEllipse(QPointF(0, 0), rIn, rIn);

      // Draw the ring foreground
      QPen pe(m_indicatorColor, fabs(rOut-rIn));
      pe.setCapStyle(Qt::RoundCap);
      painter.setPen(pe);
      painter.setBrush(Qt::NoBrush);
      painter.drawPath(path);

      painter.restore();
  } else if (m_mode == JKQTEModernProgressWidget::GradientRing) {
      painter.save();
      QPainterPath path;
      path.setFillRule(Qt::OddEvenFill);
      path.addEllipse(QPointF(0, 0), rOut, rOut);
      path.addEllipse(QPointF(0, 0), rIn, rIn);

      painter.translate(center);
      if (m_spin)
          painter.rotate(-dAngle * (double)currentItem);
      else
          painter.rotate(-90);

      // Draw the ring background
      painter.setPen(Qt::NoPen);
      painter.setBrush(m_indicatorBackgroundColor);
      painter.drawPath(path);

      // Draw the ring foreground
      QConicalGradient gradient(QPointF(0, 0), 0.0);
      if (m_spin) {
          gradient.setColorAt(0.0, m_indicatorBackgroundColor);
          gradient.setColorAt(qMax(0.0, (double)lastItem / (double)m_items - 0.05),
                              m_indicatorColor);
          gradient.setColorAt((double)lastItem / (double)m_items,
                              m_indicatorBackgroundColor);
          painter.setBrush(gradient);
      } else {
          double gfrac = qMax(0.0, qMin(1.0, 1.0 - displayFrac));
          if ((fabs(gfrac) <= 0.02)) {
              painter.setBrush(QBrush(m_indicatorColor));
          } else if (fabs(gfrac) > 0.85) {
              QColor cColor = linColor(m_indicatorColor, m_indicatorBackgroundColor,
                                       (gfrac - 0.85) / 0.15);
              gradient.setColorAt(0.05, m_indicatorBackgroundColor);
              gradient.setColorAt(0.0, cColor);
              gradient.setColorAt(0.8, m_indicatorBackgroundColor);
              gradient.setColorAt(gfrac, cColor);
              painter.setBrush(gradient);
          } else if (fabs(gfrac) < 0.15) {
              QColor cColor =
                  linColor(m_indicatorColor, m_indicatorBackgroundColor, gfrac / 0.15);
              gradient.setColorAt(0.0, m_indicatorColor);
              gradient.setColorAt(gfrac / 2.0, cColor);
              gradient.setColorAt(gfrac, m_indicatorColor);
              painter.setBrush(gradient);
          } else {
              gradient.setColorAt(0.0, m_indicatorColor);
              gradient.setColorAt(0.05, m_indicatorBackgroundColor);
              gradient.setColorAt(qMax(0.0, gfrac - 0.05), m_indicatorBackgroundColor);
              gradient.setColorAt(qMin(1.0, gfrac), m_indicatorColor);
              painter.setBrush(gradient);
          }
      }
      painter.drawPath(path);
      painter.restore();
  }

  if (m_textDisplayMode != TextDisplayMode::NoText) {
    painter.save();
    QFont f = font();
    QString s = "";
    if (m_textDisplayMode == JKQTEModernProgressWidget::PercentText) {
      s = QString::number(100.0 * (double)(m_value - m_rangeMin) /
                              (double)(m_rangeMax - m_rangeMin),
                          'f', m_precision) +
          "%";
    } else {
      s = QString::number(m_value, 'f', m_precision) + m_suffix;
    }
    QRect bound = QFontMetrics(f).boundingRect("100%");
    double r = sqrt((bound.width() / 2.0) * (bound.width() / 2.0) +
                    (bound.height() / 2.0) * (bound.height() / 2.0));
    while ((f.pointSize() > 5) && (r > rIn)) {
      f.setPointSizeF(f.pointSizeF() - 0.5);
      bound = QFontMetrics(f).boundingRect("100%");
      r = sqrt((bound.width() / 2.0) * (bound.width() / 2.0) +
               (bound.height() / 2.0) * (bound.height() / 2.0));
    }
    bound = QFontMetrics(f).boundingRect(s);
    painter.setFont(f);
    painter.setPen(m_textColor);
    painter.drawText(width() / 2 - bound.width() / 2,
                     height() / 2 + QFontMetrics(f).ascent() / 2, s);
    painter.restore();
  }
  //}
  QPainter p(this);
  p.drawPixmap(QPoint(0, 0), m_pix);
}

JKQTEModernProgressDialog::JKQTEModernProgressDialog(QWidget *parent,
                                                     Qt::WindowFlags f)
    : QDialog(parent, f) {
  createWidgets();
}

JKQTEModernProgressDialog::JKQTEModernProgressDialog(
    const QString &labelText, const QString &cancelButtonText, QWidget *parent,
    Qt::WindowFlags f)
    : QDialog(parent, f) {
  createWidgets();
  setLabelText(labelText);
  setCancelButtonText(cancelButtonText);
}

JKQTEModernProgressDialog::~JKQTEModernProgressDialog() {

}

QString JKQTEModernProgressDialog::labelText() const {
    return label->text();
}

QString JKQTEModernProgressDialog::cancelButtonText() const {
  return cancel->text();
}

void JKQTEModernProgressDialog::setLabelText(const QString &t) {
  label->setText(t);
}

void JKQTEModernProgressDialog::addLongTextLine(const QString &t) {
  longmessage->setVisible(true);
  QTextCursor c = longmessage->textCursor();
  c.movePosition(QTextCursor::End);
  c.insertText("\n" + t);
}

void JKQTEModernProgressDialog::setCancelButtonText(const QString &t) {
  cancel->setText(t);
}

void JKQTEModernProgressDialog::setHasCancel(bool has) {
  cancel->setVisible(has);
}

void JKQTEModernProgressDialog::createWidgets() {
  setWindowTitle(tr("Progress"));
  setWindowIcon(QIcon());
  m_wasCancel = false;
  label = new QLabel(this);
  longmessage = new QTextEdit(this);
  longmessage->setVisible(false);
  progress = new JKQTEModernProgressWidget(this);
  progress->setMinimumSize(QSize(48, 48));
  cancel = new QPushButton(tr("Cancel"), this);
  connect(cancel, SIGNAL(clicked()), this, SLOT(cancelClicked()));

  QVBoxLayout *vbl = new QVBoxLayout;
  setLayout(vbl);
  QHBoxLayout *hbl = new QHBoxLayout;
  hbl->addWidget(progress);
  hbl->addWidget(label);
  hbl->addStretch();
  vbl->addLayout(hbl);
  vbl->addWidget(longmessage);
  hbl = new QHBoxLayout;
  hbl->addStretch();
  hbl->addWidget(cancel);
  vbl->addLayout(hbl);
  connect(&timerDelay, SIGNAL(timeout()), this, SLOT(open()));

  QRect desktopRect=QGuiApplication::primaryScreen()->availableGeometry();
  QRect widgetRect = rect();
  move(desktopRect.center() - widgetRect.center());
}

void JKQTEModernProgressDialog::showEvent(QShowEvent *event) {
  QDialog::showEvent(event);
  m_wasCancel = false;
  progress->setSpin(true);
}

void JKQTEModernProgressDialog::closeEvent(QCloseEvent *e) {
  timerDelay.stop();
  e->accept();
}

void JKQTEModernProgressDialog::openDelayed(int minimumDuration) {
  m_wasCancel = false;
  m_closedBeforeDelay = false;
  if (minimumDuration <= 0) {
    open();
  } else {

    // QTimer::singleShot(minimumDuration, this, SLOT(open()));
    timerDelay.stop();
    timerDelay.setInterval(minimumDuration);
    timerDelay.setSingleShot(true);
    timerDelay.start();
  }
}

bool JKQTEModernProgressDialog::wasCanceled() {
    return m_wasCancel;
}

double JKQTEModernProgressDialog::value() const {
    return progress->value();
}

double JKQTEModernProgressDialog::minimum() const {
  return progress->minimum();
}

double JKQTEModernProgressDialog::maximum() const {
  return progress->maximum();
}

bool JKQTEModernProgressDialog::spin() const {
    return progress->spin();
}

const JKQTEModernProgressWidget *
JKQTEModernProgressDialog::progressWidget() const {
  return progress;
}

const QLabel *JKQTEModernProgressDialog::textLabel() const {
    return label;
}

const QPushButton *JKQTEModernProgressDialog::cancelButton() const {
  return cancel;
}

const QTextEdit *JKQTEModernProgressDialog::longTextWidth() const {
  return longmessage;
}

JKQTEModernProgressWidget *JKQTEModernProgressDialog::progressWidget() {
  return progress;
}

QLabel *JKQTEModernProgressDialog::textLabel() {
    return label;
}

QPushButton *JKQTEModernProgressDialog::cancelButton() {
    return cancel;
}

QTextEdit *JKQTEModernProgressDialog::longTextWidth() {
    return longmessage;
}

void JKQTEModernProgressDialog::cancelClicked() {
  m_wasCancel = true;
  emit canceled();
}

void JKQTEModernProgressDialog::setRange(double min, double max) {
  setMinimum(min);
  setMaximum(max);
}

void JKQTEModernProgressDialog::setMinimum(double min) {
  progress->setMinimum(min);
  if (progress->textDisplayMode() ==
      JKQTEModernProgressWidget::TextDisplayMode::NoText)
    progress->setTextDisplayMode(
        JKQTEModernProgressWidget::TextDisplayMode::ValueText);
}

void JKQTEModernProgressDialog::setMaximum(double max) {
  progress->setMaximum(max);
  if (progress->textDisplayMode() ==
      JKQTEModernProgressWidget::TextDisplayMode::NoText)
    progress->setTextDisplayMode(
        JKQTEModernProgressWidget::TextDisplayMode::ValueText);
}

void JKQTEModernProgressDialog::setMode(
    bool enabledSpin, JKQTEModernProgressWidget::TextDisplayMode mode) {
  progress->setSpin(enabledSpin);
  progress->setTextDisplayMode(mode);
}

void JKQTEModernProgressDialog::setValue(double value) {
  progress->setValue(value);
  if (progress->textDisplayMode() ==
      JKQTEModernProgressWidget::TextDisplayMode::NoText) {
    if (progress->minimum() == 0 && progress->maximum() == 100)
      progress->setTextDisplayMode(
          JKQTEModernProgressWidget::TextDisplayMode::PercentText);
    else
      progress->setTextDisplayMode(
          JKQTEModernProgressWidget::TextDisplayMode::ValueText);
  }
}
