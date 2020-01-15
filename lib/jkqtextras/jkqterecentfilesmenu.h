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

#ifndef JKQTERECENTFILESMENU_H
#define JKQTERECENTFILESMENU_H

#include <QMenu>
#include <QSettings>
#include <QList>
#include <QStringList>
#include <QMap>
#include <QFileInfo>
#include <QFileIconProvider>
#include "jkqtextras_imexport.h"

/*! \brief a special QMenu that allows to manage a list of recently loaded files
    \ingroup JKQtExtrasWidgetsMenus

    \image html JKQTERecentFilesMenu.png

    Usage example:

    \snippet jkqtextras_test/testmainwindow.cpp Example: JKQTERecentFilesMenu
 */
class JKQTEXTRAS_LIB_EXPORT JKQTERecentFilesMenu : public QMenu {
        Q_OBJECT
    public:
        explicit JKQTERecentFilesMenu(QWidget *parent = 0);

        /** \brief set the max. number of files in the list */
        void setMaxRecentFilesCount(int num);
        /** \brief returns the max. number of files in the list */
        int maxRecentFilesCount() const;
        /** \brief show icons next to the recent files */
        void setShowIcons(bool enabled);
        /** \brief show icons next to the recent files */
        bool doesShowIcons() const;

        void setAlwaysEnabled(bool enabled);

        /** \brief register an icon for a given filetype this overrides the display of system icons */
        void setIconForExtension(const QString& extension, const QIcon& icon);
        /** \brief set the default icon */
        void setDefaultIcon(const QIcon& defaultIcon);
        /** \brief use file icons from system */
        void setUseSystemFileIcons(bool use);

        /*! \brief save the list of recent files into a QSettings object.

            The settings are saved under the key
              \c [prefix] + "recentfilelist"
         */
        void storeSettings(QSettings& settings, QString prefix=QString(""));
        /*! \brief read the list of recent files from a QSettings object.

            The settings are saved under the key
              \c [prefix] + "recentfilelist"
         */
        void readSettings(QSettings& settings, QString prefix=QString(""));

        /** \brief add a new file to the list of recent files */
        void addRecentFile(const QString& filename);
        /** \brief clear all recent files */
        void clearRecentFiles();
        
    signals:
        /** \brief emitted when the user clicks one of the recent files in the menu. */
        void openRecentFile(const QString& filename);
    public slots:
        void setMenuEnabled(bool enabled);
    protected:
        bool alwaysDisabled;
        QList<QAction*> m_actions;
        QStringList m_files;
        QMap<QString, QIcon> m_fileIcons;
        QIcon m_defaultIcon;
        bool m_useSystemFileIcons;
        bool m_icons;
        bool m_alwaysEnabled;
        QFileIconProvider iconProvider;
        QString strippedName(const QString &fullFileName);
        QIcon iconForFile(const QFileInfo& fileinfo);
    protected slots:
        void updateActions();
        void intOpenRecentFile();
        
};

#endif // JKQTERECENTFILESMENU_H
