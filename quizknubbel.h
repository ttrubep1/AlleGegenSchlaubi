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

#ifndef QUIZKNUBBEL_H
#define QUIZKNUBBEL_H

#include <QLabel>
#include <QPoint>

class QuizKnubbel : public QWidget
{
    Q_OBJECT
    Q_PROPERTY ( QString text READ text WRITE setText )
    Q_PROPERTY ( Qt::Alignment alignment READ alignment WRITE setAlignment )
    Q_PROPERTY ( bool gruppeAaktiv READ gruppeAaktiv WRITE setGruppeAaktiv )
    Q_PROPERTY ( bool gruppeBaktiv READ gruppeBaktiv WRITE setGruppeBaktiv )
    Q_PROPERTY ( bool richtig READ richtig WRITE setRichtig )
    Q_PROPERTY ( double opazitaetGruppeA READ opazitaetGruppeA WRITE setOpazitaetGruppeA )
    Q_PROPERTY ( double opazitaetGruppeB READ opazitaetGruppeB WRITE setOpazitaetGruppeB )
    Q_PROPERTY ( QColor farbeHintergrund READ farbeHintergrund WRITE setFarbeHintergrund )
private:
    static const int breiteSchraege = 40;
    static const int breiteGruppenBuchstabe = 60;
    static const int hoeheTextRand = 10;
    static const int versatzGruppenBuchstabe = 12;
    static const int schriftGroesseGruppenBuchstabe = 22;
    static const int minBreite = 505;
    static const int minHoehe = 100;
    static const Qt::GlobalColor farbeNormal = Qt::white;
    static const Qt::GlobalColor farbeRichtig = Qt::green;
    static const int dauerAnimation = 500; // Millisekunden
    QLabel _text;
    QLabel _lblGruppeA;
    QLabel _lblGruppeB;
    QPoint _polypunkt1;
    QPoint _polypunkt2;
    QPoint _polypunkt3;
    QPoint _polypunkt4;
    QPoint _polypunkt5;
    QPoint _polypunkt6;
    QPoint _gruppeAPunktMitte;
    QPoint _gruppeAPunktOben;
    QPoint _gruppeAPunktUnten;
    QPoint _gruppeBPunktMitte;
    QPoint _gruppeBPunktOben;
    QPoint _gruppeBPunktUnten;
    bool _gruppeAaktiv = false;
    bool _gruppeBaktiv = false;
    double _opazitaetGruppeA = -1.0; // Startwert, wird im Konstruktor überschrieben
    double _opazitaetGruppeB = -1.0; // dito
    bool _richtig = false;
    QColor _farbe;
protected:
    double opazitaetGruppeA() const;
    void setOpazitaetGruppeA ( const double opazitaet );
    double opazitaetGruppeB() const;
    void setOpazitaetGruppeB ( const double opazitaet );
    QColor farbeHintergrund() const;
    void setFarbeHintergrund ( const QColor& farbe );
public:
    QuizKnubbel ( QWidget* parentwidget = nullptr );
    ~QuizKnubbel();
    virtual QSize sizeHint();
    virtual QSize minimumSizeHint();
    QuizKnubbel ( const QuizKnubbel& other ) = delete;
    QuizKnubbel ( QuizKnubbel&& other ) = delete;
    QuizKnubbel& operator= ( const QuizKnubbel& other ) = delete;
    QuizKnubbel& operator= ( QuizKnubbel&& other ) = delete;
    virtual QString text() const;
    virtual void setText ( const QString& textneu );
    Qt::Alignment alignment() const;
    void setAlignment ( const Qt::Alignment ausrichtung );
    bool gruppeAaktiv() const;
    void setGruppeAaktiv ( const bool aktiv );
    bool gruppeBaktiv() const;
    void setGruppeBaktiv ( const bool aktiv );
    bool richtig() const;
    void setRichtig ( const bool istrichtig );
protected:
    virtual void paintEvent ( QPaintEvent* paintargs );
    virtual void resizeEvent ( QResizeEvent* resizeargs );
    virtual void changeEvent ( QEvent* changeargs );
    virtual void fontChange ( const QFont& fontneu );
};

#endif // QUIZKNUBBEL_H
