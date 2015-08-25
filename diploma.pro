#-------------------------------------------------
#
# Project created by QtCreator 2015-08-11T08:07:57
#
#-------------------------------------------------

QT += gui
QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = diploma
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    QDPoint.cpp \
    operators.cpp \
    finiteelement.cpp \
    net.cpp \
    mfe.cpp \    
    matrixlu.cpp \
    index3.cpp \
    myglwidget.cpp

HEADERS  += mainwindow.h \
    QDPoint.h \
    operators.h \
    finiteelement.h \
    net.h \
    mfe.h \    
    matrixlu.h \
    index3.h \
    geometry.h \
    lib.h \
    myglwidget.h

FORMS    += mainwindow.ui
OTHER_FILES +=
RESOURCES +=
RC_FILE += appIcon.rc

DISTFILES += \
    NetInfo.txt \
    Finiteelement.txt



