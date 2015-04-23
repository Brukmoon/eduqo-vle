#include "courselistmodel.h"

CourseListModel::CourseListModel(QObject *parent) : QAbstractListModel(parent)
{}

CourseListModel::~CourseListModel()
{}

void CourseListModel::addCourse(const Course &crs)
{
    courses.append(crs);
}

QHash<int, QByteArray> CourseListModel::roleNames() const
{
    QHash<int, QByteArray> rNames;
    rNames[TITLE] = "title";
    rNames[CATEGORY] = "category";
    rNames[AUTHOR] = "author";
    rNames[LOCAL] = "local";
    return rNames;
}

QVariant CourseListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= courses.size())
        return QVariant();
    switch(role) {
    case TITLE:
        return courses.at(index.row()).title;
    case CATEGORY:
        return courses.at(index.row()).category;
    case AUTHOR:
        return courses.at(index.row()).author;
    case LOCAL:
        return courses.at(index.row()).local;
    default:
        return QVariant();
    }
}

int CourseListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return courses.size();
}
