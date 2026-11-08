QT += core gui qml quick widgets printsupport

CONFIG += c++17 cmdline

INCLUDEPATH += backend/system
INCLUDEPATH += libs/qcustomplot
QML_IMPORT_PATH += $$PWD/qml

RESOURCES += qml.qrc

SOURCES += \
    backend/gui/custom-plot-item.cpp \
    libs/qcustomplot/qcustomplot.cpp \
    backend/gui/auto-graphs-table-model.cpp \
    backend/gui/buffer-config-controller.cpp \
    backend/gui/buffer-table-model.cpp \
    backend/gui/calendar-table-model.cpp \
    backend/gui/pd-config-controller.cpp \
    backend/gui/system-auto-controller.cpp \
    backend/gui/system-controller.cpp \
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
    main.qml \
    qml/components/qmldir \
    qml/pages/qmldir \
    qml/styles/qmldir

HEADERS += \
    backend/gui/custom-plot-item.h \
    libs/qcustomplot/qcustomplot.h \
    backend/gui/auto-graphs-table-model.h \
    backend/gui/buffer-config-controller.h \
    backend/gui/buffer-table-model.h \
    backend/gui/calendar-table-model.h \
    backend/gui/pd-config-controller.h \
    backend/gui/system-auto-controller.h \
    backend/gui/system-controller.h \
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
