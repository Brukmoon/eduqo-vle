TEMPLATE = app

CONFIG += c++11
QT += widgets qml quick webkit sql xml

SOURCES += main.cpp \
    login.cpp \
    settings.cpp \
    courselistmodel.cpp \
    user.cpp \
    database.cpp \
    coursehandler.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=

HEADERS += \
    settings.h \
    course.h \
    courselistmodel.h \
    login.h \
    user.h \
    database.h \
    coursehandler.h
