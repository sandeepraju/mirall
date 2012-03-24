/***************************************************************************
 *   Copyright (C) 2007-2009 by Marcel Hasler                              *
 *   mahasler@gmail.com                                                    *
 *                                                                         *
 *   This file is part of KGmailNotifier.                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.  *
 ***************************************************************************/

#include "wallet.h"

#include <iostream>
using namespace std;

// ------------------------------------------------------------------------------------------------------------------- //
//    Construction & Destruction                                                                                       //
// ------------------------------------------------------------------------------------------------------------------- //

Wallet::Wallet()
    : m_wallet(0)
{
}

// ------------------------------------------------------------------------------------------------------------------- //

Wallet::~Wallet()
{
    if (m_wallet)
        delete m_wallet;
}


// ------------------------------------------------------------------------------------------------------------------- //
//    Public methods                                                                                                   //
// ------------------------------------------------------------------------------------------------------------------- //

void Wallet::writePassword(const QString& password)
{
    this->openWallet();

    if (m_wallet)
    {
        if (!m_wallet->hasFolder("Mirall"))
            m_wallet->createFolder("Mirall");

        if (m_wallet->setFolder("Mirall"))
            m_wallet->writePassword("Password", password);
    }
    else
        cerr << "In Wallet::writePassword(): Error: Couldn't connect to KWallet!" << endl;

    this->closeWallet();
}

// ------------------------------------------------------------------------------------------------------------------- //

QString Wallet::readPassword()
{
    QString password;

    this->openWallet();

    if (m_wallet)
    {
        if (m_wallet->setFolder("Mirall"))
            m_wallet->readPassword("Password", password);
    }
    else
        cerr << "In Wallet::readPassword(): Error: Couldn't connect to KWallet!" << endl;

    this->closeWallet();

    return password;
}

// ------------------------------------------------------------------------------------------------------------------- //

void Wallet::deletePassword()
{
    this->openWallet();

    if (m_wallet)
    {
        if (m_wallet->hasFolder("Mirall"))
            m_wallet->removeFolder("Mirall");
    }
    else
        cerr << "In Wallet::deletePassword(): Error: Couldn't connect to KWallet!" << endl;

    this->closeWallet();
}


// ------------------------------------------------------------------------------------------------------------------- //
//    Private helpers                                                                                                  //
// ------------------------------------------------------------------------------------------------------------------- //

void Wallet::openWallet()
{
    static bool firstTimeOpen = true;

    if (firstTimeOpen)
    {
        if (KWallet::Wallet::isOpen(KWallet::Wallet::NetworkWallet()))
            KWallet::Wallet::disconnectApplication(KWallet::Wallet::NetworkWallet(), "Mirall");

        firstTimeOpen = false;
    }

    if (!m_wallet)
        m_wallet = KWallet::Wallet::openWallet(KWallet::Wallet::NetworkWallet(), 0);
}

// ------------------------------------------------------------------------------------------------------------------- //

void Wallet::closeWallet()
{
    KWallet::Wallet::closeWallet(KWallet::Wallet::NetworkWallet(), false);

    if (m_wallet)
    {
        delete m_wallet;
        m_wallet = 0;
    }
}

// ------------------------------------------------------------------------------------------------------------------- //

//#include "wallet.moc"
