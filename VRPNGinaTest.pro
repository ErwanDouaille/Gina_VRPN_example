TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

#################################################################################### SOURCES
SOURCES += main.cpp \
    VRPNGenerator.cpp \
    VRPNObserver.cpp

################################################################################### GINA LIB
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/release/ -lGina0.2_64
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/debug/ -lGina0.2_64
else:unix: LIBS += -L$$PWD/lib/ -lGina0.2_64
win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/release/libGina0.2_64.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/debug/libGina0.2_64.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/release/Gina0.2_64.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/debug/Gina0.2_64.lib
else:unix: PRE_TARGETDEPS += $$PWD/lib/libGina0.2_64.a

################################################################################ PTHREAD LIB
unix|win32: LIBS += -lpthread-2.22

################################################################################### LUSB LIB
unix|win32: LIBS += -lusb-1.0

################################################################################### VRPN LIB
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/release/ -lvrpnserver
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/debug/ -lvrpnserver
else:unix: LIBS += -L$$PWD/lib/ -lvrpnserver
win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/release/libvrpnserver.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/debug/libvrpnserver.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/release/vrpnserver.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/debug/vrpnserver.lib
else:unix: PRE_TARGETDEPS += $$PWD/lib/libvrpnserver.a

################################################################################### QUAT LIB
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/release/ -lquat
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/debug/ -lquat
else:unix: LIBS += -L$$PWD/lib/ -lquat
win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/release/libquat.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/debug/libquat.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/release/quat.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/debug/quat.lib
else:unix: PRE_TARGETDEPS += $$PWD/lib/libquat.a

#################################################################################### HEADERS
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
HEADERS += \
    Leap.h \
    LeapMath.h \
    LgData.h \
    LgDataTemplate.h \
    LgEnvironment.h \
    LgFunctions.h \
    LgGenerator.h \
    LgGroupTemplate.h \
    LgHistoricTemplate.h \
    LgMetaData.h \
    LgNode.h \
    LgNodeFactory.h \
    LgObserver.h \
    LgPoint2D.h \
    LgPoint3D.h \
    LgProcessor.h \
    LgSwitch.h \
    LgTimer.h \
    VRPNGenerator.h \
    VRPNObserver.h
