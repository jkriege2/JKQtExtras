#ifndef JKQTECOLORSAMPLER_H
#define JKQTECOLORSAMPLER_H

#include <QWidget>
#include "jkqtextras_imexport.h"

/*! \brief a widget which display a color (sample)
    \ingroup JKQtExtrasWidgetsLabels

    Screenshots:
    \image html JKQTEColorSampler.png

    Basic usage is simple:

    \snippet jkqtextras_test/testmainwindow.cpp Example: JKQTEColorSampler

*/
class JKQTEColorSampler : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(SamplerMode samplerMode READ samplerMode WRITE setSamplerMode USER true)
    Q_PROPERTY(QColor color READ color WRITE setColor USER true)
public:
    /** \brief available modes for the slider
         *
         *  the appearance and the range of the slider depend on this */
    enum SamplerMode {
        CircleSampler=0,    /**< color is shown as a filled circle \image html JKQTEColorSampler_CircleSampler.png */
        RectangleSampler,   /**< color is shown as a filled rectangle \image html JKQTEColorSampler_RectangleSampler.png */
    };
    Q_ENUM(SamplerMode)

    explicit JKQTEColorSampler(QWidget *parent = nullptr);

    /** \brief sets the color to display */
    QColor color() const;
    /** \brief sets the display mode of the color sampler */
    SamplerMode samplerMode() const;

    virtual QSize minimumSizeHint() const override;
    virtual QSize sizeHint() const override;
public slots:
    /** \brief sets the color to display */
    void setColor(QColor col);
    /** \brief sets the display mode of the color sampler */
    void setSamplerMode(SamplerMode m);
signals:

protected:
    QColor m_color;
    SamplerMode m_samplerMode;

    /** \brief paints the sampler */
    virtual void paintEvent(QPaintEvent *ev) override;
};

#endif // JKQTECOLORSAMPLER_H
