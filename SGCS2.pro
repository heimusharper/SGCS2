QT += core network positioning quick multimedia quickcontrols2 serialport
TARGET = SGCS2  
TEMPLATE = app

QMAKE_CXXFLAGS += -Wall
CONFIG += c++17

INCLUDEPATH += thirdparty/c_library_v2

HEADERS += \
        uav/UAV.h \
        uav/Positioning.h \
        uav/Sensors.h \
        uav/Mission.h \
        uav/MissionItem.h \
        connection/Connection.h \
        connection/ConnectionType.h \
        connection/UDPConnection.h \
        connection/SerialConnection.h \
        streamer/HomePositionRequest.h \
        streamer/ARMRequest.h \
        streamer/DataStreamer.h \
        streamer/MainDataStream.h \
        streamer/PositionDataStream.h \
        streamer/SensorsDataStream.h \
        streamer/ManualControlRequest.h \
        streamer/MissionReadRequest.h \
        streamer/MissionWriteRequest.h \
        mavlink/ModeHelper.h \
        mavlink/MavlinkRequest.h \
        mavlink/MavlinkStream.h \
        mavlink/MavlinkStreamer.h \
        mavlink/MavlinkMainDataStream.h \
        mavlink/MavlinkPositionDataStream.h \
        mavlink/MavlinkHomePositionRequest.h \
        mavlink/MavlinkSensorsDataStream.h \
        mavlink/MavlinkARMRequest.h \
        mavlink/MavlinkPingRequest.h \
        mavlink/MavlinkManualControlRequest.h \
        mavlink/MavlinkMissionReadRequest.h \
        mavlink/MavlinkMissionWriteRequest.h \
        Configuration.h \
        VideoViewV4L2Item.h

SOURCES += \
        main.cpp \
        uav/UAV.cpp \
        uav/Positioning.cpp \
        uav/Sensors.cpp \
        uav/Mission.cpp \
        connection/Connection.cpp \
        connection/ConnectionType.cpp \
        connection/UDPConnection.cpp \
        connection/SerialConnection.cpp \
        streamer/DataStreamer.cpp \
        mavlink/MavlinkStreamer.cpp \
        mavlink/MavlinkMainDataStream.cpp \
        mavlink/MavlinkPositionDataStream.cpp \
        mavlink/MavlinkHomePositionRequest.cpp \
        mavlink/MavlinkSensorsDataStream.cpp \
        mavlink/MavlinkARMRequest.cpp \
        mavlink/MavlinkPingRequest.cpp \
        mavlink/MavlinkManualControlRequest.cpp \
        mavlink/MavlinkMissionReadRequest.cpp \
        mavlink/MavlinkMissionWriteRequest.cpp \
		Configuration.cpp \
		VideoViewV4L2Item.cpp


RESOURCES += \
        qml.qrc

TRANSLATIONS += \
		SGCS2_ru_RU.ts
