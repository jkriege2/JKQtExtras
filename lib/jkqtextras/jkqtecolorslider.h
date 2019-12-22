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
#include "jkqtextras_imexport.h"

/*! \brief a QSlider that allows to choose a color hue
    \ingroup JKQtExtrasWidgetsSliders


    Horizontal Hue-Slider:
    \image html JKQTEHueSliderHorizontal.png

    Vertical Hue Slider:
    \image html JKQTEHueSliderVertical.png

    Usage is simple:

    \snippet jkqtextras_test/testmainwindow.cpp Example: JKQTEHueSlider

 */
class JKQTEXTRAS_LIB_EXPORT JKQTEColorSlider : public QSlider {
        Q_OBJECT
    public:
        /** \brief available modes for the slider
         *
         *  the appearance and the range of the slider depend on this */
        enum SliderMode {
            RedSlider,
            GreenSlider,
            BlueSlider,
            GreySlider,
            HueSlider,
        };

        explicit JKQTEColorSlider(QWidget *parent = nullptr);
        explicit JKQTEColorSlider(Qt::Orientation orientation, QWidget *parent = nullptr);

        /** \brief returns the currently set color/slider mode
         *
         *  The appearance and the range of the slider depend on this
         *
         *  \see SliderMode setColorMode() */
        SliderMode colorMode() const;
        /** \brief takes the color \a colorIn and applies the value of the slider to the color */
        QColor modifiedColor(QColor colorIn=QColor("black")) const;


        virtual QSize minimumSizeHint() const override;
        virtual QSize sizeHint() const override;

    signals:

    public slots:
        /** \brief sets the currently set color/slider mode
         *
         *  The appearance and the range of the slider depend on this
         *
         *  \note This also changes the range of the slider!
         *  \see SliderMode colorMode()
         */
        void setColorMode(SliderMode mode);
    protected:
        SliderMode m_mode;


        virtual void paintEvent(QPaintEvent *ev) override;


};


#endif // JKQTECOLORSLIDER_H
