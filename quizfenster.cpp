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
    setzeAuswahlA ( KeineAntwort );
    setzeAuswahlB ( KeineAntwort );
    _ui.lblFrage->setText ( frage.getFrage() );
    _ui.qkAntwortA->setText ( QString::fromUtf8 ( "A: " ) + frage.getAntwortA() );
    _ui.qkAntwortB->setText ( QString::fromUtf8 ( "B: " ) + frage.getAntwortB() );
    _ui.qkAntwortC->setText ( QString::fromUtf8 ( "C: " ) + frage.getAntwortC() );
    _ui.qkAntwortD->setText ( QString::fromUtf8 ( "D: " ) + frage.getAntwortD() );
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

void QuizFenster::setzeAuswahlA ( const QuizFenster::AntwortAuswahl auswahl )
{
    if ( _auswahlA == auswahl )
        return;
    _auswahlA = auswahl;
    _ui.qkAntwortA->setGruppeAaktiv ( false );
    _ui.qkAntwortB->setGruppeAaktiv ( false );
    _ui.qkAntwortC->setGruppeAaktiv ( false );
    _ui.qkAntwortD->setGruppeAaktiv ( false );
    switch ( _auswahlA )
    {
    case AntwortA:
        _ui.qkAntwortA->setGruppeAaktiv ( true );
        break;
    case AntwortB:
        _ui.qkAntwortB->setGruppeAaktiv ( true );
        break;
    case AntwortC:
        _ui.qkAntwortC->setGruppeAaktiv ( true );
        break;
    case AntwortD:
        _ui.qkAntwortD->setGruppeAaktiv ( true );
        break;
    case KeineAntwort:
    default:
        break;
    }
}

void QuizFenster::setzeAuswahlB ( const QuizFenster::AntwortAuswahl auswahl )
{
    if ( _auswahlB == auswahl )
        return;
    _auswahlB = auswahl;
    _ui.qkAntwortA->setGruppeBaktiv ( false );
    _ui.qkAntwortB->setGruppeBaktiv ( false );
    _ui.qkAntwortC->setGruppeBaktiv ( false );
    _ui.qkAntwortD->setGruppeBaktiv ( false );
    switch ( _auswahlB )
    {
    case AntwortA:
        _ui.qkAntwortA->setGruppeBaktiv ( true );
        break;
    case AntwortB:
        _ui.qkAntwortB->setGruppeBaktiv ( true );
        break;
    case AntwortC:
        _ui.qkAntwortC->setGruppeBaktiv ( true );
        break;
    case AntwortD:
        _ui.qkAntwortD->setGruppeBaktiv ( true );
        break;
    case KeineAntwort:
    default:
        break;
    }
}

void QuizFenster::beenden()
{
    _ende = true;
    hide();
}

#include "quizfenster.moc"
