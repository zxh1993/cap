TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt



LIBS += \
    -lpcap

HEADERS += \
    cap/CPcap.h \
    packet/CEtherPacket.h \
    packet/CIPPacket.h \
    packet/CUDPPacket.h \
    packet/CTCPPacket.h

SOURCES += \
    cap/CPcap.cpp \
    packet/CEtherPacket.cpp \
    packet/CIPPacket.cpp \
    packet/CUDPPacket.cpp \
    main.cpp \
    packet/CTCPPacket.cpp

