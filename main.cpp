/**
 * @file main.cpp
 *
 * @author Tobias Triffterer
 *
 * @brief Einsprungpunkt der ausführbaren Datei
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

#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>
#ifdef __linux
#include <KDE/KComponentData>
#include <KDE/KGlobal>
#include <KDE/KLocale>
#endif

#include "steuerfenster.h"

int main ( int argc, char** argv )
{
    QApplication app ( argc, argv );
    app.setApplicationName ( QString::fromUtf8 ( "AlleGegenSchlaubi" ) );
    app.setApplicationVersion ( QString::fromUtf8 ( "0.0.1" ) );
    // Dieses Programm wird vorerst nur auf Deutsch entwickelt:
    QLocale::setDefault ( QLocale ( QLocale::German, QLocale::Germany ) );
#ifdef __linux
    KComponentData kde4info ( QString::fromUtf8 ( "AlleGegenSchlaubi" ).toUtf8() );
    KGlobal::setActiveComponent( kde4info );
    KGlobal::locale()->setLanguage ( QString::fromUtf8 ( "de" ), nullptr );
#endif
    QTranslator qtSprache;
    qtSprache.load (
        QLocale::system(),
        QString::fromUtf8 ( "qt" ),
        QString::fromUtf8 ( "_" ),
        QLibraryInfo::location ( QLibraryInfo::TranslationsPath )
    );
    app.installTranslator ( &qtSprache );
    SteuerFenster hauptFenster;
    hauptFenster.show();
    return app.exec();
}
