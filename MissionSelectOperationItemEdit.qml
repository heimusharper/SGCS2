import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtLocation 5.12
import QtPositioning 5.12
import QtQuick.Controls.Material 2.12
import Finco 1.0

Item {

    Item {
        id: editRTL
    }
    Item {
        id: editLand
        ColumnLayout {
            RowLayout {
                Text {
                    text: qsTr("Lat")
                }
                TextField {
                    id: landLatitudeField

                    text: "0"
                    validator: DoubleValidator {
                        bottom: -90
                        top: 90
                        decimals: 6
                    }
                }
            }
            RowLayout {
                Text {
                    text: qsTr("Lon")
                }
                TextField {
                    id: landLongitudeField

                    text: "0"
                    validator: DoubleValidator {
                        bottom: -360
                        top: 360
                        decimals: 6
                    }
                }
            }
        }
    }
    Item {
        id: editJump
        RowLayout {
            Text {
                text: qsTr("To")
            }
            SpinBox {
            }
        }
    }
    Item {
        id: editDelay
        RowLayout {
            Text {
                text: qsTr("Time")
            }
            SpinBox {
            }
        }
    }
    Item {
        id: editDistance
        RowLayout {
            Text {
                text: qsTr("Distance")
            }
            SpinBox {
            }
        }
    }
    Item {
        id: editSpeed
        RowLayout {
            Text {
                text: qsTr("Speed")
            }
            SpinBox {
            }
        }
    }
    Item {
        id: editServo
        ColumnLayout {
        RowLayout {
            Text {
                text: qsTr("Servo")
            }
            SpinBox {
            }
        }
        RowLayout {
            Text {
                text: qsTr("PWM")
            }
            SpinBox {
            }
        }
        }
    }
    Item {
        id: editROI
        ColumnLayout {
        RowLayout {
            Text {
                text: qsTr("Lat")
            }
            SpinBox {
            }
        }
        RowLayout {
            Text {
                text: qsTr("Lon")
            }
            SpinBox {
            }
        }
        RowLayout {
            Text {
                text: qsTr("Alt")
            }
            SpinBox {
            }
        }
        }
    }
    Item {
        id: editGimbal
        ColumnLayout {
        RowLayout {
            Text {
                text: qsTr("Roll")
            }
            SpinBox {
            }
        }
        RowLayout {
            Text {
                text: qsTr("Pitch")
            }
            SpinBox {
            }
        }
        RowLayout {
            Text {
                text: qsTr("Yaw")
            }
            SpinBox {
            }
        }
        }
    }
    Item {
        id: editCamera
    }
    Item {
        id: editTrigger
    }
    Item {
        id: editParachute
    }

    property int itemIndex: -1
    signal closeMe()

    Rectangle {
        anchors.fill: parent
        color: "white"
    }

    ColumnLayout {
        anchors.fill: parent

        ComboBox {
            id: selectMode
            // Layout.fillHeight: true
            Layout.fillWidth: true
            model: [qsTr("RTL"), qsTr("Land"), qsTr("Jump"),
                qsTr("Delay"), qsTr("Distance"), qsTr("Speed"),
                qsTr("Servo"), qsTr("ROI"), qsTr("Camera"),
                qsTr("Gimbal"), qsTr("Trigger"), qsTr("Parachute")]
            onCurrentIndexChanged: {
                operationEdit.pop()
                switch (currentIndex) {
                case 0:
                    //operationEdit.push(editRTL)
                    break;
                case 1:
                    operationEdit.push(editLand)
                    break;
                case 2:
                    operationEdit.push(editJump)
                    break;
                case 3:
                    operationEdit.push(editDelay)
                    break;
                case 4:
                    operationEdit.push(editDistance)
                    break;
                case 5:
                    operationEdit.push(editSpeed)
                    break;
                case 6:
                    operationEdit.push(editServo)
                    break;
                case 7:
                    operationEdit.push(editROI)
                    break;
                case 8:
                    operationEdit.push(editCamera)
                    break;
                case 9:
                    operationEdit.push(editGimbal)
                    break;
                case 10:
                    operationEdit.push(editTrigger)
                    break;
                case 11:
                    operationEdit.push(editParachute)
                    break;
                }
            }
        }

        StackView {
            id: operationEdit
            Layout.fillHeight: true
            Layout.fillWidth: true
            initialItem: editRTL
        }

        RowLayout {
            Button {
                text: qsTr("Ok")
                enabled: selectMode.currentIndex >= 0 && itemIndex > 0
                onClicked: {
                    console.log(selectMode.currentIndex + " " + itemIndex)
                    if (selectMode.currentIndex >= 0 && itemIndex > 0) {
                        switch (selectMode.currentIndex) {
                        case 0: {
                            UAV.getMission().appendOperationAt(
                                        itemIndex,
                                        Mission.RTL,
                                        0, 0, 0, 0, 0, 0, 0,
                                        Mission.INVALID)
                            closeMe()
                            break;
                        }
                        case 1: {
                            UAV.getMission().appendOperationAt(
                                        itemIndex,
                                        Mission.LAND,
                                        0, 0, 0, 0,
                                        Number.fromLocaleString(Qt.locale(), landLatitudeField.text),
                                        Number.fromLocaleString(Qt.locale(), landLongitudeField.text), 0,
                                        Mission.INVALID)
                            closeMe()
                            break;
                        }
                        }
                    }
                }
            }
            Button {
                text: qsTr("Exit")
                onClicked: closeMe()
            }
        }
    }
}
