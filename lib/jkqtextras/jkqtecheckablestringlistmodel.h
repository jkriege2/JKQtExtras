/*
    Copyright (c) 2015-2020 Jan W. Krieger (<jan@jkrieger.de>)

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

#ifndef JKQTECHECKABLESTRINGLISTMODEL_H
#define JKQTECHECKABLESTRINGLISTMODEL_H

#include <QStringListModel>
#include <QSet>
#include "jkqtextras_imexport.h"

/** \brief a QStringListModel, which allows to check/uncheck each entry
 *  \ingroup JKQtExtrasToolsClassesModels
 *
 *  Usage in QListView:
 *  \image html JKQTECheckableStringListModel.png
 *
 *  Basic usage is simple:
 *
 *  \snippet jkqtextras_test/testmainwindow.cpp Example: JKQTECheckableStringListModel
 *
 */
class JKQTEXTRAS_LIB_EXPORT JKQTECheckableStringListModel : public QStringListModel {
    Q_OBJECT
public:
    explicit JKQTECheckableStringListModel(QObject *parent = 0);
    explicit JKQTECheckableStringListModel(bool editable, bool checkable, QObject *parent = 0);

    /** \brief check the \a i -th entry */
    void setChecked(int i);
    /** \brief check/uncheck the \a i -th entry */
    void setChecked(int i, bool c);
    /** \brief uncheck the \a i -th entry */
    void setUnChecked(int i);
    /** \brief is the \a i -th entry checked? */
    bool isChecked(int i) const;
    /** \brief uncheck all items */
    void unCheckAll();
    /** \brief check all items */
    void checkAll();

    /** \brief model contents (texts!) is editable */
    void setTextEditable(bool editable);
    /** \brief is the model contents (texts!) editable? */
    bool isTextEditable() const;

    /** \brief model contents (texts!) is editable */
    void setCheckable(bool checkable);
    /** \brief is the model contents (texts!) editable? */
    bool isCheckable() const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex &index) const;


protected:
    QSet<int> m_check;
    bool m_editable;
    bool m_checkable;
};

#endif // JKQTECHECKABLESTRINGLISTMODEL_H
