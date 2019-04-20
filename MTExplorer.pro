#-------------------------------------------------
#
# Project created by QtCreator 2019-04-02T18:30:28
#
#-------------------------------------------------

QT       += core network gui xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MTExplorer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    agentmanager.cpp \
    agentdialog.cpp \
    agentinfo.cpp \
    deviceinfo.cpp \
    requestmanager.cpp \
    xmlsyntaxhighlighter.cpp

HEADERS += \
        mainwindow.h \
    agentmanager.h \
    agentdialog.h \
    agentinfo.h \
    deviceinfo.h \
    requestmanager.h \
    xmlsyntaxhighlighter.h

FORMS += \
        mainwindow.ui \
    agentdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    mtexplorer.qrc

#
# special setting for Anroid and Windows
# if agent is accessed via https, it requires openssl library
# Android - generate openssl library based on the Android's architect platform
#           and update the below locations
# Windows - add the location of libcrypto.dll and libsll.dll to the PATH system variable.
#
contains(ANDROID_TARGET_ARCH, x86) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/../android-openssl/jni/openssl/arch-x86/lib/libcrypto.so \
        $$PWD/../android-openssl/jni/openssl/arch-x86/lib/libssl.so
}
