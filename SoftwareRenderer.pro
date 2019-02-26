# target_name =
# QT +=
# SOURCES +=
# HEADERS +=
# RESOUCES +=

TARGET = $$qtLibraryTarget(SoftwareRenderer)

QT += gui

TEMPLATE = app

CONFIG += c++14 qt

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# CX_MAKESPEC = $${split(QMAKESPEC,'/')}
# DESTDIR = $${PWD}/../dist/$${last(CX_MAKESPEC)}-bin

# Default rules for deployment.
# qnx: target.path = /tmp/$${TARGET}/bin
# else: unix:!android: target.path = /opt/$${TARGET}/bin
# !isEmpty(target.path): INSTALLS += target

# Additional import path used to resolve QML modules in Qt Creator's code model
# QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
# QML_DESIGNER_IMPORT_PATH =

# customize configure
# include($$PWD/thirdparty/thirdparty.pri)

# for(lib,LIB_LIST){
#     win32{
#         LIBS += $$PWD/dist/bin/$${lib}.dll
#     } unix{
#
#     }
# }

# equals(TEMPLATE,lib) {
#     win32{
#         src_path  = $$system_path($$HEADER_SOURCE_PATH\*.h)
#         dest_path = $$system_path($$PWD/dist/include)
#         system("xcopy $$src_path $$dest_path\\$$TARGET /i /s /d /y ")
#     }
#     unix {
#         target.path = /usr/lib
#         INSTALLS += target
#     }
# }

SOURCES += \
    main.cpp \
    window/rasterwindow.cpp \
    window/baserasterwindow.cpp \
    rasterizer/rasterizeengine.cpp

HEADERS += \
    window/rasterwindow.h \
    window/baserasterwindow.h \
    rasterizer/rasterizeengine.h
