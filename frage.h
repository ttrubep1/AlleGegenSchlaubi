/**
 * @file frage.h
 *
 * @author Tobias Triffterer
 *
 * @brief Container-Klasse für Fragen
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

#ifndef FRAGE_H
#define FRAGE_H

#include <QString>

class Frage final
{
public:
    enum RichtigeAntwort : short unsigned int
    {
        Arichtig = 1,
        Brichtig = 2,
        Crichtig = 3,
        Drichtig = 4
    };
private:
    QString _titel;
    QString _frage;
    QString _antwortA;
    QString _antwortB;
    QString _antwortC;
    QString _antwortD;
    RichtigeAntwort _richtig;
public:
    Frage ( QString titel, QString frage, QString antwortA, QString antwortB, QString antwortC, QString antwortD, RichtigeAntwort richtig ) noexcept;
    Frage ( const Frage& other ) noexcept;
    Frage ( Frage&& other ) noexcept;
    ~Frage() noexcept;
    Frage& operator= ( const Frage& other ) noexcept;
    Frage& operator= ( Frage&& other ) noexcept;
    bool operator== ( const Frage& other ) const noexcept;
    QString getTitel() const noexcept;
    void setTitel ( const QString titel ) noexcept;
    QString getFrage() const noexcept;
    void setFrage ( const QString frage ) noexcept;
    QString getAntwortA() const noexcept;
    void setAntwortA ( const QString antwort ) noexcept;
    QString getAntwortB() const noexcept;
    void setAntwortB ( const QString antwort ) noexcept;
    QString getAntwortC() const noexcept;
    void setAntwortC ( const QString antwort ) noexcept;
    QString getAntwortD() const noexcept;
    void setAntwortD ( const QString antwort ) noexcept;
    RichtigeAntwort getRichtig() const noexcept;
    void setRichtig ( const RichtigeAntwort richtig ) noexcept;
};

#endif // FRAGE_H
