#include "course.h"

Course::Course(const QString &title, const QString &category, const QString &author, const bool downloaded)
{
    this->author = author;
    this->category = category;
    this->downloaded = downloaded;
    this->title = title;
}

