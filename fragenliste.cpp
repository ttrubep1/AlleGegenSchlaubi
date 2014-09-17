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

#include <stdexcept>

#include "fragenliste.h"

FragenListe::FragenListe() : QAbstractListModel()
{

}

FragenListe::~FragenListe()
{

}

QVariant FragenListe::data ( const QModelIndex& queriedindex, int queriedrole ) const
{
    switch ( queriedrole )
    {
    case Qt::DisplayRole:
        if ( queriedindex == QModelIndex() )
            return QVariant();
        if ( ( size_t ) queriedindex.row() >= _fragen.size() )
            throw std::out_of_range ( "queriedindex.row() zu groß in FragenListe::data()" );
        return QVariant::fromValue<QString> ( _fragen[queriedindex.row()].getTitel() );
        break;
    case Qt::UserRole:
        if ( queriedindex == QModelIndex() )
            return QVariant();
        if ( ( size_t ) queriedindex.row() >= _fragen.size() )
            throw std::out_of_range ( "queriedindex.row() zu groß in FragenListe::data()" );
        return QVariant::fromValue<int> ( queriedindex.row() );
        break;
    default:
        return QVariant();
    }
}

int FragenListe::rowCount ( const QModelIndex& parentindex ) const
{
    Q_UNUSED ( parentindex );
    return ( int ) _fragen.size();
}

void FragenListe::neueFrage ( const Frage& frage )
{
    beginInsertRows ( QModelIndex(), ( int ) _fragen.size(), ( int ) _fragen.size() );
    _fragen.push_back ( frage );
    endInsertRows();
}

void FragenListe::neueFrage ( Frage&& frage )
{
    beginInsertRows ( QModelIndex(), ( int ) _fragen.size(), ( int ) _fragen.size() );
    _fragen.push_back ( std::move ( frage ) );
    endInsertRows();
}

Frage& FragenListe::holeFrage ( const size_t nummer )
{
    if ( nummer >= _fragen.size() )
        throw std::out_of_range ( "Fragennummer zu groß in FragenListe::holeFrage()" );
    return _fragen[nummer];
}

void FragenListe::loescheFrage ( const size_t nummer )
{
    if ( nummer >= _fragen.size() )
        throw std::out_of_range ( "Fragennummer zu groß in FragenListe::loescheFrage()" );
    beginRemoveRows ( QModelIndex(), ( int ) nummer, ( int ) nummer );
    _fragen.erase ( _fragen.begin() + nummer );
    endRemoveRows();
}

void FragenListe::loescheAlles()
{
    beginRemoveRows ( QModelIndex(), 0, ( int ) _fragen.size() );
    _fragen.clear();
    endRemoveRows();
}

void FragenListe::schiebeFrageHoch ( const size_t nummer )
{
    if ( nummer >= _fragen.size() )
        throw std::out_of_range ( "Fragennummer zu groß in FragenListe::schiebeFrageHoch()" );
    if ( nummer == 0 )
        return; // Erste Frage kann nicht hochgeschoben werden
    std::swap<Frage> ( _fragen[nummer], _fragen[nummer-1] );
    emit dataChanged ( index ( ( int ) nummer-1 ), index ( ( int ) nummer ) );
}

void FragenListe::schiebeFrageRunter ( const size_t nummer )
{
    if ( nummer >= _fragen.size() )
        throw std::out_of_range ( "Fragennummer zu groß in FragenListe::schiebeFrageHoch()" );
    if ( nummer == _fragen.size() -1 )
        return; // Letzte Frage kann nicht runtergeschoben werden
    std::swap<Frage> ( _fragen[nummer], _fragen[nummer+1] );
    emit dataChanged ( index ( ( int ) nummer ), index ( ( int ) nummer+1 ) );
}

FragenListe::FragenVektor::iterator FragenListe::begin()
{
    return _fragen.begin();
}

FragenListe::FragenVektor::iterator FragenListe::end()
{
    return _fragen.end();
}

FragenListe::FragenVektor::const_iterator FragenListe::begin() const
{
    return _fragen.begin();
}

FragenListe::FragenVektor::const_iterator FragenListe::end() const
{
    return _fragen.end();
}
