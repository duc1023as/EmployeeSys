QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    component/comboboxmodel.cpp \
    component/querymodel.cpp \
    db/databaseutils.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    component/comboboxmodel.h \
    component/querymodel.h \
    db/databaseutils.h \
    globalVariables.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc

DISTFILES += \
    img/AddIcon.png \
    img/DeleteUser.png \
    img/SearchIcon.png \
    img/UpdateUser.png \
    img/aboutIcon.png \
    img/avatar.png \
    img/company.jpg \
    img/company.png \
    img/department.png \
    img/employee.png \
    img/login.png \
    img/logout.png \
    img/project.png \
    img/techIcon.png
