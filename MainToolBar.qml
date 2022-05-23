import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.10
import QtQuick.Controls.Material 2.10

import Finco 1.0



ToolBar {
    id: toolBarRoot
    // signals
    signal activateFlightMode()
    signal activateMissionMode()

    Popup {
        id: outerPopup
        x: parent.width - width
        y: parent.height
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        contentItem: Rectangle {
            Grid {
                horizontalItemAlignment: Qt.AlignHCenter
                verticalItemAlignment: Qt.AlignVCenter
                columns: 2
                spacing: 5

                Text {
                    text: "UDP"
                }
                Button {
                    text: "Connect"
                    onClicked: {
                        outerPopup.close();
                        UAV.connection().connectToUDP(udpHostField.text, udpPortField.value);
                    }
                }
                Text {
                    text: "Host"
                }
                TextField {
                    id: udpHostField
                    text: "192.168.88.183"
                }

                Text {
                    text: "Port"
                }

                SpinBox {
                    id: udpPortField
                    value: 14550
                    from: 1024
                    to: 64000
                }
            }
        }
    }

    background: Rectangle {
        color: Material.color(Material.Cyan)
        Rectangle {
            width:
                (connectionButton.visible ? connectionButton.width : 0)
                + (flightMode.visible ? flightMode.width : 0)
                + (missionMode.visible ? missionMode.width +  buttonsLayout.spacing: 0)
            height: parent.height
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            color: UAV.connection().connected
                   ? Material.color(Material.LightGreen)
                   : Material.color(Material.LightRed)
        }
    }

    function getGPSText (n) {
        switch(n) {
        case Sensors.ERROR:
            return "ER"
        case Sensors.FIX2D:
            return "2D"
        case Sensors.FIX3D:
            return "3D"
        case Sensors.DGPS:
            return "DGPS"
        case Sensors.RTKFIX:
            return "RTK FIX"
        case Sensors.RTKFLOAT:
            return "RTK FLOAT"
        case Sensors.STATIC:
            return "STATIC"
        case Sensors.PPP:
            return "PPP"
        case Sensors.NA:
        default:
            return "NA"
        }
    }
    function getGPSColor (n) {
        switch(n) {
        case Sensors.ERROR:
            return Material.color(Material.Red)
        case Sensors.FIX2D:
            return Material.color(Material.Amber)
        case Sensors.FIX3D:
        case Sensors.DGPS:
        case Sensors.RTKFIX:
        case Sensors.RTKFLOAT:
            return Material.color(Material.Green)
        case Sensors.STATIC:
        case Sensors.PPP:
            return Material.color(Material.Blue)
        case Sensors.NA:
        default:
            return Material.color(Material.Grey)
        }
    }

    ColumnLayout {
        spacing: 0
        anchors.fill: parent
         RowLayout {
             id: buttonsLayout

             ToolButton {
                 id: toolButton
                 text: stackView.depth > 1 ? "\u25C0" : "\u2630"
                 font.pixelSize: height / 2
                 onClicked: {
                 }
             }
             ToolButton {
                 id: gps
                 text:  getGPSText(UAV.getSensors().gpsStatus)
                 font.pixelSize: height / 2
                 icon.name: "satelites"
                 icon.color: getGPSColor(UAV.getSensors().gpsStatus)
             }
             Item {
                 Layout.fillWidth: true
             }
             ToolButton {
                 id: connectionButton
                 visible: ! UAV.connection().connected
                 text: "Connect"
                 font.pixelSize: height / 2
                 onClicked: {
                     outerPopup.open() // connection popup
                 }
             }
             ToolButton {
                 id: flightMode
                 text: "FM"
                 visible: UAV.connection().connected
                 font.pixelSize: height / 2
                 onClicked: {
                    toolBarRoot.activateFlightMode()
                 }
             }
             ToolButton {
                 id: missionMode
                 text: "MM"
                 visible: UAV.connection().connected
                 font.pixelSize: height / 2
                 onClicked: {
                     toolBarRoot.activateMissionMode()
                 }
             }
         }
         Rectangle {
             Layout.fillWidth: true
             height: 4
             color: Material.color(Material.Cyan)

             Rectangle {
                 id: statusLine
                 height: parent.height
                 width: parent.width * 0.3
                 color: Material.color(Material.LightGreen)

             }
         }
    }
}