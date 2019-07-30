#-------------------------------------------------
#
# Project created by QtCreator 2019-04-02T18:30:28
#
#-------------------------------------------------

QT       += core network gui xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets xml

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

win32 {
    RC_FILE = platforms/Windows/MTExplorer.rc

    DISTFILES += \
        platforms/Windows/MTExplorer.ico

    QT_INSTALL_FRAMEWORK_PATH = C:/Qt/QtIFW-3.1.0
    CONFIG(release, debug|release): QMAKE_POST_LINK = $${PWD}/binaries/Windows/createSetup.bat $${PWD} $${OUT_PWD} ${QTDIR} $${QT_INSTALL_FRAMEWORK_PATH}
}

macx {
    ICON = platforms/MacOS/MTExplorer.icns
    CONFIG(release, debug|release): QMAKE_POST_LINK = cd $${OUT_PWD};${QTDIR}/bin/macdeployqt MTExplorer.app -dmg ; cp -pf MTExplorer.dmg $${PWD}/binaries/MacOS
}

ios {
    QMAKE_INFO_PLIST = platforms/ios/Info.plist
    QMAKE_ASSET_CATALOGS += platforms/ios/Assets.xcassets

    DISTFILES += \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/1024.png \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/120.png \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/128.png \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/152.png \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/16.png \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/167.png \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/180.png \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/20.png \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/256.png \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/29.png \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/32.png \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/40.png \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/512.png \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/58.png \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/60.png \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/64.png \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/76.png \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/80.png \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/87.png \
        platforms/ios/Assets.xcassets/AppIcon.appiconset/Contents.json
}

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





