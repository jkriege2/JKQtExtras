/*
    Copyright (c) 2013-2020 Jan W. Krieger (<jan@jkrieger.de>)

    This software is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License (GPL) as published by
    the Free Software Foundation, either version 3.0 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "jkqterecentfilesmenu.h"
#include <QFileInfo>
#include <QFileIconProvider>

JKQTERecentFilesMenu::JKQTERecentFilesMenu(QWidget *parent) :
    QMenu(parent)
{
    setTitle(tr("Recent Files ..."));
    setMaxRecentFilesCount(20);
    m_useSystemFileIcons=true;
    m_icons=true;
    m_defaultIcon=QIcon();
    m_alwaysEnabled=false;
    m_fileIcons.clear();
    alwaysDisabled=false;
}

void JKQTERecentFilesMenu::setMaxRecentFilesCount(int num) {
    if (m_actions.count()>num) {
        for (int i=m_actions.count()-1; i>=num; i--) {
            removeAction(m_actions[i]);
            delete m_actions[i];
            m_actions.pop_back();
        }
    } else if (m_actions.count()<num) {
        for (int i=m_actions.count(); i<num; i++) {
            QAction* act=new QAction(this);
            act->setVisible(false);
            connect(act, SIGNAL(triggered()), this, SLOT(intOpenRecentFile()));
            m_actions.append(act);
            addAction(act);
        }
    }
}

int JKQTERecentFilesMenu::maxRecentFilesCount() const {
    return m_actions.count();
}

void JKQTERecentFilesMenu::setShowIcons(bool enabled) {
    m_icons=enabled;
    updateActions();
}

bool JKQTERecentFilesMenu::doesShowIcons() const {
    return m_icons;
}

void JKQTERecentFilesMenu::setAlwaysEnabled(bool enabled) {
    m_alwaysEnabled=enabled;
    updateActions();
}

void JKQTERecentFilesMenu::setIconForExtension(const QString &extension, const QIcon &icon) {
    m_fileIcons[extension]=icon;
    updateActions();
}

void JKQTERecentFilesMenu::storeSettings(QSettings &settings, QString prefix) {
    settings.setValue(prefix+QString("recentfilelist"), m_files);
    //settings.setValue(prefix+QString("recentfilelist_max"), maxRecentFilesCount());
}

void JKQTERecentFilesMenu::readSettings(QSettings &settings, QString prefix) {
    //setMaxRecentFilesCount(settings.value(prefix+QString("recentfilelist_max"), maxRecentFilesCount()).toInt());
    m_files=settings.value(prefix+QString("recentfilelist")).toStringList();
    m_files.removeDuplicates();
    if (m_files.size()>0) for (int j = m_files.size()-1; j >=0 ; j--) {
        if (m_files[j].trimmed().isEmpty()) {
            m_files.removeAt(j);
        }
    }
    while (m_files.size()>maxRecentFilesCount()) {
        m_files.pop_back();
    }
    updateActions();
}

void JKQTERecentFilesMenu::addRecentFile(const QString &filename) {
    m_files.removeDuplicates();
    if (m_files.size()>0) for (int j = m_files.size()-1; j >=0 ; j--) {
        if (m_files[j].trimmed().isEmpty()) {
            m_files.removeAt(j);
        }
    }
    m_files.removeAll(filename);
    m_files.prepend(filename);
    while (m_files.size()>maxRecentFilesCount()) {
        m_files.pop_back();
    }
    updateActions();
}

void JKQTERecentFilesMenu::clearRecentFiles() {
    m_files.clear();
    updateActions();
}

void JKQTERecentFilesMenu::updateActions() {
    int numRecentFiles = qMin(m_files.size(), (int)maxRecentFilesCount());
    for (int i = 0; i < numRecentFiles; ++i) {
        QString text = tr("&%1 %2").arg(i + 1).arg(strippedName(m_files[i]));
        m_actions[i]->setText(text);
        m_actions[i]->setToolTip(m_files[i]);
        m_actions[i]->setData(m_files[i]);
        m_actions[i]->setIcon(iconForFile(QFileInfo(m_files[i])));
        m_actions[i]->setVisible(true);
    }
    for (int i=numRecentFiles; i<maxRecentFilesCount(); i++) {
        m_actions[i]->setText("");
        m_actions[i]->setData("");
        m_actions[i]->setToolTip("");
        m_actions[i]->setVisible(false);
        m_actions[i]->setIcon(QIcon());
    }
    if (alwaysDisabled) setEnabled(false);
    else {
        if (numRecentFiles<=0) setEnabled(m_alwaysEnabled);
        else setEnabled(true);
    }
}

void JKQTERecentFilesMenu::intOpenRecentFile() {
    QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        emit openRecentFile(action->data().toString());
    }
}

QString JKQTERecentFilesMenu::strippedName(const QString &fullFileName) {
    return QFileInfo(fullFileName).fileName();
}

QIcon JKQTERecentFilesMenu::iconForFile(const QFileInfo &fileinfo) {
    if (m_icons) {
        if (m_fileIcons.contains(fileinfo.completeSuffix().toLower())) {
            return m_fileIcons[fileinfo.completeSuffix().toLower()];
        }
        if (m_useSystemFileIcons) {
            return iconProvider.icon(fileinfo);
        }
        return m_defaultIcon;
    } else {
        return QIcon();
    }
}

void JKQTERecentFilesMenu::setUseSystemFileIcons(bool use) {
    m_useSystemFileIcons=use;
}

void JKQTERecentFilesMenu::setDefaultIcon(const QIcon &defaultIcon) {
    m_defaultIcon=defaultIcon;
}

void JKQTERecentFilesMenu::setMenuEnabled(bool enabled)
{
    alwaysDisabled=!enabled;
    updateActions();
}
