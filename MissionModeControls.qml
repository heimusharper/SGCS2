import QtQuick 2.0
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.15
import Finco 1.0
import QtQuick.Layouts 1.15

Item {

    id: root
    property bool showAdditionalActions: false
    property bool addPointModeEnabled: true
    property int buttonsSize: 30

    signal pointModeSet()

    width: mcl.childrenRect.width
    height: mcl.childrenRect.height

    Component.onCompleted: {
        pointModeSet()
    }
    onAddPointModeEnabledChanged: {
        pointModeSet()
    }
    onVisibleChanged: {
        if (!visible) {
            addPointModeEnabled = false;
        } else {
            addPointModeEnabled = true;
        }
    }

    // down side

    Item {
        id: infoLine
        height: root.height / 20
        width: ex.childrenRect.width
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            anchors.fill: parent
            color: Material.color(Material.Grey)
        }

        Row {
            id: ex

            anchors.fill: parent

            Text {
                text: qsTr("Points:")
                font.pixelSize: infoLine.height
            }

        }
    }


    Item {
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        width: mcl.childrenRect.width
        height: mcl.childrenRect.height

        RowLayout {
            id: mcl
            ColumnLayout {

                RoundButton {
                    id: uploadButton
                    //width: buttonsSize
                    height: buttonsSize
                    radius: 10
                    visible: showAdditionalActions
                    text: qsTr("Upload")
                    onClicked: {
                        UAV.getMission().writeAll()
                    }
                }
                RoundButton {
                    id: downloadButton
                    //width: buttonsSize
                    height: buttonsSize
                    radius: 10
                    visible: showAdditionalActions
                    text: qsTr("Download")
                    onClicked: {
                        UAV.getMission().readAll()
                    }
                }
                RoundButton {
                    id: clearButton
                    //width: buttonsSize
                    height: buttonsSize
                    radius: 10
                    visible: showAdditionalActions
                    text: qsTr("Clear")
                    onClicked: {
                        UAV.getMission().clear()
                    }
                }
            }
            RoundButton {
                id: showButton
                width: buttonsSize
                height: buttonsSize
                radius: 10
                checkable: true
                Layout.alignment: Qt.AlignBottom
                text: "..."
                onCheckedChanged: {
                    showAdditionalActions = !showAdditionalActions
                }
            }
        }
    }
}
