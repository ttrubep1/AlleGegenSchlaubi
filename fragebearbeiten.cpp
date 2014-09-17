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

#include "fragebearbeiten.h"

#include "steuerfenster.h"

FrageBearbeiten::FrageBearbeiten ( Frage& frage, SteuerFenster& steuerung )
    : QDialog ( &steuerung ),
      _frage ( frage ),
      _steuerung ( steuerung )
{
    _ui.setupUi ( this );
    _ui.txtTitel->setText ( _frage.getTitel() );
    _ui.txtFrage->setPlainText ( _frage.getFrage() );
    _ui.txtAntwortA->setPlainText ( _frage.getAntwortA() );
    _ui.txtAntwortB->setPlainText ( _frage.getAntwortB() );
    _ui.txtAntwortC->setPlainText ( _frage.getAntwortC() );
    _ui.txtAntwortD->setPlainText ( _frage.getAntwortD() );
    switch ( _frage.getRichtig() )
    {
    case Frage::Arichtig:
        _ui.rdbRichtigA->setChecked ( true );
        break;
    case Frage::Brichtig:
        _ui.rdbRichtigB->setChecked ( true );
        break;
    case Frage::Crichtig:
        _ui.rdbRichtigC->setChecked ( true );
        break;
    case Frage::Drichtig:
        _ui.rdbRichtigD->setChecked ( true );
        break;
    }
}

FrageBearbeiten::~FrageBearbeiten()
{
}

bool FrageBearbeiten::bearbeiteFrage ( Frage& frage, SteuerFenster& steuerung )
{
    FrageBearbeiten editor ( frage, steuerung );
    const int result = editor.exec();
    if ( result == QDialog::Accepted )
    {
        frage.setTitel ( editor._ui.txtTitel->text() );
        frage.setFrage ( editor._ui.txtFrage->toPlainText() );
        frage.setAntwortA ( editor._ui.txtAntwortA->toPlainText() );
        frage.setAntwortB ( editor._ui.txtAntwortB->toPlainText() );
        frage.setAntwortC ( editor._ui.txtAntwortC->toPlainText() );
        frage.setAntwortD ( editor._ui.txtAntwortD->toPlainText() );
        if ( editor._ui.rdbRichtigA->isChecked() )
            frage.setRichtig ( Frage::Arichtig );
        if ( editor._ui.rdbRichtigB->isChecked() )
            frage.setRichtig ( Frage::Brichtig );
        if ( editor._ui.rdbRichtigC->isChecked() )
            frage.setRichtig ( Frage::Crichtig );
        if ( editor._ui.rdbRichtigD->isChecked() )
            frage.setRichtig ( Frage::Drichtig );
	return true;
    }
    return false;
}

#include "fragebearbeiten.moc"
