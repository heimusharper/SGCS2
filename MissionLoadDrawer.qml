import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtLocation 5.12
import QtPositioning 5.12
import QtQuick.Controls.Material 2.12
import Finco 1.0


Item {
    property bool hasWriteError: UAV.getMission().writeErrorState
    property bool hasReadError: UAV.getMission().readErrorState
    onHasReadErrorChanged: {
        errorRect.visible = hasWriteError || hasReadError
    }
    onHasWriteErrorChanged: {
        errorRect.visible = hasWriteError || hasReadError
    }

    ColumnLayout {
        anchors.fill: parent
        GridLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            columns: 2
            Button {
                id: buttonUploadMission
                Layout.fillWidth: true
                text: qsTr("Upload")
                onClicked: {
                    UAV.getMission().writeAll()
                }
                background: Rectangle {
                            border.width: 2
                            border.color: hasWriteError ?
                                              Material.color(Material.Red) :
                                              Material.color(Material.LightGreen)
                            radius: 4
                        }
            }
            Button {
                Layout.fillWidth: true
                text: qsTr("Download")
                onClicked: {
                    UAV.getMission().readAll()
                }
                background: Rectangle {
                            border.width: 2
                            border.color: hasReadError ?
                                            Material.color(Material.Red) :
                                            Material.color(Material.LightGreen)
                            radius: 4
                        }
            }
            Button {
                Layout.fillWidth: true
                text: qsTr("Open file")
                onClicked: {
                    // UAV.getMission().writeAll()
                }
                background: Rectangle {
                            border.width: 2
                            radius: 4
                        }
            }
            Button {
                Layout.fillWidth: true
                text: qsTr("Save to file")
                onClicked: {
                    // UAV.getMission().readAll()
                }
                background: Rectangle {
                            border.width: 2
                            radius: 4
                        }
            }
            Item {
                Layout.fillHeight: true
            }
        }
        Rectangle {
            id: errorRect
            visible: hasWriteError || hasReadError
            Layout.fillWidth: true
            color: "red"
            height: errorText.height
            Text {
                id: errorText
                text: UAV.getMission().lastError
            }
        }
    }
}
