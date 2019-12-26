#include "jkqteenhancedcombobox.h"
#include <QLineEdit>
#include <QAbstractItemView>
#include <QListView>

JKQTEEnhancedComboBox::JKQTEEnhancedComboBox(QWidget *parent) :
    QComboBox(parent)
{
    m_readonly=false;
    m_oldEditable=isEditable();
}

void JKQTEEnhancedComboBox::setReadonly(bool readonly) {
    m_readonly=readonly;
    if (lineEdit()) lineEdit()->setReadOnly(readonly);
    if (isEditable() && readonly) {
        m_oldEditable=true;
        setEditable(false);
    }
    if (!readonly && (m_oldEditable!=isEditable())) {
        setEditable(m_oldEditable);
    }
}

bool JKQTEEnhancedComboBox::readonly() const
{
    return m_readonly;
}

void JKQTEEnhancedComboBox::showPopup() {
    if (!m_readonly) {
        QComboBox::showPopup();



        QFontMetrics fm(view()->font());
        int width=view()->size().width();
        for (int i=0; i<qMin(count(), 100); i++) {
            int w=fm.width(itemText(i));
            if (w>width) width=w;
        }

        view()->setMinimumWidth(qMax(width, this->width()));
        view()->setGeometry(0,0,width, view()->size().height());

    }
}

void JKQTEEnhancedComboBox::keyPressEvent ( QKeyEvent * e ) {
    if (e->key()==Qt::Key_Enter || e->key()==Qt::Key_Return) emit editingFinished();
//    else e->ignore();
    if (!m_readonly) QComboBox::keyPressEvent(e);
}

void JKQTEEnhancedComboBox::keyReleaseEvent ( QKeyEvent * e ) {
    if (!m_readonly) QComboBox::keyReleaseEvent(e);
}

void JKQTEEnhancedComboBox::wheelEvent ( QWheelEvent * e ) {
    if (!m_readonly) QComboBox::wheelEvent(e);
}
