/*
    Copyright (c) 2013-2019 Jan W. Krieger (<jan@jkrieger.de>)

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


#ifndef JKQTEVERTICALSCROLLAREA_H
#define JKQTEVERTICALSCROLLAREA_H

#include "jkqtextras_imexport.h"
#include <QScrollArea>

/*! \brief a scrollarea which shows only vertical scrollbars whenever possible (minimum widget size) and otherwise tries
           to maximize the size of the widget.
    \ingroup JKQtExtrasWidgetsLayout


 */
class JKQTEXTRAS_LIB_EXPORT JKQTEVerticalScrollArea : public QScrollArea {
        Q_OBJECT
    public:
        JKQTEVerticalScrollArea(QWidget* parent);
        virtual ~JKQTEVerticalScrollArea();
    protected:
        virtual void resizeEvent(QResizeEvent* event);
    private:
};

#endif // JKQTEVERTICALSCROLLAREA_H
