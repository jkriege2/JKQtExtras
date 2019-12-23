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

#ifndef JKQTECOLORSLIDER_H
#define JKQTECOLORSLIDER_H

#include <QSlider>
#include <QPen>
#include <QBrush>
#include <QColor>
#include "jkqtextras_imexport.h"

/*! \brief a QSlider that allows to choose a color hue
    \ingroup JKQtExtrasWidgetsSliders


    Horizontal Hue-Slider:
    \image html JKQTEColorSliderHorizontal.png

    Vertical Hue Slider:
    \image html JKQTEColorSliderVertical.png

    Basic usage is simple:

    \snippet jkqtextras_test/testmainwindow.cpp Example: JKQTEColorSlider

    \section JKQTEColorSliderBaseColorMode Base Color Mode

    Especially when building a color-chooser, you need to combine several sliders.
    That then define a color together. To support such modes, the slider can use
    a "base color" i.e. an input color which is then modified and output again.
    The following functions support this mode:
        - setBaseColor()
        - baseColor()
        - modifiedColor()
        - Signal: colorChanged()
    .

    Here is an example of how to use this feature:

    \snippet jkqtextras_test/testmainwindow.cpp Example: JKQTEColorSliderRGBGroup

    \image html JKQTEColorSliderRGBGroup.png

*/
class JKQTEXTRAS_LIB_EXPORT JKQTEColorSlider : public QSlider {
        Q_OBJECT
        Q_PROPERTY(QColor baseColor READ baseColor WRITE setBaseColor USER true)
        Q_PROPERTY(SliderMode sliderMode READ sliderMode WRITE setSliderMode USER true)
        Q_PROPERTY(QBrush indicatorBrush READ indicatorBrush WRITE setIndicatorBrush USER true)
        Q_PROPERTY(QPen indicatorPen READ indicatorPen WRITE setIndicatorPen USER true)
        Q_PROPERTY(IndicatorStyle IndicatorStyle READ indicatorStyle WRITE setIndicatorStyle USER true)
    public:
        /** \brief available modes for the slider
         *
         *  the appearance and the range of the slider depend on this */
        enum SliderMode {
            GreySlider=0,  /**< the slider modifies the grey color channel \image html JKQTEColorSlider_Grey.png */
            GraySlider=GreySlider,  /**< the slider modifies the grey color channel \image html JKQTEColorSlider_Grey.png */
            RedSlider,   /**< the slider modifies the red color channel \image html JKQTEColorSlider_Red.png */
            GreenSlider, /**< the slider modifies the green color channel \image html JKQTEColorSlider_Green.png */
            BlueSlider,  /**< the slider modifies the blue color channel \image html JKQTEColorSlider_Blue.png */
            HueSlider,   /**< the slider modifies the hue color channel (from HSV color model) \image html JKQTEColorSlider_Hue.png */
            SaturationSlider,   /**< the slider modifies the saturation color channel (from HSV color model) \image html JKQTEColorSlider_Saturation.png */
            ValueSlider,   /**< the slider modifies the value color channel (from HSV color model) \image html JKQTEColorSlider_Value.png */
            TransparencySlider,   /**< the slider modifies the transparency color channel  \image html JKQTEColorSlider_Transparency.png */
            AlphaSlider=TransparencySlider,   /**< the slider modifies the transparency color channel  \image html JKQTEColorSlider_Transparency.png */
        };
        Q_ENUM(SliderMode)

        /** \brief available modes for the slider
         *
         *  the appearance and the range of the slider depend on this */
        enum IndicatorStyle {
            FixedColorDoubleArrowIndicator=0,  /**< draws two inward pointing triangles as indicator, filled with indicatorBrush() \image html JKQTEColorSlider_FixedColorDoubleArrowIndicator.png */
            FixedColorCircleIndicator,   /**< draws a circle as indicator, filled with indicatorBrush()  \image html JKQTEColorSlider_FixedColorCircleIndicator.png */
            SelectedColorDoubleArrowIndicator,  /**< draws two inward pointing triangles as indicator, filled with the current color \image html JKQTEColorSlider_SelectedColorDoubleArrowIndicator.png */
            SelectedColorCircleIndicator,   /**< draws a circle as indicator, filled with the current color  \image html JKQTEColorSlider_SelectedColorCircleIndicator.png */
        };
        Q_ENUM(IndicatorStyle)

        explicit JKQTEColorSlider(QWidget *parent = nullptr);
        explicit JKQTEColorSlider(Qt::Orientation orientation, QWidget *parent = nullptr);
        explicit JKQTEColorSlider(SliderMode mode, QWidget *parent = nullptr);
        explicit JKQTEColorSlider(SliderMode mode, Qt::Orientation orientation, QWidget *parent = nullptr);

        /** \brief returns the currently set color/slider mode
         *
         *  The appearance and the range of the slider depend on this
         *
         *  \see SliderMode setSliderMode() */
        SliderMode sliderMode() const;
        /** \brief style of the indicator */
        IndicatorStyle indicatorStyle() const;
        /** \brief takes the color \a colorIn and applies the value of the slider to the color */
        QColor modifiedColor(QColor colorIn) const;
        /** \brief takes the color baseColor() and applies the value of the slider to the color
         *
         * \see \ref JKQTEColorSliderBaseColorMode baseColor(), setBaseColor(), baseColor(), colorChanged()
         * */
        QColor modifiedColor() const;
        /** \brief returns the currently set base color that is modified by the slider
         *
         * \see \ref JKQTEColorSliderBaseColorMode baseColor(), setBaseColor(), modifiedColor(), colorChanged()
         * */
        QColor baseColor() const;

        /** \brief returns the <a href="https://doc.qt.io/qt-5/qbrush.html">QBrush</a> used to draw the indicator */
        const QBrush &indicatorBrush() const;
        /** \brief returns the <a href="https://doc.qt.io/qt-5/qpen.html">QPen</a> used to draw the indicator */
        const QPen& indicatorPen() const;
        /** \brief returns the <a href="https://doc.qt.io/qt-5/qbrush.html">QBrush</a> used to draw the indicator */
        QBrush& indicatorBrush();
        /** \brief returns the <a href="https://doc.qt.io/qt-5/qpen.html">QPen</a> used to draw the indicator */
        QPen& indicatorPen();

        /** \brief sets the <a href="https://doc.qt.io/qt-5/qbrush.html">QBrush</a> used to draw the indicator */
        void setIndicatorBrush(const QBrush& b);
        /** \brief sets the <a href="https://doc.qt.io/qt-5/qpen.html">QPen</a> used to draw the indicator */
        void setIndicatorPen(const QPen &p);
        /** \brief sets the style of the indicator */
        void setIndicatorStyle(IndicatorStyle s) ;

        virtual QSize minimumSizeHint() const override;
        virtual QSize sizeHint() const override;

    signals:
        /** \brief emitted when the slider moves, the color is based on the baseColor(),
         *         modified by the slider value
         *
         * \see \ref JKQTEColorSliderBaseColorMode baseColor(), setBaseColor(), modifiedColor(), colorChanged()
         * */
        void colorChanged(QColor color);
    public slots:
        /** \brief sets the currently set color/slider mode
         *
         *  The appearance and the range of the slider depend on this
         *
         *  \note This also changes the range of the slider!
         *  \see SliderMode sliderMode()
         */
        void setSliderMode(SliderMode mode);
        /** \brief sets the currently set base color that is modified by the slider
         *
         * \see \ref JKQTEColorSliderBaseColorMode baseColor(), baseColor(), modifiedColor(), colorChanged()
         * */
        void setBaseColor(QColor baseColor);
    protected slots:
        void baseSliderChanged(int value);
    protected:
        /** \brief currently set color/slider mode */
        SliderMode m_mode;
        /** \brief currently set base color that is modified by the slider
         *
         * \see \ref JKQTEColorSliderBaseColorMode baseColor(), baseColor(), modifiedColor(), colorChanged() */
        QColor m_baseColor;
        /** \brief <a href="https://doc.qt.io/qt-5/qbrush.html">QBrush</a> used to draw the indicator */
        QBrush m_indicatorBrush;
        /** \brief <a href="https://doc.qt.io/qt-5/qpen.html">QPen</a> used to draw the indicator */
        QPen m_indicatorPen;
        /** \brief style of the indicator */
        IndicatorStyle m_indicatorStyle;
        /** \brief returns the default base color for a given slider mode */
        static QColor defaultBaseColor(SliderMode mode);
        /** \brief paints the slider */
        virtual void paintEvent(QPaintEvent *ev) override;


};


#endif // JKQTECOLORSLIDER_H
