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

#include <QXmlStreamReader>
#include <QXmlStreamWriter>

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

const Frage& FragenListe::constHoleFrage ( const size_t nummer ) const
{
    if ( nummer >= _fragen.size() )
        throw std::out_of_range ( "Fragennummer zu groß in FragenListe::holeFrage()" );
    return _fragen[nummer];
}

void FragenListe::geaendertFrage ( const size_t nummer )
{
    if ( nummer >= _fragen.size() )
        throw std::out_of_range ( "Fragennummer zu groß in FragenListe::geaendertFrage()" );
    emit dataChanged ( index ( ( int ) nummer ), index ( ( int ) nummer ) );
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

void FragenListe::oeffneFragen ( QIODevice*const quelle )
{
    FragenVektor temp;
    QXmlStreamReader xml ( quelle );
    bool inHauptelement = false;
    bool inFragenelement = false;
    bool gelesenTitel = false;
    bool gelesenFrage = false;
    bool gelesenAntwortA = false;
    bool gelesenAntwortB = false;
    bool gelesenAntwortC = false;
    bool gelesenAntwortD = false;
    bool gelesenRichtig = false;
    QString titel;
    QString frage;
    QString antwortA;
    QString antwortB;
    QString antwortC;
    QString antwortD;
    Frage::RichtigeAntwort richtig = Frage::Arichtig; // Der Compiler verlangt einen Standard-Wert
    while ( !xml.atEnd() )
    {
        switch ( xml.readNext() )
        {
        case QXmlStreamReader::NoToken:
        case QXmlStreamReader::DTD:
        case QXmlStreamReader::ProcessingInstruction:
        case QXmlStreamReader::StartDocument:
        case QXmlStreamReader::Comment:
        case QXmlStreamReader::EndDocument:
        case QXmlStreamReader::Characters:
        case QXmlStreamReader::EntityReference:
            break; // Ist hier nicht relevant
        case QXmlStreamReader::StartElement:
            if ( !inHauptelement )
            {
                // Außerhalb des Hauptelementes, d.h. dieses muss hier beginnen:
                if ( xml.name() != QString::fromUtf8 ( "AlleGegenSchlaubi" ) )
                    throw std::runtime_error ( "Ungültiges Hauptelement in der XML-Datei!" );
                else
                    inHauptelement = true;
            }
            else
            {
                if ( !inFragenelement )
                {
                    // Hier muss nun ein Fragen-Block kommen
                    if ( xml.name() != QString::fromUtf8 ( "Fragenliste" ) )
                        throw std::runtime_error ( "Unbekanntes XML-Element anstelle eines <Fragenliste>-Blocks!" );
                    else
                    {
                        inFragenelement = true;
                        gelesenTitel = false;
                        gelesenFrage = false;
                        gelesenAntwortA = false;
                        gelesenAntwortB = false;
                        gelesenAntwortC = false;
                        gelesenAntwortD = false;
                        gelesenRichtig = false;
                    }
                }
                else
                {
                    // Unterscheidung der einzelnen Parameter einer Frage
                    if ( xml.name() == QString::fromUtf8 ( "Titel" ) )
                    {
                        titel = xml.readElementText ( QXmlStreamReader::ErrorOnUnexpectedElement );
                        gelesenTitel = true;
                    }
                    else if ( xml.name() == QString::fromUtf8 ( "Frage" ) )
                    {
                        frage = xml.readElementText ( QXmlStreamReader::ErrorOnUnexpectedElement );
                        gelesenFrage = true;
                    }
                    else if ( xml.name() == QString::fromUtf8 ( "AntwortA" ) )
                    {
                        antwortA = xml.readElementText ( QXmlStreamReader::ErrorOnUnexpectedElement );
                        gelesenAntwortA = true;
                    }
                    else if ( xml.name() == QString::fromUtf8 ( "AntwortB" ) )
                    {
                        antwortB = xml.readElementText ( QXmlStreamReader::ErrorOnUnexpectedElement );
                        gelesenAntwortB = true;
                    }
                    else if ( xml.name() == QString::fromUtf8 ( "AntwortC" ) )
                    {
                        antwortC = xml.readElementText ( QXmlStreamReader::ErrorOnUnexpectedElement );
                        gelesenAntwortC = true;
                    }
                    else if ( xml.name() == QString::fromUtf8 ( "AntwortD" ) )
                    {
                        antwortD = xml.readElementText ( QXmlStreamReader::ErrorOnUnexpectedElement );
                        gelesenAntwortD = true;
                    }
                    else if ( xml.name() == QString::fromUtf8 ( "Richtig" ) )
                    {
                        richtig = textzuEnum ( xml.readElementText ( QXmlStreamReader::ErrorOnUnexpectedElement ) );
                        gelesenRichtig = true;
                    }
                    else
                    {
                        throw std::runtime_error ( "Unbekanntes XML-Element im <Fragenliste>-Block!" );
                    }
                }
            }
            break;
        case QXmlStreamReader::EndElement:
            if ( inHauptelement )
            {
                if ( inFragenelement )
                {
                    if ( xml.name() == QString::fromUtf8 ( "Fragenliste" ) )
                    {
                        // Fragenelement beendet, alle Daten müssen vorhanden sein:
                        if ( !gelesenTitel )
                            throw std::runtime_error ( "Unvollständiges Fragenliste-Element: Titel fehlt!" );
                        if ( !gelesenFrage )
                            throw std::runtime_error ( "Unvollständiges Fragenliste-Element: Frage fehlt!" );
                        if ( !gelesenAntwortA )
                            throw std::runtime_error ( "Unvollständiges Fragenliste-Element: AntwortA fehlt!" );
                        if ( !gelesenAntwortB )
                            throw std::runtime_error ( "Unvollständiges Fragenliste-Element: AntwortB fehlt!" );
                        if ( !gelesenAntwortC )
                            throw std::runtime_error ( "Unvollständiges Fragenliste-Element: AntwortC fehlt!" );
                        if ( !gelesenAntwortD )
                            throw std::runtime_error ( "Unvollständiges Fragenliste-Element: AntwortD fehlt!" );
                        if ( !gelesenRichtig )
                            throw std::runtime_error ( "Unvollständiges Fragenliste-Element: Richtig fehlt!" );
                        temp.push_back ( Frage ( titel, frage, antwortA, antwortB, antwortC, antwortD, richtig ) );
                        inFragenelement = false;
                    }
                }
                else
                {
                    if ( xml.name() == QString::fromUtf8 ( "AlleGegenSchlaubi" ) )
                        inHauptelement = false;
                }
            }
            break;
        case QXmlStreamReader::Invalid:
        default:
            throw std::runtime_error ( xml.errorString().toUtf8().data() );
        }
    }
    loescheAlles();
    beginInsertRows ( QModelIndex(), 0, ( int ) temp.size() -1 );
    _fragen = std::move ( temp );
    endInsertRows();
}

void FragenListe::speichereFragen ( QIODevice*const ziel ) const
{
    const QString xmlnamespace = QString::fromUtf8 ( "private://AlleGegenSchlaubi/Fragen.Liste" );
    QXmlStreamWriter xml ( ziel );
    xml.setAutoFormatting ( true );
    xml.writeStartDocument ( QString::fromUtf8 ( "1.0" ) );
    xml.writeDTD ( QString::fromUtf8 ( "<!DOCTYPE AlleGegenSchlaubi SYSTEM \"+//ALLE GEGEN SCHLAUBI/FRAGENLISTE//+\">" ) );
    xml.writeDefaultNamespace ( xmlnamespace );
    xml.writeStartElement ( xmlnamespace, QString::fromUtf8 ( "AlleGegenSchlaubi" ) );
    for ( auto i = _fragen.begin(); i != _fragen.end(); i++ )
    {
        xml.writeStartElement ( xmlnamespace, QString::fromUtf8 ( "Fragenliste" ) );
        xml.writeTextElement ( xmlnamespace, QString::fromUtf8 ( "Titel" ), ( *i ).getTitel() );
        xml.writeTextElement ( xmlnamespace, QString::fromUtf8 ( "Frage" ), ( *i ).getFrage() );
        xml.writeTextElement ( xmlnamespace, QString::fromUtf8 ( "AntwortA" ), ( *i ).getAntwortA() );
        xml.writeTextElement ( xmlnamespace, QString::fromUtf8 ( "AntwortB" ), ( *i ).getAntwortB() );
        xml.writeTextElement ( xmlnamespace, QString::fromUtf8 ( "AntwortC" ), ( *i ).getAntwortC() );
        xml.writeTextElement ( xmlnamespace, QString::fromUtf8 ( "AntwortD" ), ( *i ).getAntwortD() );
        xml.writeTextElement ( xmlnamespace, QString::fromUtf8 ( "Richtig" ), enumZuText ( ( *i ).getRichtig() ) );
        xml.writeEndElement();
    }
    xml.writeEndDocument();
}

Frage::RichtigeAntwort FragenListe::textzuEnum ( const QString text )
{
    if ( text == QString::fromUtf8 ( "A" ) )
        return Frage::Arichtig;
    if ( text == QString::fromUtf8 ( "B" ) )
        return Frage::Brichtig;
    if ( text == QString::fromUtf8 ( "C" ) )
        return Frage::Crichtig;
    if ( text == QString::fromUtf8 ( "D" ) )
        return Frage::Drichtig;
    throw std::runtime_error ( "Unbekannter Wert für richtige Antwort in FragenListe::textzuEnum()" );
}

QString FragenListe::enumZuText ( const Frage::RichtigeAntwort wert )
{
    switch ( wert )
    {
    case Frage::Arichtig:
        return QString::fromUtf8 ( "A" );
    case Frage::Brichtig:
        return QString::fromUtf8 ( "B" );
    case Frage::Crichtig:
        return QString::fromUtf8 ( "C" );
    case Frage::Drichtig:
        return QString::fromUtf8 ( "D" );
    }
    throw std::logic_error ( "Unbekannter Wert für richtige Antwort in FragenListe::enumZuText()" );
}
