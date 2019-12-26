#ifndef JKQTEENHANCEDCOMBOBOX_H
#define JKQTEENHANCEDCOMBOBOX_H

#include <QComboBox>
#include "jkqtextras_imexport.h"
#include <QKeyEvent>

/** \brief this QComboox descendent with en hanced features (e.g. can be set to
 *         read-only, editingFinished() signal, ...)
 *  \ingroup JKQtExtrasWidgetsEdits
 *
 *  Added features are:
 *    - setReadonly() slot, which shows the combobox in the standardway, but prevents editing (and deletes any key-press events)
 *    - editingFinished() signal, which is emitted when "return" or "enter" key is pressed
 *    .
 *
 *  \image html JKQTEEnhancedComboBox.png
 *
 *  Usage example:
 *  \snippet jkqtextras_test/testmainwindow.cpp Example: JKQTEEnhancedComboBox
 */
class JKQTEXTRAS_LIB_EXPORT JKQTEEnhancedComboBox : public QComboBox {
        Q_OBJECT
        Q_PROPERTY(bool readonly READ readonly WRITE setReadonly USER true)
    public:
        explicit JKQTEEnhancedComboBox(QWidget *parent = 0);

        virtual void showPopup();
        /** \brief is the combobox in read-only mode? */
        bool readonly() const;


    public slots:
        /** \brief switches the combobox between read-only mode and editable mode */
        void setReadonly(bool readonly);

    signals:
        /** \brief signal, which is emitted when the editing of the widget finishes.
         *
         * This signal is emitted when \c setEditbale(true) was set and the editing in the widget
         * finished, i.e. a text is entered and RETURN or ENTER is pressed.
         */
        void editingFinished();

    protected:
        bool m_readonly;
        bool m_oldEditable;
        virtual void keyPressEvent ( QKeyEvent * e );
        virtual void keyReleaseEvent ( QKeyEvent * e );
        virtual void wheelEvent ( QWheelEvent * e );
};

#endif // JKQTEENHANCEDCOMBOBOX_H

