QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        backend/system/buffer.cpp \
        backend/system/calendar.cpp \
        backend/system/calendarentry.cpp \
        backend/system/device.cpp \
        backend/system/msstime.cpp \
        backend/system/producer.cpp \
        backend/system/system.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md

HEADERS += \
    backend/system/buffer.h \
    backend/system/calendar.h \
    backend/system/calendarentry.h \
    backend/system/device.h \
    backend/system/msstime.h \
    backend/system/producer.h \
    backend/system/system.h
