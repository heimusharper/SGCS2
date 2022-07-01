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
    signal activateBurger()

    Popup {
        id: outerPopup
        x: parent.width - width
        y: parent.height
        padding: 10
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        ColumnLayout {
            anchors.fill: parent

            RadioButton {
                text: qsTr("UDP")
                checked: Configuration.connectionMethod === "udp"
                onClicked: {
                    connectionStack.currentIndex = 0
                }
            }
            RadioButton {
                text: qsTr("Serial")
                checked: Configuration.connectionMethod === "serial"
                onClicked: {
                    connectionStack.currentIndex = 1
                }
            }
            Component.onCompleted: {
                if (Configuration.connectionMethod === "udp")
                    connectionStack.currentIndex = 0
                else if (Configuration.connectionMethod === "serial")
                    connectionStack.currentIndex = 1
                else
                    connectionStack.currentIndex = 2
            }

            StackLayout {
                id: connectionStack
                Item {
                    implicitWidth: gridOfUDP.width
                    implicitHeight: gridOfUDP.height
                    id: udpView
                    GridLayout {
                        id: gridOfUDP
                        // horizontalItemAlignment: Qt.AlignHCenter
                        // verticalItemAlignment: Qt.AlignVCenter
                        columns: 2
                        // spacing: 5

                        Text {
                            text: "UDP"
                        }
                        Button {
                            text: "Connect"
                            onClicked: {
                                outerPopup.close();
                                Configuration.connectionMethod = "udp"
                                Configuration.connectionUDPHost = udpHostField.text
                                Configuration.connectionUDPPort = udpPortField.value
                                UAV.connection().connectToUDP(udpHostField.text, udpPortField.value);
                            }
                        }
                        Text {
                            text: "Host"
                        }
                        TextField {
                            id: udpHostField
                            text: Configuration.connectionUDPHost
                        }

                        Text {
                            text: "Port"
                        }

                        SpinBox {
                            id: udpPortField
                            value: Configuration.connectionUDPPort
                            from: 1024
                            to: 64000
                        }
                    }
                }

                Item {
                    implicitWidth: gridOfSerial.width
                    implicitHeight: gridOfSerial.height
                    id: serialView
                    GridLayout {
                        id: gridOfSerial
                        // horizontalItemAlignment: Qt.AlignHCenter
                        // verticalItemAlignment: Qt.AlignVCenter
                        columns: 2
                        // spacing: 5

                        Text {
                            text: qsTr("Serial")
                        }
                        Button {
                            text: qsTr("Connect")
                            onClicked: {
                                outerPopup.close();
                                Configuration.connectionMethod = "serial"
                                Configuration.connectionSerialPort = serialPortField.text
                                UAV.connection().connectToUART(serialPortField.text);
                            }
                        }
                        Text {
                            text: qsTr("Port")
                        }
                        TextField {
                            id: serialPortField
                            text: Configuration.connectionSerialPort
                        }
                    }
                }
            }
        }
    }

    background: Rectangle {
        color: Material.color(Material.Cyan)
    }

    function getGPSText (n) {
        switch(n) {
        case Sensors.ERROR:
            return qsTr("ER")
        case Sensors.FIX2D:
            return qsTr("2D")
        case Sensors.FIX3D:
            return qsTr("3D")
        case Sensors.DGPS:
            return qsTr("DGPS")
        case Sensors.RTKFIX:
            return qsTr("RTK FIX")
        case Sensors.RTKFLOAT:
            return qsTr("RTK FLOAT")
        case Sensors.STATIC:
            return qsTr("STATIC")
        case Sensors.PPP:
            return qsTr("PPP")
        case Sensors.NA:
        default:
            return qsTr("NA")
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
                     activateBurger()
                 }
             }
             ToolButton {
                 id: gps
                 text:  getGPSText(UAV.getSensors().gpsStatus)
                 font.pixelSize: height / 2
                 icon.name: "satelites"
                 icon.color: getGPSColor(UAV.getSensors().gpsStatus)
             }
             ToolButton {
                 id: photos
                 text: qsTr("Photos: ") + UAV.getPayloadPhoto().fullCount
                 font.pixelSize: height / 2
             }
             Item {
                 Layout.fillWidth: true
             }
             ToolButton {
                 id: connectionButton
                 visible: !UAV.connection().connected
                 text: qsTr("Connect")
                 height: buttonsLayout.height
                 font.pixelSize: height / 2
                 onClicked: {
                     outerPopup.open() // connection popup
                 }
                 Rectangle {
                     anchors.fill: parent
                     anchors.margins: 0
                     color: Material.color(Material.LightRed)
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
                 width: parent.width * UAV.progress
                 color: Material.color(Material.LightGreen)

             }
         }
    }
}
