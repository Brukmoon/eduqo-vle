#include <QDebug>
#include <QDir>
#include <QFile>
#include <QSqlQuery>
#include <QQmlContext>
#include <QSortFilterProxyModel>
#include <QtXml>
#include "coursehandler.h"
#include "courselistmodel.h"
#include "settings.h"

CourseHandler::CourseHandler(QQmlContext* context, QObject *parent) : QObject(parent)
{
    model = new CourseListModel(this); // Zanikne spolu se svým manipulátorem
    /* Vytvoření proxy modelu pro řazení a filtraci přes regularni vyrazy
     * Není nutné model znovu inicializovat při změně regexp -> snížení zatížení
     *
     * */
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(qobject_cast<QAbstractItemModel*>(model));
    // Řazení implicitně podle titulu kurzu
    proxyModel->setFilterRole(CourseListModel::TITLE);
    context->setContextProperty("listmodel", proxyModel);
}

CourseHandler::~CourseHandler()
{}

/*
 * TODO: Přidej načtení externích kurzů z databáze -> slot, připoj k loginu, proxyModel
 * se automaticky zaktualizuje
 *
 * */
void CourseHandler::loadRemoteCourses()
{
    qDebug() << __func__ << ": Not implemented.";
}

void CourseHandler::loadLocalCourses()
{
    Settings settings;
    QFile file(settings.getValue("courses/sourceDir", "./courses").toString() + "/courselist.xml");
    // Soubor musí existovat a musí ho být možné otevřít.
    if(!file.exists()) { //TODO: implementuj recovery system.
        qDebug() << __func__ << ": File courselist.xml does not appear to exist in the course folder.";
        return;
    }
    else if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    // Interní reprezentace XML dokumentu
    QDomDocument doc;
    if(!doc.setContent(&file)) {
        qDebug() << __func__ << ": XML DOM error.";
        file.close(); // Nezapomeň uzavřít tok
        return;
    }
    // Dokument je načten, můžeš zavřít soubor
    file.close();

    // Nastav jako počáteční bod parsování kořen XML stromu
    QDomElement root = doc.documentElement();
    if(root.tagName() != "courseList")
    {
        // Soubor je uzavřený, ale stále mohu vyextrahovat jeho cestu pro lepší zdokumentování chyby
        qDebug() << __func__ << ": " << file.fileName() + " is corrupted.";
        return;
    }
    // Vše je v pořádku, začni parsovat od prvního potomka kořene.
    parseCourseList(root.firstChild());
}

void CourseHandler::parseCourseList(QDomNode node)
{
    // Pomocná proměnná, použitá ke kopírování kurzů do modelu
    Course temp;
    while(!node.isNull()) { // Dokud nedosáhneš posledního prvku v zadaném podstromu
        QDomElement e = node.toElement();
        if(!e.hasChildNodes()) { // Chybná struktura stromu.
            qDebug() << __func__ << ": Corrupted course, skipping.";
        } else { // Stále je možné, že struktura bude chybná (chybějící tagy)
            QDomElement child = e.firstChildElement();
            while(!child.isNull())
            {
                // Absence jednotlivých vlastností kurzů zatím není kontrolována.
                if(child.tagName() == "title")
                    temp.title = child.text();
                else if(child.tagName() == "category")
                    temp.category = child.text();
                else if(child.tagName() == "author")
                    temp.author = child.text();
                else if(child.tagName() == "source")
                    temp.url = child.text();
                else
                    qDebug() << __func__ << ": Unknown course tag " << child.tagName();
                child = child.nextSiblingElement();
            }
            model->addCourse(temp);
        }
        node = node.nextSiblingElement("course"); // další element s tagem course
    }
}
