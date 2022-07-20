import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtLocation 5.12
import QtPositioning 5.12
import QtQuick.Controls.Material 2.12
import Finco 1.0
import QtGraphicalEffects 1.13


ApplicationWindow {
    id: window
    width: 1024
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
            mapView.setMapType(mapConfigureView.mapProvider, mapConfigureView.mapType)
        }
    }

    StreamConfigureView {
        id: streamConfigureView
        onVideoStreamAddressChanged: {
            videoObject.run(streamConfigureView.videoStreamAddress)
        }
    }

    MissionEditDrawer {
        id: missionEditView
        onConfigureAt: {
            switch (item_type) {
                case Mission.SIMPLE_POINT:
                    missionISimplePointtemEditView.updateContent(index,
                                                                 param5, param6, param7,
                                                                 param1, frame)
                    missionEditDrawer.push(missionISimplePointtemEditView)
                    break;
            }
        }
        onAddOperationOn: {
            missionIOperationSelectEditView.itemIndex = index
            missionEditDrawer.push(missionIOperationSelectEditView)
        }
    }
    MissionSimplePointItemEdit {
        id: missionISimplePointtemEditView
        onCloseMe: {
            missionEditDrawer.pop()
        }
    }

    MissionSelectOperationItemEdit {
        id: missionIOperationSelectEditView
        onCloseMe: {
            missionEditDrawer.pop()
        }
    }

    MissionLoadDrawer {
        id: missionLoadView
    }

    property bool missionIsMain: true

    Item {
        id: mainComponent
        function checkParents(sw) {
            viewsSwitchArea.checkParents(sw)
        }

        Rectangle {
            anchors.fill: parent
            color: "white"
        }

        Item {
            id: mapRectangle;
            anchors.fill: parent
            RowLayout {
                anchors.fill: parent
                MapView {
                    id: mapView
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    addPointOnMapClick: missionModeControls.addPointModeEnabled;
                    // anchors.fill: parent
                    onMapFocused: {
                        flightModeControls.showAdditionalActions = false
                        missionModeControls.showAdditionalActions = false;
                    }

                    MissionModeControls {
                        id: missionModeControls
                        anchors.fill: parent
                        visible: missionMode && missionIsMain
                        //onAddPointModeEnabledChanged: {
                        //    mapRectangle.addPointOnMapClick = addPointModeEnabled
                        // }
                    }
                    FlightModeControls {
                        id: flightModeControls
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        visible: !missionMode && missionIsMain
                    }
                    MapControls {
                        anchors.right: parent.right
                        anchors.top: parent.top
                        visible: missionIsMain
                        onTrackUAV: {
                            mapView.trackUAV = !mapView.trackUAV
                        }
                        onZoomIn: {
                            mapView.zoomIn()
                        }
                        onZoomOut: {
                            mapView.zoomOut()
                        }
                    }

                }

                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    visible: missionMode
                    ColumnLayout {
                        anchors.fill: parent
                        RowLayout {

                            Button {
                                id: selectMissionModePoints
                                text: qsTr("Points")
                                checkable: true
                                checked: true

                                onCheckedChanged: {
                                    if (selectMissionModePoints.checked) {
                                        while (missionEditDrawer.depth > 1) {
                                            missionEditDrawer.pop()
                                        }
                                        selectMissionModeExtended.checked = false
                                        selectMissionModeLoad.checked = false
                                    }
                                }
                                background: Rectangle {
                                            border.width: 2
                                            color: selectMissionModePoints.checked ?
                                                       Material.color(Material.LightGreen) :
                                                       Material.color(Material.Grey)
                                            radius: 4
                                        }
                            }
                            Button {
                                id: selectMissionModeExtended
                                text: qsTr("Extended")
                                checkable: true

                                onCheckedChanged: {
                                    if (selectMissionModeExtended.checked) {
                                        //while (missionEditDrawer.depth > 1) {
                                        //    missionEditDrawer.pop()
                                        //}
                                        selectMissionModePoints.checked = false
                                        selectMissionModeLoad.checked = false
                                    }
                                }

                                background: Rectangle {
                                            border.width: 2
                                            color: selectMissionModeExtended.checked ?
                                                       Material.color(Material.LightGreen) :
                                                       Material.color(Material.Grey)
                                            radius: 4
                                        }
                            }
                            Button {
                                id: selectMissionModeLoad
                                text: qsTr("Load")
                                checkable: true

                                onClicked: {
                                    if (selectMissionModeLoad.checked) {
                                        while (missionEditDrawer.depth > 1) {
                                            missionEditDrawer.pop()
                                        }
                                        missionEditDrawer.push(missionLoadView)
                                        selectMissionModePoints.checked = false
                                        selectMissionModeExtended.checked = false
                                    }
                                }
                                background: Rectangle {
                                            border.width: 2
                                            color: selectMissionModeLoad.checked ?
                                                       Material.color(Material.LightGreen) :
                                                       Material.color(Material.Grey)
                                            radius: 4
                                        }
                            }
                        }
                        StackView {
                            id: missionEditDrawer
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            initialItem: missionEditView
                        }
                        RowLayout {
                            Text {
                                text: qsTr("Altitude:")
                            }
                            SpinBox {
                                id: altitudeSet
                                to: 16000
                                from: -500
                                editable: true
                                value: UAV.getMission().defaultAltitude
                                onValueModified: {
                                    UAV.getMission().defaultAltitude = value
                                }
                            }
                            Text {
                                text: qsTr("Frame:")
                            }
                            ComboBox {
                                model: [qsTr("Relative"), qsTr("Relief"), qsTr("Absolute")]
                                currentIndex: UAV.getMission().defaultFrame
                                onCurrentIndexChanged: {
                                    UAV.getMission().defaultFrame = currentIndex
                                }
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            z: mainComponent.z + 2
            id: viewsSwitchArea
            visible: !missionMode
            layer.enabled: true
            layer.effect: OpacityMask {
                maskSource: Item {
                    width: viewsSwitchArea.width
                    height: viewsSwitchArea.height
                    Rectangle {
                        anchors.centerIn: parent
                        width: viewsSwitchArea.width
                        height: viewsSwitchArea.height
                        radius: 10
                    }
                }
            }

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
                        missionIsMain = true
                    } else {
                        // map to video
                        mapRectangle.parent = viewsSwitchArea
                        videoObject.parent = mainComponent
                        missionIsMain = false
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
            missionEditDrawer.visible = true
        }
        onActivateFlightMode: {
            missionMode = false
            mainComponent.checkParents(false)
            missionEditDrawer.visible = false
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
}
