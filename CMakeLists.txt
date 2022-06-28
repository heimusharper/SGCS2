cmake_minimum_required(VERSION 3.10)

project(SGCS2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# mavlink
EXECUTE_PROCESS(COMMAND
    python mavlink/pymavlink/tools/mavgen.py --output c_library_v2 --lang C --wire-protocol 2.0 mavlink/message_definitions/v1.0/all.xml
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/thirdparty
    )

FIND_PATH(MAVLINK_INCLUDE_DIR
    NAMES
        protocol.h
    PATHS
    ${PROJECT_SOURCE_DIR}/thirdparty/c_library_v2)

IF (NOT MAVLINK_INCLUDE_DIR)
    message("Failed build mavlink")
ELSE()
    message("Mavlink in ${MAVLINK_INCLUDE_DIR}")
    INCLUDE_DIRECTORIES(${MAVLINK_INCLUDE_DIR})
ENDIF()



find_package(QT NAMES Qt5 REQUIRED COMPONENTS
    Core
    Quick
    LinguistTools
    Positioning
    Network
    Multimedia
    QuickControls2
)
find_package(Qt5 REQUIRED COMPONENTS
    Core
    Quick
    LinguistTools
    Positioning
    Network
    Multimedia
    QuickControls2
)

set(TS_FILES SGCS2_ru_RU.ts)

set(PROJECT_SOURCES
        main.cpp
        # uav
        uav/UAV.h
        uav/Positioning.h
        uav/Sensors.h
        uav/Mission.h

        uav/UAV.cpp
        uav/Positioning.cpp
        uav/Sensors.cpp
        uav/Mission.cpp


        connection/Connection.h
        connection/ConnectionType.h
        connection/UDPConnection.h

        connection/Connection.cpp
        connection/ConnectionType.cpp
        connection/UDPConnection.cpp



        # streamers

        streamer/HomePositionRequest.h
        streamer/ARMRequest.h

        streamer/DataStreamer.h
        streamer/MainDataStream.h
        streamer/PositionDataStream.h
        streamer/SensorsDataStream.h
        streamer/ManualControlRequest.h
        streamer/MissionReadRequest.h


        streamer/DataStreamer.cpp

        # mavlink
        mavlink/ModeHelper.h
        mavlink/MavlinkRequest.h
        mavlink/MavlinkStream.h

        mavlink/MavlinkStreamer.h
        mavlink/MavlinkMainDataStream.h
        mavlink/MavlinkPositionDataStream.h
        mavlink/MavlinkHomePositionRequest.h
        mavlink/MavlinkSensorsDataStream.h
        mavlink/MavlinkARMRequest.h
        mavlink/MavlinkPingRequest.h
        mavlink/MavlinkManualControlRequest.h
        mavlink/MavlinkMissionReadRequest.h

        mavlink/MavlinkStreamer.cpp
        mavlink/MavlinkMainDataStream.cpp
        mavlink/MavlinkPositionDataStream.cpp
        mavlink/MavlinkHomePositionRequest.cpp
        mavlink/MavlinkSensorsDataStream.cpp
        mavlink/MavlinkARMRequest.cpp
        mavlink/MavlinkPingRequest.cpp
        mavlink/MavlinkManualControlRequest.cpp
        mavlink/MavlinkMissionReadRequest.cpp


        #qml
        Configuration.h Configuration.cpp
        VideoViewV4L2Item.h VideoViewV4L2Item.cpp

        qml.qrc
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SGCS2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SGCS2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(SGCS2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SGCS2
          ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES
        #${CMAKE_SOURCE_DIR}
        ${PROJECT_SOURCES}
        ${TS_FILES})
endif()

target_compile_definitions(SGCS2
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(SGCS2
  PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Positioning
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::QuickControls2
)

set_target_properties(SGCS2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(SGCS2)
    qt_finalize_executable(SGCS2)
endif()
