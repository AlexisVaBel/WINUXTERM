QT+=gui
QT+=widgets
QT+=W_OS_LINUX

HEADERS += \
    view/consoleview.hpp \
    view/mainwindow.hpp \
    view/controlview.hpp \
    serial/serialdevlin.hpp \
    serial/serialdevbase.hpp \
    serial/SerialParams.hpp \
    cmn/DataProvider.hpp \
    cntrl/serialwritter.hpp \
    cntrl/serialworker.hpp \
    cntrl/serialreader.hpp

SOURCES += \
    main.cpp \
    view/consoleview.cpp \
    view/mainwindow.cpp \
    view/controlview.cpp \
    serial/serialdevlin.cpp \
    cntrl/serialwritter.cpp \
    cntrl/serialworker.cpp \
    cntrl/serialreader.cpp
