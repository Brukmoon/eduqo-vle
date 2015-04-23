#ifndef COURSEHANDLER_H
#define COURSEHANDLER_H

#include <QObject>
QT_FORWARD_DECLARE_CLASS(CourseListModel)
QT_FORWARD_DECLARE_CLASS(QQmlContext)
QT_FORWARD_DECLARE_CLASS(QDomNode)

class CourseHandler : public QObject
{
    Q_OBJECT
public:
    explicit CourseHandler(QQmlContext* context = 0, QObject *parent = 0);
    ~CourseHandler();
signals:

public slots:
    void loadLocalCourses();
    void loadRemoteCourses();
private:
    // Načti kurzy
    void parseCourseList(QDomNode node);

    CourseListModel *model;
};

#endif // COURSEHANDLER_H
