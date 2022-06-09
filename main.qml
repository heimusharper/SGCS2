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

    // predefined
    MapConfigureView {
        id: mapConfigureView
        onMapTypeChanged: {
            mapRectangle.setMapType(mapConfigureView.mapProvider, mapConfigureView.mapType)
        }
    }

    Item {
        id: mainComponent

        MapView {
            id: mapRectangle
            anchors.fill: parent
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

            VideoViewV4L2Item {
                id: videoObject
                // color: "green"
                anchors.fill: parent
            }

            Rectangle {
                z: viewsSwitchArea.z + 2
                anchors.fill: parent
                color: "transparent"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (mapRectangle.parent == mainComponent) {
                            mapRectangle.simpleMode = true
                            mapRectangle.parent = viewsSwitchArea
                            videoObject.parent = mainComponent
                        } else {
                            videoObject.parent = viewsSwitchArea
                            mapRectangle.simpleMode = false
                            mapRectangle.parent = mainComponent
                        }
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
    }


    Drawer {
        id: drawer
        width: window.width * 0.66
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
                    width: drawer.width / 3
                    icon.name: "map"
                    text: qsTr("Map settings");
                    onClicked: {
                        stackView.push(mapConfigureView)
                        drawer.close()
                    }
                }
                Button {
                    id: configureBtn
                    width: drawer.width / 3
                    icon.name: "configure"
                    text: qsTr("Configure");
                    onClicked: {
                        drawer.close()
                    }
                }
                Button {
                    id: helpBtn
                    width: drawer.width / 3
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
