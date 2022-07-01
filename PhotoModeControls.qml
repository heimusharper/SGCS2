import QtQuick 2.0
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import Finco 1.0

Item {

    id: root

    // down side
        Column {
            spacing: 10
            anchors.fill: parent
            RoundButton {
                id: undoButton
                width: root.width / 5
                height: width
                radius: width / 2
                text: qsTr("Take picture")
                //font.pixelSize: height * 0.8
                onClicked: {
                    UAV.getPayloadPhoto().takeShot()
                }
            }
        }
}
