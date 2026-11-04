QT += core gui qml quick

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += qml.qrc

SOURCES += \
        backend/gui/buffer-config-controller.cpp \
        backend/gui/full-system-controller.cpp \
        backend/gui/pd-config-controller.cpp \
        backend/gui/system-auto-controller.cpp \
        backend/gui/system-step-controller.cpp \
        backend/system/buffer.cpp \
        backend/system/calendar.cpp \
        backend/system/calendarentry.cpp \
        backend/system/device.cpp \
        backend/system/distribution.cpp \
        backend/system/msstime.cpp \
        backend/system/producer.cpp \
        backend/system/system.cpp \
        backend/system/types.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    main.qml

HEADERS += \
    backend/gui/buffer-config-controller.h \
    backend/gui/full-system-controller.h \
    backend/gui/pd-config-controller.h \
    backend/gui/system-auto-controller.h \
    backend/gui/system-step-controller.h \
    backend/system/buffer.h \
    backend/system/calendar.h \
    backend/system/calendarentry.h \
    backend/system/device.h \
    backend/system/distribution.h \
    backend/system/msstime.h \
    backend/system/producer.h \
    backend/system/system.h \
    backend/system/types.h
