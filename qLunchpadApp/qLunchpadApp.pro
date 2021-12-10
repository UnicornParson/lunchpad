QT += serialport widgets
CONFIG += c++17 console

DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS_WARN_ON -= -Wreorder -Wformat= -WsignConversion
RC_ICONS += app.ico

CONFIG(debug, debug|release) {
  DESTDIR = bin/debug
  OBJECTS_DIR = bin/debug/.obj
  MOC_DIR = bin/debug/.moc
  RCC_DIR = bin/debug/.rcc
  UI_DIR = bin/debug/.ui
}

CONFIG(release, debug|release) {
  # enable optimisation
  QMAKE_CXXFLAGS_RELEASE += -O4
  QMAKE_CXXFLAGS_RELEASE -= -O2
  QMAKE_CXXFLAGS_RELEASE -= -O3
  QMAKE_CXXFLAGS_RELEASE -= -Os
  QMAKE_CXXFLAGS += -O4
  QMAKE_CXXFLAGS -= -O2
  QMAKE_CXXFLAGS -= -O3
  QMAKE_CXXFLAGS -= -Os

  DESTDIR = bin/release
  OBJECTS_DIR = bin/release/.obj
  MOC_DIR = bin/release/.moc
  RCC_DIR = bin/release/.rcc
  UI_DIR = bin/release/.ui
}
QMAKE_CXXFLAGS += -floop-parallelize-all -ftree-parallelize-loops=4

SOURCES += \
        comreader.cpp \
        executor.cpp \
        keyinjector.cpp \
        main.cpp \
        winconstants.cpp

HEADERS += \
    comreader.h \
    constants.h \
    executor.h \
    keyinjector.h \
    winconstants.h

RESOURCES += \
    rc.qrc

LIBS += -lKernel32
