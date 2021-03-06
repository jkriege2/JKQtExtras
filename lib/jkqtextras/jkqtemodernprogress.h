/*
    Copyright (c) 2008-2020 Jan W. Krieger (<jan@jkrieger.de>)

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

#ifndef JKQTEMODERNPROGRESS_H
#define JKQTEMODERNPROGRESS_H

#include "jkqtextras_imexport.h"
#include <QColor>
#include <QDialog>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include <QWidget>

/*! \brief a modern progress indicator widget
    \ingroup JKQtExtrasWidgetsProgress

   Like <a href="https://doc.qt.io/qt-5/qprogressbar.html">QProgressBar</a>
   this can be used to display a progress value() between
   rangeMin() and rangeMax(), but there is also a mode where a colored
   circle/stroke wanders around the widget to indicate that something is going
   on, but not giving a real progress.


   \image html JKQTEModernProgressWidget.png

   Usage example:

   \code
    JKQTEModernProgressWidget* progress=new JKQTEModernProgressWidget(main);
    // choose a mode
    progress->setMode(JKQTEModernProgressWidget::Circles);
    // set the range (these may be any doubles)
    progress->setRange(0,100);
    // set the display mode of the text in the center of the widget (here: OFF)
    progress->setTextDisplayMode(JKQTEModernProgressWidget::NoText);
    // set the suffix for the text display (e.g. to display "25/100" when JKQTEModernProgressWidget::ValueText is used)
    progress->setSuffix("/100");
    // connect to a slider, so we see can change the progress for demonstration
    connect(slider, &QSlider::valueChanged, progress, &JKQTEModernProgressWidget::setValue);
   \endcode
*/
class JKQTEXTRAS_LIB_EXPORT JKQTEModernProgressWidget : public QWidget {
  Q_OBJECT
  Q_PROPERTY(QColor innerCircleProgressColor READ innerCircleProgressColor WRITE setInnerCircleProgressColor USER true)
  Q_PROPERTY(InnerProgressIndicatorMode innerProgressIndicatorMode READ innerProgressIndicatorMode WRITE setInnerProgressIndicatorMode USER true)
  Q_PROPERTY(TextDisplayMode textDisplayMode READ textDisplayMode WRITE setTextDisplayMode USER true)
  Q_PROPERTY(Mode mode READ mode WRITE setMode USER true)
  Q_PROPERTY(int items READ items WRITE setItems USER true)
  Q_PROPERTY(int spinInterval READ spinInterval WRITE setSpinInterval USER true)
  Q_PROPERTY(bool spin READ spin WRITE setSpin USER true)
  Q_PROPERTY(QColor indicatorColor READ indicatorColor WRITE setIndicatorColor USER true)
  Q_PROPERTY(QColor stopColor READ stopColor WRITE setStopColor USER true)
  Q_PROPERTY(QColor startColor READ startColor WRITE setStartColor USER true)
  Q_PROPERTY(QColor innerCircleBackgroundColor READ innerCircleBackgroundColor WRITE setInnerCircleBackgroundColor USER true)
  Q_PROPERTY(QColor indicatorBackgroundColor READ indicatorBackgroundColor WRITE setIndicatorBackgroundColor USER true)
  Q_PROPERTY(double nonBackgroundRange READ nonBackgroundRange WRITE setNonBackgroundRange USER true)
  Q_PROPERTY(double innerRadius READ innerRadius WRITE setInnerRadius USER true)
  Q_PROPERTY(double outerRadius READ outerRadius WRITE setOuterRadius USER true)
  Q_PROPERTY(double value READ value WRITE setValue USER true)
  Q_PROPERTY(double maximum READ maximum WRITE setMaximum USER true)
  Q_PROPERTY(double minimum READ minimum WRITE setMinimum USER true)
  Q_PROPERTY(int precision READ precision WRITE setPrecision USER true)
  Q_PROPERTY(QString suffix READ suffix WRITE setSuffix USER true)
public:
  /** \brief modes of the progress widget */
  enum Mode {
    Strokes,      /**< a ring of rounded strokes \image html JKQTEModernProgressWidget_Strokes.png */
    Circles,      /**< a ring of circles \image html JKQTEModernProgressWidget_circles.png */
    Ring,         /**< a ring filled with a color \image html JKQTEModernProgressWidget_Ring.png */
    GradientRing, /**< a ring filled with a color gradient \image html JKQTEModernProgressWidget_GradientRing.png */
    RoundedStrokeRing, /**< a ring filled with a color \image html JKQTEModernProgressWidget_RoundedStrokeRing.png */
    Pie, /**< a pie filled with a color \image html JKQTEModernProgressWidget_Pie.png */
  };
  Q_ENUM(Mode)

  /** \brief mode of percentage display */
  enum TextDisplayMode {
      NoText,      /**< do not display any text \image html JKQTEModernProgressWidget_NoText.png */
      PercentText, /**< display the percentage (value() between minimum() and maximum() ) \image html JKQTEModernProgressWidget_PercentText.png */
      ValueText    /**< display the value with the given suffix() (suffix() \c =="/100" in the example image)  \image html JKQTEModernProgressWidget_ValueText.png */
  };
  Q_ENUM(TextDisplayMode)

  /** \brief mode of percentage display */
  enum InnerProgressIndicatorMode {
      NoInnerIndicator,      /**< do not display a progress indicator in the center \image html JKQTEModernProgressWidget_NoInnerIndicator.png */
      InnerProgressBarHorizontal,      /**< display a progress bar in the center (below the text) \image html JKQTEModernProgressWidget_InnerProgressBarHorizontal.png */
      InnerProgressFillVertical,     /**< fill the center, depending on the progress, using innerCircleProgressColor() (behind the text) \image html JKQTEModernProgressWidget_InnerProgressFillVertical.png */
      InnerProgressFillHorizontal,     /**< fill the center, depending on the progress, using innerCircleProgressColor() (behind the text) \image html JKQTEModernProgressWidget_InnerProgressFillHorizontal.png */
  };
  Q_ENUM(InnerProgressIndicatorMode)

  JKQTEModernProgressWidget(QWidget *parent = NULL);
  virtual ~JKQTEModernProgressWidget();

  /** \brief suffix for progress display */
  QString suffix() const;
  /** \brief precision for progress display */
  int precision() const;
  /** \brief range minimum */
  double minimum() const;
  /** \brief range maximum */
  double maximum() const;
  /** \brief progress value */
  double value() const;
  /** \brief outer radius (0..1) of the displayed circle/stroke ring */
  double outerRadius() const;
  /** \brief inner radius (0..1) of the displayed circle/stroke ring */
  double innerRadius() const;
  /** \brief color of an indicator, when inactive (usually a bit darker than the
   * widget background color) */
  QColor indicatorBackgroundColor() const;
  /** \brief backround color of the inner circle */
  QColor innerCircleBackgroundColor() const;
  /** \brief color of the indicator the furthest away from the main indicator
   * (usually the same as backgroundColor() ) */
  QColor startColor() const;
  /** \brief color just before the current indicator (usually darker than
   * startColor() ) */
  QColor stopColor() const;
  /** \brief color of the current item */
  QColor indicatorColor() const;
  /** \brief how many of the indicators (fraction 0..1 of items() ) should
   * follow current indicator with a different color than backgroundColor() ) */
  double nonBackgroundRange() const;
  /** \brief is an automatic spin going on? */
  bool spin() const;
  /** \brief interval (milliseconds) of the movement if spin() is \c true */
  int spinInterval() const;
  /** \brief number of indicators making up the circle */
  int items() const;
  /** \brief type of widget: display a ring of strokes or circles, ...) */
  Mode mode() const;
  /** \brief color of the progress text */
  QColor textColor() const;
  /** \brief type of text display mode */
  TextDisplayMode textDisplayMode() const;
  /** \brief type of inner progress indicator */
  InnerProgressIndicatorMode innerProgressIndicatorMode() const;
  /** \brief backround color of the inner circle progress indicator */
  QColor innerCircleProgressColor() const;


public slots:
  /** \brief range minimum */
  void setMinimum(double val);
  /** \brief range maximum */
  void setMaximum(double val);
  /** \brief progress value */
  void setValue(double val);
  /** \brief set range of progress */
  void setRange(double min, double max);
  /** \brief suffix for progress display */
  void setSuffix(QString s);
  /** \brief precision for progress display */
  void setPrecision(int p);
  /** \brief color of the progress text */
  void setTextColor(QColor col);
  /** \brief outer radius (0..1) of the displayed circle/stroke ring */
  void setOuterRadius(int val);
  /** \brief inner radius (0..1) of the displayed circle/stroke ring */
  void setInnerRadius(int val);
  /** \brief how many of the indicators (fraction 0..1 of items() ) should
   * follow current indicator with a different color than backgroundColor() ) */
  void setNonBackgroundRange(double val);
  /** \brief color of the indicator the furthest away from the main indicator
   * (usually the same as backgroundColor() ) */
  void setStartColor(QColor col);
  /** \brief color just before the current indicator (usually darker than
   * startColor() ) */
  void setStopColor(QColor col);
  /** \brief color of the current item */
  void setIndicatorColor(QColor col);
  /** \brief background color behind the indicator items */
  void setIndicatorBackgroundColor(QColor col);
  /** \brief color of an indicator, when inactive (usually a bit darker than the
   * widget background color) */
  void setBackgroundColor(QColor col);
  /** \brief backround color of the inner circle */
  void setInnerCircleBackgroundColor(QColor col);
  /** \brief backround color of the inner circle progress indicator */
  void setInnerCircleProgressColor(QColor col);
  /** \brief is an automatic spin going on? */
  void setSpin(bool enabled);
  /** \brief interval (milliseconds) of the movement if spin() is \c true */
  void setSpinInterval(int msec);
  /** \brief number of indicators making up the circle */
  void setItems(int i);
  /** \brief type of widget: display a ring of strokes or circles, ...) */
  void setMode(Mode m);
  /** \brief type of text display mode */
  void setTextDisplayMode(TextDisplayMode m);
  /** \brief type of inner progress indicator */
  void setInnerProgressIndicatorMode(InnerProgressIndicatorMode innerProgressMode);
protected:
  virtual void paintEvent(QPaintEvent *event);
  virtual void resizeEvent(QResizeEvent *event);
protected slots:
  void doSpin();
  void updateWidget();

private:
  static int getSmoothItems(int items);
  TextDisplayMode m_textDisplayMode;
  QString m_suffix;
  int m_precision;
  double m_rangeMin;
  double m_rangeMax;
  double m_value;
  double m_outerRadius;
  double m_innerRadius;
  int m_items;
  int m_spinItem;
  int m_smoothItems;
  int m_smoothSpinItem;

  QColor m_startColor;
  QColor m_stopColor;
  QColor m_indicatorBackgroundColor;
  QColor m_indicatorColor;
  QColor m_textColor;
  /** \brief backround color of the inner circle */
  QColor m_innerCircleBackgroundColor;
  QColor m_innerCircleProgressColor;
  double m_nonBackgroundRange;
  bool m_spin;
  int m_spinInterval;

  bool m_doRepaint;
  bool m_darkCircleBorder;

  Mode m_mode;
  InnerProgressIndicatorMode m_innerProgressMode;

  QTimer timer;
};

/*! \brief dialog, using JKQTEModernProgressWidget
    \ingroup JKQtExtrasWidgetsProgress

   Use open() and hide() to show/hide the dialog and openDelayed() if you wsnt
   the dialog to appear a given time after you called the function.

   The dialog is displayed at the screen center if setCentered() is set \c true.


    \image html JKQTEModernProgressDialog.png

    Usage example:

    \snippet jkqtextras_test/testmainwindow.cpp Example: JKQTEModernProgressDialog



*/
class JKQTEXTRAS_LIB_EXPORT JKQTEModernProgressDialog : public QDialog {
  Q_OBJECT
public:
  JKQTEModernProgressDialog(QWidget *parent = NULL, Qt::WindowFlags f = 0);
  JKQTEModernProgressDialog(const QString &labelText,
                            const QString &cancelButtonText,
                            QWidget *parent = NULL,
                            Qt::WindowFlags f = Qt::Window |
                                                Qt::WindowTitleHint);
  virtual ~JKQTEModernProgressDialog();

  /** \brief text in the label of the dialog */
  QString labelText() const;
  /** \brief text on the "Cancel" button of the dialog */
  QString cancelButtonText() const;

  /** \brief add a line of text to the dialog */
  void addLongTextLine(const QString &t);



  /*! \brief display the progress dialog after a delay of \a minimumDuration
     milliseconds

      If the dialog has beend closed before the delay runs out, it is never
     displayed.
   */
  void openDelayed(int minimumDuration = 2500);
  /** \brief returns \c true if the "Cancel" button has been clicked */
  bool wasCanceled();
  /** \brief returns the current progress value */
  double value() const;
  /** \brief returns the current progress range minimum */
  double minimum() const;
  /** \brief returns the current progress range maximum */
  double maximum() const;
  /** \brief returns whether the indicator spins */
  bool spin() const;
  /** \brief returns the progress widget */
  const JKQTEModernProgressWidget *progressWidget() const;
  /** \brief returns the text label widget */
  const QLabel *textLabel() const;
  /** \brief returns the cancel button widget */
  const QPushButton *cancelButton() const;
  /** \brief returns the long text lines widget */
  const QTextEdit *longTextWidth() const;
  /** \brief returns the progress widget */
  JKQTEModernProgressWidget *progressWidget();
  /** \brief returns the text label widget */
  QLabel *textLabel();
  /** \brief returns the cancel button widget */
  QPushButton *cancelButton();
  /** \brief returns the long text lines widget */
  QTextEdit *longTextWidth(); /** \brief en-/disable spin and progress mode */
  /** \brief set mode of the widget and en/-diable the spin */
  void setMode(bool enabledSpin, JKQTEModernProgressWidget::TextDisplayMode mode);

public slots:
  /** \brief set the value in progress mode (activate calling setRange() or
   * setProgress() ) */
  void setValue(double value);
  /** \brief set the progress range */
  void setRange(double min, double max);
  /** \brief set the progress range */
  void setMinimum(double min);
  /** \brief set the progress range */
  void setMaximum(double max);
  /** \brief text in the label of the dialog */
  void setLabelText(const QString &t);
  /** \brief text on the "Cancel" button of the dialog */
  void setCancelButtonText(const QString &t);
  /** \brief indicate whetehr the dialog has a Cancel button (default: \c true )*/
  void setHasCancel(bool has = true);

signals:
  /** \brief emitted when the "Cancel" button is clicked */
  void canceled();

private:
  QLabel *label;
  QTextEdit *longmessage;
  JKQTEModernProgressWidget *progress;
  QPushButton *cancel;
  int m_minimumDuration;
  bool m_wasCancel;
  bool m_closedBeforeDelay;
  QTimer timerDelay;

protected:
  void createWidgets();
  virtual void showEvent(QShowEvent *event);
  virtual void closeEvent(QCloseEvent *e);
protected slots:
  void cancelClicked();
};

#endif // JKQTEMODERNPROGRESS_H
