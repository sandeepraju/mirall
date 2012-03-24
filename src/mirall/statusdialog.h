/*
 * Copyright (C) by Klaas Freitag <freitag@kde.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#ifndef STATUSDIALOG_H
#define STATUSDIALOG_H

#include <QDialog>
#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include <QUrl>

#include "ui_statusdialog.h"
#include "application.h"

namespace Mirall {

class Theme;
class ownCloudInfo;

class FolderStatusModel : public QStandardItemModel
{
public:
    FolderStatusModel();
    virtual Qt::ItemFlags flags( const QModelIndex& );
    QVariant data(const QModelIndex &index, int role) const;

};


class FolderViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    public:
    FolderViewDelegate();
    virtual ~FolderViewDelegate();

    enum datarole { FolderAliasRole    = Qt::UserRole + 100,
                    FolderPathRole    = Qt::UserRole + 101,
                    FolderIconRole    = Qt::UserRole + 102,
                    FolderRemotePath  = Qt::UserRole + 103,
                    FolderStatus      = Qt::UserRole + 104,
                    FolderErrorMsg    = Qt::UserRole + 105,
                    FolderStatusIcon  = Qt::UserRole + 106,
                    FolderSyncEnabled = Qt::UserRole + 107
    };
    void paint( QPainter*, const QStyleOptionViewItem&, const QModelIndex& ) const;
    QSize sizeHint( const QStyleOptionViewItem&, const QModelIndex& ) const;
    bool editorEvent( QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option,
                      const QModelIndex& index );
};

class StatusDialog : public QDialog, public Ui::statusDialog
{
    Q_OBJECT
public:
    explicit StatusDialog( Theme *theme, QWidget *parent = 0);
    void setFolderList( Folder::Map );

signals:
    void removeFolderAlias( const QString& );
    void fetchFolderAlias( const QString& );
    void pushFolderAlias( const QString& );
    void enableFolderAlias( const QString&, const bool );
    void infoFolderAlias( const QString& );
    void openFolderAlias( const QString& );

    /* start the add a folder wizard. */
    void addASync();

public slots:
    void slotRemoveFolder();
    void slotFetchFolder();
    void slotPushFolder();
    void slotFolderActivated( const QModelIndex& );
    void slotOpenOC();
    void slotEnableFolder();
    void slotInfoFolder();
    void slotAddSync();
    void slotAddFolder( Folder* );
    void slotUpdateFolderState( Folder* );
    void slotFolderRemoved( Folder* );
    void slotCheckConnection();

protected slots:
    void slotOCInfoFail();
    void slotOCInfo( const QString&, const QString& );
    void slotDoubleClicked( const QModelIndex& );

protected:
    void showEvent ( QShowEvent* );
private:
    void folderToModelItem( QStandardItem*, Folder* );

    QStandardItemModel *_model;
    QUrl   _OCUrl;
    Theme *_theme;
    ownCloudInfo *_ownCloudInfo;
};
};

#endif // STATUSDIALOG_H
