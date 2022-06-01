import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtLocation 5.12
import QtPositioning 5.12
import Finco 1.0

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    header: MainToolBar {

    }


    Drawer {

    }

    StackView {
        id: stackView
        x: -141
        y: 96
        width: 200
        height: 200
        anchors.fill: parent
        initialItem: mainComponent

        Item {
            id: mainComponent

            Item {
                id: mapRectangle
                anchors.fill: parent

                Rectangle {
                    id: mapObject
                    color: "yellow"
                    anchors.fill: parent
                }
            }

            Item {
                id: viewsSwitchArea
                width: 100
                height: 50
                Rectangle {
                    anchors.fill: parent
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if (mapObject.parent == mapRectangle)
                                mapObject.parent = viewsSwitchArea
                            else
                                mapObject.parent = mapRectangle
                            if (videoObject.parent == mapRectangle)
                                videoObject.parent = viewsSwitchArea
                            else
                                videoObject.parent = mapRectangle
                        }
                    }
                    color: "red"
                }

                VideoViewV4L2Item {
                    id: videoObject
                    //color: "green"
                    anchors.fill: parent
                }
            }
        }
    }
}
