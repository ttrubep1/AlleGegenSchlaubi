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
private:
    static const int breiteSchraege = 40;
    static const int breiteGruppenBuchstabe = 60;
    static const int hoeheTextRand = 10;
    static const int versatzGruppenBuchstabe = 12;
    static const int schriftGroesseGruppenBuchstabe = 22;
    static const int minBreite = 505;
    static const int minHoehe = 100;
    QLabel _text;
    QLabel _gruppeA;
    QLabel _gruppeB;
    QPoint polypunkt1;
    QPoint polypunkt2;
    QPoint polypunkt3;
    QPoint polypunkt4;
    QPoint polypunkt5;
    QPoint polypunkt6;
    QPoint gruppeAPunktMitte;
    QPoint gruppeAPunktOben;
    QPoint gruppeAPunktUnten;
    QPoint gruppeBPunktMitte;
    QPoint gruppeBPunktOben;
    QPoint gruppeBPunktUnten;
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
protected:
    virtual void paintEvent ( QPaintEvent* paintargs );
    virtual void resizeEvent ( QResizeEvent* resizeargs );
    virtual void changeEvent ( QEvent* changeargs );
    virtual void fontChange ( const QFont& fontneu );
};

#endif // QUIZKNUBBEL_H
