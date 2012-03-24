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

#ifndef WALLET_H
#define WALLET_H

#include <QString>
#include <kwallet.h>

class Wallet : public QObject
{
    Q_OBJECT
public:
    Wallet();
    ~Wallet();

    QString readPassword();
    void writePassword(const QString &password);
    void deletePassword();

private:
    void openWallet();
    void closeWallet();

    KWallet::Wallet *m_wallet;
};

#endif // WALLET_H
