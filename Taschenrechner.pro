QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    allgemein.cpp \
    basictaschenrechner.cpp \
    komplex.cpp \
    main.cpp \
    mainwindow.cpp \
    matrix.cpp \
    matrizen.cpp \
    nullstelle.cpp \
    nullstellenfinder.cpp \
    qcustomplot.cpp \
    random.cpp \
    regression.cpp




HEADERS += \
    allgemein.h \
    basictaschenrechner.h \
    komplex.h \
    mainwindow.h \
    matrix.h \
    matrizen.h \
    nullstelle.h \
    nullstellenfinder.h \
    qcustomplot.h \
    random.h \
    regression.h




FORMS += \
    basictaschenrechner.ui \
    mainwindow.ui \
    matrix.ui \
    nullstellenfinder.ui \
    random.ui \
    regression.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md
