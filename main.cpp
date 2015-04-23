#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include "courselistmodel.h"
#include "database.h"
#include "user.h"
#include "settings.h"
#include "coursehandler.h"

// Pomocná procedura, nastaví vlastnosti kontextu QML
void setProperties(QQmlContext *context);
// Obsahuje hlavní tok programu.
int main(int argc, char *argv[])
{
    // Inicializuj aplikaci
    QApplication app(argc, argv);
    QApplication::setOrganizationName("EduQo");
    QApplication::setApplicationName("Eduqo-VLE");

    // Vytvoř kontext pro QML
    QQmlApplicationEngine engine;
    // Inicializuj kontext
    auto* context = engine.rootContext();
    // Nastav vlastnosti kontextu
    setProperties(context);
    // Načti okno
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    // Připoj se k databázi (pokud možno)
    if(!database::createConnection())
        qDebug() << "Database connection could not be established.";

    // Předej kontrolu aplikaci
    return app.exec();
}

void setProperties(QQmlContext *context)
{
    if(context == nullptr) {
        // Kontext musí být nejdříve inicializován.
        qDebug() << __func__ << ": Context can't be null.";
        return;
    }
    // Naked pointery nejsou nebezpečné - nehrozí únik paměti, jsou smazány Qt GC
    User *user = new User(context);
    context->setContextProperty("user", user); // Obraz uživatele

    // Instance nastavení pro Qt Quick - Qt (C++) si nastavení alokuje na zásobníku při každé množině dotazů
    Settings *settings = new Settings(context);
    context->setContextProperty("settings", settings);

    CourseHandler *courseHandler = new CourseHandler(context, context);
    // Předpřiprav si model, parsuj lokální XML -> méně zátěže po loginu
    courseHandler->loadLocalCourses();
}
