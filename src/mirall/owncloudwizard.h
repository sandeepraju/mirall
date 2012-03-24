/*
 * Copyright (C) by Duncan Mac-Vicar P. <duncan@kde.org>
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

#ifndef MIRALL_OWNCLOUDWIZARD_H
#define MIRALL_OWNCLOUDWIZARD_H

#include <QWizard>

#include "ui_owncloudwizardselecttypepage.h"
#include "ui_createanowncloudpage.h"
#include "ui_owncloudftpaccesspage.h"
#include "ui_owncloudwizardresultpage.h"
#include "ui_owncloudcredentialspage.h"

namespace Mirall {

class OwncloudWizard: public QWizard
{
    Q_OBJECT
public:

    enum {
      Page_SelectType,
      Page_Create_OC,
      Page_OC_Credentials,
      Page_FTP,
      Page_Install
    };

    enum LogType {
      LogPlain,
      LogParagraph
    };

    OwncloudWizard(QWidget *parent = 0L);

    void setOCUrl( const QString& );

public slots:
    void appendToResultWidget( const QString& msg, LogType type = LogParagraph );
    void slotCurrentPageChanged( int );
    void showOCUrlLabel( bool );


signals:
    void connectToOCUrl( const QString& );
    void installOCServer();
    void installOCLocalhost();

private:
    QString _configFile;
    QString _oCUrl;
};

/**
 * page to ask for the type of Owncloud to connect to
 */

class OwncloudWizardSelectTypePage: public QWizardPage
{
    Q_OBJECT
public:
  OwncloudWizardSelectTypePage();
  ~OwncloudWizardSelectTypePage();

  virtual bool isComplete() const;
  virtual void initializePage();
  int nextId() const;
  void setOCUrl( const QString& );
  void showOCUrlLabel( const QString& );

private:
  Ui_OwncloudWizardSelectTypePage _ui;

};

class CreateAnOwncloudPage: public QWizardPage
{
    Q_OBJECT
public:
  CreateAnOwncloudPage();
  ~CreateAnOwncloudPage();

  virtual bool isComplete() const;
  virtual void initializePage();
  virtual int nextId() const;

  QString domain() const;

private:
  Ui_CreateAnOwncloudPage _ui;

};

class OwncloudCredentialsPage: public QWizardPage
{
    Q_OBJECT
public:
  OwncloudCredentialsPage();
  ~OwncloudCredentialsPage();

  virtual bool isComplete() const;
  virtual void initializePage();
  virtual int nextId() const;


private:
  Ui_OwncloudCredentialsPage _ui;

};
/**
 * page to ask for the ftp credentials etc. for ftp install
 */
class OwncloudFTPAccessPage : public QWizardPage
{
  Q_OBJECT
public:
  OwncloudFTPAccessPage();
  ~OwncloudFTPAccessPage();

  virtual bool isComplete() const;
  virtual void initializePage();
  void setFTPUrl( const QString& );
  virtual int nextId() const;

private:
  Ui_OwncloudFTPAccessPage _ui;

};

/**
 * page to display the install result
 */
class OwncloudWizardResultPage : public QWizardPage
{
  Q_OBJECT
public:
  OwncloudWizardResultPage();
  ~OwncloudWizardResultPage();

  virtual bool isComplete() const;
  virtual void initializePage();

public slots:
  void appendResultText( const QString&, OwncloudWizard::LogType type = OwncloudWizard::LogParagraph );
  void showOCUrlLabel( const QString&, bool );

private:
  Ui_OwncloudWizardResultPage _ui;

};

} // ns Mirall

#endif
