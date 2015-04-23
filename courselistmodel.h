#ifndef COURSELISTMODEL_H
#define COURSELISTMODEL_H

#include <QAbstractListModel>
#include "course.h"

/*
 * Definuje model kurzů.
 *
 * */
class CourseListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    // Vlastní identifikátory dat v modelu
    enum RoleTypes
    {
        TITLE = Qt::UserRole+1,
        CATEGORY,
        AUTHOR,
        LOCAL
    };

    explicit CourseListModel(QObject* parent = 0);
    virtual ~CourseListModel();

    // Pro Qt Quick, vrací vlastní role
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    // Vrací hodnotu courses[index.row][role] (simplifikace)
    QVariant data(const QModelIndex &index, int role = TITLE) const Q_DECL_OVERRIDE;

    // Počet kurzů v seznamu.
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    // Přidá kurz do seznamu kurzů.
    void addCourse(const Course &crs);
private:
    QList<Course> courses;
};
#endif // COURSELISTMODEL_H
