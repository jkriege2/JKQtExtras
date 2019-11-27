#ifndef JKQTEVISIBLEHANDLESPLITTER_H
#define JKQTEVISIBLEHANDLESPLITTER_H

#include <QSplitter>
#include <QSplitterHandle>
#include "jkqtextras_imexport.h"

/*! \brief a QSplitter that has a really visible Splitter handle
    \ingroup JKQtExtrasWidgets

    This is a simple replacement for <a href="https://doc.qt.io/qt-5/qsplitter.html">QSplitter</a>,
    which only adds sime visual tweaks:
      - a better visible handle
      - a highlighting/hover effect
      - a changeable grip width
    .

    The splitter looks like this:
    \image html JKQTEVisibleHandleSplitter.png
    \image html JKQTEVisibleHandleSplitterHover.png

    Usage is simple:

    \snippet jkqtextras_test/testmainwindow.cpp Example: JKQTEVisibleHandleSplitter

 */
class JKQTEXTRAS_LIB_EXPORT JKQTEVisibleHandleSplitter : public QSplitter {
        Q_OBJECT
    public:
        explicit JKQTEVisibleHandleSplitter(Qt::Orientation orientation, QWidget *parent = nullptr);
        explicit JKQTEVisibleHandleSplitter(QWidget *parent = nullptr);
        void setDecorated(bool enabled);
        void setHoverEffect(bool enabled);
        void setGripWidth(int width);
    signals:

    public slots:

    protected:
        QSplitterHandle *createHandle();

};



/*! \brief a QSplitterHandle that is really visible Splitter handle (used by JKQTEVisibleHandleSplitter)
    \ingroup JKQtExtrasWidgets

    \see JKQTEVisibleHandleSplitter

 */
class JKQTEXTRAS_LIB_EXPORT JKQTEVisibleHandleSplitterHandle: public QSplitterHandle {
        Q_OBJECT
    public:
        JKQTEVisibleHandleSplitterHandle(Qt::Orientation orientation, QSplitter * parent=nullptr);
        void setDecorated(bool enabled);
        bool decorated() const;
        void setHoverEffect(bool enabled);
        bool hoverEffect() const;
        void setGripWidth(int width);
        int gripWidth() const;
    protected:
        virtual void leaveEvent(QEvent* event);
        virtual void enterEvent(QEvent* event);
        virtual void paintEvent(QPaintEvent* event);
        int m_gripHeight;
        bool m_inside;
        bool m_lightup;
        bool m_drawGrip;
};

#endif // JKQTEVISIBLEHANDLESPLITTER_H
