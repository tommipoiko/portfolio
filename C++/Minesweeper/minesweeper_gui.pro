QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gameboard.cpp \
    gameboard.cpp \
    main.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow.cpp \
    optionswindow.cpp \
    optionswindow.cpp \
    square.cpp \
    square.cpp

HEADERS += \
    gameboard.hh \
    gameboard.hh \
    mainwindow.hh \
    mainwindow.hh \
    optionswindow.hh \
    optionswindow.hh \
    square.hh \
    square.hh

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    instructions.txt \
    minesweeper_gui.pro.user

RESOURCES += \
    Resources/mainwindow.qrc
