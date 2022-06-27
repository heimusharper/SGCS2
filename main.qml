import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtLocation 5.12
import QtPositioning 5.12
import QtQuick.Controls.Material 2.12
import Finco 1.0


ApplicationWindow {
    id: window
    width: 640
    height: width * (9 / 16)
    visible: true
    title: qsTr("SGCS")
    property bool missionMode : false

    Material.theme: Material.System
    Material.accent: Material.LightBlue

    // predefined
    MapConfigureView {
        id: mapConfigureView
        onMapTypeChanged: {
            mapRectangle.setMapType(mapConfigureView.mapProvider, mapConfigureView.mapType)
        }
    }

    StreamConfigureView {
        id: streamConfigureView
        onVideoStreamAddressChanged: {
            videoObject.run(streamConfigureView.videoStreamAddress)
        }
    }

    Item {
        id: mainComponent
        function checkParents(sw) {
            viewsSwitchArea.checkParents(sw)
        }

        Rectangle {
            anchors.fill: parent
            color: "white"
        }

        MapView {
            id: mapRectangle
            anchors.fill: parent
            onMapFocused: {
                missionModeControls.showAdditionalActions = false
                flightModeControls.showAdditionalActions = false
            }
        }

        Item {
            z: mainComponent.z + 2
            id: viewsSwitchArea

            anchors.top: mainComponent.top
            anchors.topMargin: 10
            anchors.left: mainComponent.left
            anchors.leftMargin: 10

            width: mainComponent.width / 4
            height: (mainComponent.width / 4) * (9/16)

            function checkParents(sw) {
                if (sw) {
                    if (mapRectangle.parent != mainComponent) {
                        //video to video
                        videoObject.parent = viewsSwitchArea
                        mapRectangle.parent = mainComponent
                    } else {
                        // map to video
                        mapRectangle.parent = viewsSwitchArea
                        videoObject.parent = mainComponent
                    }
                } else {
                    if (missionMode && mapRectangle.parent != mainComponent)
                        checkParents(true)
                }

            }

            VideoViewV4L2Item {
                id: videoObject
                // color: "green"
                anchors.fill: parent
                visible: !missionMode
                Component.onCompleted: {
                    if (Configuration.streamAutoConnect)
                    {
                        videoObject.run(Configuration.streamLast)
                    }
                }
            }

            Rectangle {
                z: viewsSwitchArea.z + 2
                anchors.fill: parent
                color: "transparent"
                visible: !missionMode
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        viewsSwitchArea.checkParents(true)
                    }
                }
            }
        }
    }

    // main

    header: MainToolBar {
        onActivateBurger: {
            if (stackView.depth > 1)
                stackView.pop()
            else
                drawer.open()
        }
        onActivateMissionMode: {
            missionMode = true;
            mainComponent.checkParents(false)
        }
        onActivateFlightMode: {
            missionMode = false
            mainComponent.checkParents(false)
        }
    }


    Drawer {
        id: drawer
        width: window.width * 0.80
        height: window.height


        Column {
            anchors.fill: parent
            // spacer
            Item {// spacer item
                Layout.fillWidth: true
                Layout.fillHeight: true
                Rectangle { anchors.fill: parent; color: "#ffaaaa" } // to visualize the spacer
            }

        }
        Item {
            anchors.bottom: parent.bottom
            width:  parent.width
            height: mapBtn.height
            Row {
                anchors.fill: parent
                Button {
                    id: mapBtn
                    width: drawer.width / 4
                    icon.name: "map"
                    text: qsTr("Map");
                    onClicked: {
                        stackView.push(mapConfigureView)
                        drawer.close()
                    }
                }
                Button {
                    id: streamBtn
                    width: drawer.width / 4
                    icon.name: "stream"
                    text: qsTr("Stream");
                    onClicked: {
                        stackView.push(streamConfigureView)
                        drawer.close()
                    }
                }
                Button {
                    id: configureBtn
                    width: drawer.width / 4
                    icon.name: "configure"
                    text: qsTr("Configure");
                    onClicked: {
                        drawer.close()
                    }
                }
                Button {
                    id: helpBtn
                    width: drawer.width / 4
                    icon.name: "help"
                    text: qsTr("Help");
                    onClicked: {
                        drawer.close()
                    }
                }
            }
        }
    }

    StackView {
        id: stackView
        x: -141
        y: 96
        width: 200
        height: 200
        anchors.fill: parent
        initialItem: mainComponent
    }
    MissionModeControls {
        id: missionModeControls
        anchors.fill: parent
        visible: missionMode
        onPointModeSet: {
            mapRectangle.addPointOnMapClick = missionModeControls.addPointModeEnabled;
        }
    }
    FlightModeControls {
        id: flightModeControls
        anchors.fill: parent
        visible: !missionMode
    }

}
