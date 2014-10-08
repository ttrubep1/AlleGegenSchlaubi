/**
 * @file punkteab.cpp
 *
 * @author Tobias Triffterer
 *
 * @brief Verwaltung der Punkte der beiden Teams
 *
 * @version 1.0.0
 *
 **/
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

#include "punkteab.h"

PunkteAB::PunkteAB ( unsigned int neuPunkteA, unsigned int neuPunkteB ) noexcept
    : QObject ( nullptr ),
      _punkteA ( neuPunkteA ),
      _punkteB ( neuPunkteB )
{}

PunkteAB::PunkteAB ( const PunkteAB& other ) noexcept
    : QObject ( nullptr ),
      _punkteA ( other._punkteA ),
      _punkteB ( other._punkteB )
{}

PunkteAB::PunkteAB ( PunkteAB&& other ) noexcept
    : QObject ( nullptr ),
      _punkteA ( other._punkteA ),
      _punkteB ( other._punkteB )
{}

PunkteAB::~PunkteAB()
{}

PunkteAB& PunkteAB::operator= ( const PunkteAB& other ) noexcept
{
    if ( this != &other )
    {
        _punkteA = other._punkteA;
        _punkteB = other._punkteB;
    }
    return *this;
}

PunkteAB& PunkteAB::operator= ( PunkteAB&& other ) noexcept
{
    if ( this != &other )
    {
        _punkteA = other._punkteA;
        _punkteB = other._punkteB;
    }
    return *this;
}

bool PunkteAB::operator== ( const PunkteAB& other ) noexcept
{
    return ( _punkteA == other._punkteA ) && ( _punkteB == other._punkteB );
}

unsigned int PunkteAB::punkteA() const noexcept
{
    return _punkteA;
}

void PunkteAB::punkteAplusEins() noexcept
{
    _punkteA++;
    emit punkteGeaendert();
}

void PunkteAB::setzePunkteA ( const unsigned int punkte ) noexcept
{
    _punkteA = punkte;
    emit punkteGeaendert();
}

unsigned int PunkteAB::punkteB() const noexcept
{
    return _punkteB;
}

void PunkteAB::punkteBplusEins() noexcept
{
    _punkteB++;
    emit punkteGeaendert();
}

void PunkteAB::setzePunkteB ( const unsigned int punkte ) noexcept
{
    _punkteB = punkte;
    emit punkteGeaendert();
}

#include "punkteab.moc"
