/*
 * AlleGegenSchlaubi - educational quiz game
 * Copyright (C) 2014  Tobias Triffterer <tobias@ep1.ruhr-uni-bochum.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef PUNKTEAB_H
#define PUNKTEAB_H

#include <QObject>

class PunkteAB : public QObject
{
    Q_OBJECT
private:
    unsigned int _punkteA;
    unsigned int _punkteB;
public:
    PunkteAB ( unsigned int neuPunkteA = 0, unsigned int neuPunkteB = 0 ) noexcept;
    PunkteAB ( const PunkteAB& other ) noexcept;
    PunkteAB ( PunkteAB&& other ) noexcept;
    ~PunkteAB() noexcept;
    PunkteAB& operator= ( const PunkteAB& other ) noexcept;
    PunkteAB& operator= ( PunkteAB&& other ) noexcept;
    bool operator== ( const PunkteAB& other ) noexcept;
    unsigned int punkteA() const noexcept;
    void punkteAplusEins() noexcept;
    void setzePunkteA ( const unsigned int punkte ) noexcept;
    unsigned int punkteB() const noexcept;
    void punkteBplusEins() noexcept;
    void setzePunkteB ( const unsigned int punkte ) noexcept;
signals:
    void punkteGeaendert();
};

#endif // PUNKTEAB_H
