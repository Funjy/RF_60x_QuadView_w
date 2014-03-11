# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = RF_60x_QuadView_w
DESTDIR = ./debug
CONFIG += debug
DEFINES += _WINDOWS QT_QUICK_LIB QT_QML_LIB QT_WIDGETS_LIB QT_NETWORK_LIB QT_OPENGL_ES_2 QT_OPENGL_ES_2_ANGLE
INCLUDEPATH += ./../../../../../../Qt/Qt5.2.1_msvc2012_x86/5.2.1/msvc2012/include \
    ./../../../../../../Qt/Qt5.2.1_msvc2012_x86/5.2.1/msvc2012/include/QtQuick \
    ./../../../../../../Qt/Qt5.2.1_msvc2012_x86/5.2.1/msvc2012/include/QtQml \
    ./../../../../../../Qt/Qt5.2.1_msvc2012_x86/5.2.1/msvc2012/include/QtWidgets \
    ./../../../../../../Qt/Qt5.2.1_msvc2012_x86/5.2.1/msvc2012/include/QtNetwork \
    ./../../../../../../Qt/Qt5.2.1_msvc2012_x86/5.2.1/msvc2012/include/QtGui \
    ./../../../../../../Qt/Qt5.2.1_msvc2012_x86/5.2.1/msvc2012/include/QtANGLE \
    ./../../../../../../Qt/Qt5.2.1_msvc2012_x86/5.2.1/msvc2012/include/QtCore \
    ./debug \
    . \
    ./../../../../../../Qt/Qt5.2.1_msvc2012_x86/5.2.1/msvc2012/mkspecs/win32-msvc2012 \
    ./GeneratedFiles \
    $(ProjectDir)/RFDevice/include \
    $(QWT_ROOT)/include
LIBS += -L"$(ProjectDir)/RFDevice" \
    -L"$(QWT_ROOT)/lib" \
    -llibEGLd \
    -llibGLESv2d \
    -lgdi32 \
    -luser32 \
    -lRFDevice \
    -lqwtd
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(RF_60x_QuadView_w.pri)
win32:RC_FILE = RF_60x_QuadView_w.rc

OTHER_FILES += \
    properties.js \
    main.qml

RESOURCES += \
    res.qrc
