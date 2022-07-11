import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtLocation 5.12
import QtPositioning 5.12
import QtQuick.Controls.Material 2.12
import Finco 1.0

Item {
    GridLayout {
        anchors.fill: parent
        columns: 2
        Button {
            Layout.fillWidth: true
            text: qsTr("Upload")
            onClicked: {
                UAV.getMission().writeAll()
            }
        }
        Button {
            Layout.fillWidth: true
            text: qsTr("Download")
            onClicked: {
                UAV.getMission().readAll()
            }
        }
        Button {
            Layout.fillWidth: true
            text: qsTr("Open file")
            onClicked: {
                // UAV.getMission().writeAll()
            }
        }
        Button {
            Layout.fillWidth: true
            text: qsTr("Save to file")
            onClicked: {
                // UAV.getMission().readAll()
            }
        }
        Item {
            Layout.fillHeight: true
        }
    }
}
