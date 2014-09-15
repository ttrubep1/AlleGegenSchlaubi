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

#include "frage.h"

Frage::Frage ( QString frage, QString antwortA, QString antwortB, QString antwortC, QString antwortD, Frage::RichtigeAntwort richtig ) noexcept
:
_frage ( frage ),
       _antwortA ( antwortA ),
       _antwortB ( antwortB ),
       _antwortC ( antwortC ),
       _antwortD ( antwortD ),
       _richtig ( richtig )
{}

Frage::Frage ( const Frage& other ) noexcept
:
_frage ( other._frage ),
_antwortA ( other._antwortA ),
_antwortB ( other._antwortB ),
_antwortC ( other._antwortC ),
_antwortD ( other._antwortD ),
_richtig ( other._richtig )
{}

Frage::Frage ( Frage&& other ) noexcept
:
_frage ( std::move ( other._frage ) ),
_antwortA ( std::move ( other._antwortA ) ),
_antwortB ( std::move ( other._antwortB ) ),
_antwortC ( std::move ( other._antwortC ) ),
_antwortD ( std::move ( other._antwortD ) ),
_richtig ( other._richtig )
{}

Frage::~Frage() noexcept
{}

Frage& Frage::operator= ( const Frage& other ) noexcept
{
    if ( this != &other )
    {
        _frage = other._frage;
        _antwortA = other._antwortA;
        _antwortB = other._antwortB;
        _antwortC = other._antwortC;
        _antwortD = other._antwortD;
        _richtig = other._richtig;
    }
    return *this;
}


Frage& Frage::operator= ( Frage&& other ) noexcept
{
    if ( this != &other )
    {
        _frage = std::move ( other._frage );
        _antwortA = std::move ( other._antwortA );
        _antwortB = std::move ( other._antwortB );
        _antwortC = std::move ( other._antwortC );
        _antwortD = std::move ( other._antwortD );
        _richtig = other._richtig;
    }
    return *this;
}

bool Frage::operator== ( const Frage& other ) const noexcept
{
    return ( _frage == other._frage ) && ( _antwortA == other._antwortA ) && ( _antwortB == other._antwortB ) && ( _antwortC == other._antwortC ) && ( _antwortD == other._antwortD ) && ( _richtig == other._richtig );
}

QString Frage::getFrage() const noexcept
{
    return _frage;
}

void Frage::setFrage ( const QString frage ) noexcept
{
    _frage = frage;
}

QString Frage::getAntwortA() const noexcept
{
    return _antwortA;
}

void Frage::setAntwortA ( const QString antwort ) noexcept
{
    _antwortA = antwort;
}

QString Frage::getAntwortB() const noexcept
{
    return _antwortB;
}

void Frage::setAntwortB ( const QString antwort ) noexcept
{
    _antwortB = antwort;
}

QString Frage::getAntwortC() const noexcept
{
    return _antwortC;
}

void Frage::setAntwortC ( const QString antwort ) noexcept
{
    _antwortC = antwort;
}

QString Frage::getAntwortD() const noexcept
{
    return _antwortD;
}

void Frage::setAntwortD ( const QString antwort ) noexcept
{
    _antwortD = antwort;
}

Frage::RichtigeAntwort Frage::getRichtig() const noexcept
{
    return _richtig;
}

void Frage::setRichtig ( const Frage::RichtigeAntwort richtig ) noexcept
{
    _richtig = richtig;
}
