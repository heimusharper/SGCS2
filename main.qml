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
    // title: qsTr("Photobase SGCS")
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
            PhotoModeControls {
                id: photoModeControls
                anchors.fill: parent
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
        width: (window.width > window.height) ? window.width * 0.6 : window.width
        height: window.height

        ColumnLayout {
            // spacer
            GridLayout {
                property var onTime: UAV.getPayloadPhoto().onTime
                property var onDistance: UAV.getPayloadPhoto().onDistance
                onOnTimeChanged: {
                    onTimeCheck.checked = onTime > 0
                    onTimeBox.value = onTime
                    onTimeBg.color = "lightgreen"
                }
                onOnDistanceChanged: {
                    onDistanceCheck.checked = onDistance > 0
                    onDistanceBox.value = onDistance
                    onDistBg.color = "lightgreen"
                }

                // Layout.fillWidth: true
                // Layout.fillHeight: true
                columns: 2
                CheckBox {
                    id: onTimeCheck;
                    text: qsTr("On time")
                }
                SpinBox {
                    id: onTimeBox
                    onValueChanged: {
                        onTimeBg.color = "lightblue"
                    }

                    background: Rectangle {
                        id: onTimeBg
                        anchors.fill: parent
                        color: "red"
                    }
                }

                CheckBox {
                    id: onDistanceCheck
                    text: qsTr("On distance")
                }
                SpinBox {
                    id: onDistanceBox
                    onValueChanged: {
                        onDistBg.color = "lightblue"
                    }

                    background: Rectangle {
                        id: onDistBg
                        anchors.fill: parent
                        color: "red"
                    }
                }

                Button {
                    text: qsTr("Apply")
                    onClicked: {

                        UAV.getPayloadPhoto().commit((onTimeCheck.checked) ? onTimeBox.value : 0,
                                                     (onTimeCheck.checked) ? onDistanceBox.value : 0)
                    }
                }
                Text {

                }
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
                    width: drawer.width / 2
                    icon.name: "map"
                    text: qsTr("Map");
                    onClicked: {
                        stackView.push(mapConfigureView)
                        drawer.close()
                    }
                }
                Button {
                    id: helpBtn
                    width: drawer.width / 2
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
