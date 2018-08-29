#-------------------------------------------------
#
# Project created by QtCreator 2018-07-27T20:56:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = designer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(mainwindow/mainwindow.pri)
include(editor/editor.pri)
include(elements/elements.pri)
include(flowline/flowline.pri)
include(layer/layer.pri)
include(util/util.pri)
include(options/options.pri)

SOURCES += \
    main.cpp

RESOURCES += \
    res.qrc
