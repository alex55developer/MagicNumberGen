QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

BOOSTDIR = E:\LIBS\boost_1_75_0
BOOST_LIB = $$BOOSTDIR\stage\lib\gcc_64bit

message(BOOSTDIR: $$BOOSTDIR)
message(BOOST_LIB: $$BOOST_LIB)

INCLUDEPATH += $$BOOSTDIR
message(INCLUDEPATH: $$INCLUDEPATH)

LIBS += \
	$$BOOST_LIB\libboost_regex-mgw6-mt-d-x64-1_75.a

SOURCES += \
        main.cpp \
		sequence.h

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
