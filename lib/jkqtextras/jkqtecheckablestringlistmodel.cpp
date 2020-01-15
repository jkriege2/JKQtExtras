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

#include "jkqtecheckablestringlistmodel.h"
#include <QDebug>
JKQTECheckableStringListModel::JKQTECheckableStringListModel(QObject *parent) :
    QStringListModel(parent),
    m_editable(false),
    m_checkable(true)
{
    m_check.clear();
}

JKQTECheckableStringListModel::JKQTECheckableStringListModel(bool editable, bool checkable, QObject *parent) :
    QStringListModel(parent),
    m_editable(editable),
    m_checkable(checkable)
{
    m_check.clear();
}

void JKQTECheckableStringListModel::setChecked(int i) {
    m_check.insert(i);
    emit dataChanged(index(i, 0), index(i, 0));
}

void JKQTECheckableStringListModel::setChecked(int i, bool c) {
    if (c) m_check.insert(i);
    else m_check.remove(i);
    emit dataChanged(index(i, 0), index(i, 0));
}

void JKQTECheckableStringListModel::setUnChecked(int i) {
    m_check.remove(i);
    emit dataChanged(index(i, 0), index(i, 0));
}

bool JKQTECheckableStringListModel::isChecked(int i) const {
    //qDebug()<<i<<m_check;
    return m_check.contains(i);
}

void JKQTECheckableStringListModel::unCheckAll() {
    m_check.clear();
    int cnt=rowCount();
    for (int i=0; i<cnt; i++) {
        emit dataChanged(index(i, 0), index(i, 0));
    }
}

void JKQTECheckableStringListModel::checkAll() {
    m_check.clear();
    for (int i=0; i<stringList().size(); i++) {
        m_check.insert(i);
        emit dataChanged(index(i, 0), index(i, 0));
    }
}

QVariant JKQTECheckableStringListModel::data(const QModelIndex &index, int role) const {
    if (role==Qt::CheckStateRole) {
        if (isChecked(index.row())) return QVariant(Qt::Checked);
        else return QVariant(Qt::Unchecked);
    } else {
        return QStringListModel::data(index, role);
    }
}

bool JKQTECheckableStringListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role==Qt::CheckStateRole) {
        setChecked(index.row(), value.toBool());
        return true;
    } else {
        return QStringListModel::setData(index, value, role);
    }
}

Qt::ItemFlags JKQTECheckableStringListModel::flags(const QModelIndex &/*index*/) const {
    if (m_checkable) {
        if (m_editable) return Qt::ItemIsUserCheckable|Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable;
        else return Qt::ItemIsUserCheckable|Qt::ItemIsSelectable|Qt::ItemIsEnabled;
    } else {
        if (m_editable) return Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable;
        else return Qt::ItemIsSelectable|Qt::ItemIsEnabled;
    }
}

void JKQTECheckableStringListModel::setTextEditable(bool editable) {
    m_editable=editable;
}

bool JKQTECheckableStringListModel::isTextEditable() const {
    return m_editable;
}

void JKQTECheckableStringListModel::setCheckable(bool checkable)
{
    m_checkable=checkable;
}

bool JKQTECheckableStringListModel::isCheckable() const
{
    return m_checkable;
}
