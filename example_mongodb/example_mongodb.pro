QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/../../../mongo-cxx-driver/lib/ -lbsoncxx.dll

INCLUDEPATH += $$PWD/../../../mongo-cxx-driver/include
DEPENDPATH += $$PWD/../../../mongo-cxx-driver/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../mongo-cxx-driver/lib/bsoncxx.dll.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../../mongo-cxx-driver/lib/libbsoncxx.dll.a

win32: LIBS += -L$$PWD/../../../mongo-cxx-driver/lib/ -lmongocxx.dll

INCLUDEPATH += $$PWD/../../../mongo-cxx-driver/include
DEPENDPATH += $$PWD/../../../mongo-cxx-driver/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../mongo-cxx-driver/lib/mongocxx.dll.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../../mongo-cxx-driver/lib/libmongocxx.dll.a
