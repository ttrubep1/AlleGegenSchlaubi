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

#ifndef QUIZFENSTER_H
#define QUIZFENSTER_H

#include <QMainWindow>

#include "frage.h"
#include "punkteab.h"
#include "ui_quizfenster.h"

class QuizFenster : public QMainWindow
{
    Q_OBJECT
public:
    enum AntwortAuswahl : short unsigned int
    {
        KeineAntwort = 0,
        AntwortA = 1,
        AntwortB = 2,
        AntwortC = 3,
        AntwortD = 4
    };
private:
    PunkteAB& _punkte;
    bool _ende;
    Ui::QuizFenster _ui;
    AntwortAuswahl _auswahlA = KeineAntwort;
    AntwortAuswahl _auswahlB = KeineAntwort;
private slots:
    void aktualisierePunktestand();
protected:
    virtual void closeEvent ( QCloseEvent* closeargs );
public:
    QuizFenster ( PunkteAB& punkte );
    virtual ~QuizFenster();
    QuizFenster ( const QuizFenster& other ) = delete;
    QuizFenster ( QuizFenster&& other ) = delete;
    QuizFenster& operator= ( const QuizFenster& other ) = delete;
    QuizFenster& operator= ( QuizFenster&& other ) = delete;
    void zeigeFrage ( const Frage& frage );
    void setzeAuswahlA ( const AntwortAuswahl auswahl );
    void setzeAuswahlB ( const AntwortAuswahl auswahl );
    void beenden();
};

#endif // QUIZFENSTER_H
