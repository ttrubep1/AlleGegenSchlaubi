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

#include <QCloseEvent>
#include <QMessageBox>

#include "quizfenster.h"

QuizFenster::QuizFenster ( PunkteAB& punkte )
    : _punkte ( punkte ),
      _ende ( false )
{
    _ui.setupUi ( this );
    connect ( &_punkte, SIGNAL ( punkteGeaendert() ), this, SLOT ( aktualisierePunktestand() ) );
}

QuizFenster::~QuizFenster()
{}

void QuizFenster::closeEvent ( QCloseEvent* closeargs )
{
    if ( !_ende )
    {
        closeargs->ignore();
        QMessageBox::warning (
            this,
            QString::fromUtf8 ( "Alle Gegen Schlaubi" ),
            QString::fromUtf8 ( "Zum Beenden des Programmes bitte das Steuerfenster schließen.\nDas Quizfenster wird dann automatisch mit geschlossen." )
        );
    }
}

void QuizFenster::zeigeFrage ( const Frage& frage )
{
    _ui.lblFrage->setText ( frage.getFrage() );
    _ui.lblAntwortA->setText ( frage.getAntwortA() );
    _ui.lblAntwortB->setText ( frage.getAntwortB() );
    _ui.lblAntwortC->setText ( frage.getAntwortC() );
    _ui.lblAntwortD->setText ( frage.getAntwortD() );
}

void QuizFenster::aktualisierePunktestand()
{
    _ui.lblPunkteA->setText (
        QString::fromUtf8 ( "A: " )
        + QString::number ( _punkte.punkteA(), 10 )
    );
    _ui.lblPunkteB->setText (
        QString::fromUtf8 ( "B: " )
        + QString::number ( _punkte.punkteB(), 10 )
    );
}

void QuizFenster::beenden()
{
    _ende = true;
    hide();
}

#include "quizfenster.moc"
