#ifndef COURSE_H
#define COURSE_H
#include <QString>

/*
 * POD (abbr.) struktura uchovávající metadata kurzu.
 *
 * */
struct Course
{
    // Nadpis kurzu
    QString title;

    // Kategorie kurzu
    QString category;

    // Jméno autora kurzu
    QString author;

    // Relativní cesta ke kurzu
    QString url;

    // Doplňková vlastnost; nachází se kurz na lokálním úložišti?
    bool local;
};

#endif // COURSE_H
