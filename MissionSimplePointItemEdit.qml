import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtLocation 5.12
import QtPositioning 5.12
import QtQuick.Controls.Material 2.12
import Finco 1.0

Item {

    property int itemIndex: -1
    signal closeMe()
    function updateContent(index) {
        itemIndex = index
        pointLatitudeField.text = Number(UAV.getMission().itemAt(itemIndex).position.latitude)
            .toLocaleString(Qt.locale(), 'f', 6)
        pointLongitudeField.text = Number(UAV.getMission().itemAt(itemIndex).position.longitude)
            .toLocaleString(Qt.locale(), 'f', 6)
        pointAltitudeField.text = Number(UAV.getMission().itemAt(itemIndex).position.altitude)
            .toLocaleString(Qt.locale(), 'f', 2)
        pointWaitField.text = Number(UAV.getMission().itemAt(itemIndex).wait)
            .toLocaleString(Qt.locale(), 'f', 0)
    }

    ColumnLayout {
        anchors.fill: parent

        GridLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            columns: 2
            Text {
                text: qsTr("Latitude")
            }
            TextField {
                id: pointLatitudeField

                validator: DoubleValidator {
                    bottom: -360
                    top: 360
                    decimals: 6
                }
                onTextChanged: acceptableInput ? console.log("Input acceptable") : console.log("Input not acceptable")

            }
            Text {
                text: qsTr("Longitude")
            }
            TextField {
                id: pointLongitudeField

                validator: DoubleValidator {
                    bottom: -360
                    top: 360
                    decimals: 6
                }

            }
            Text {
                text: qsTr("Altitude")
            }
            TextField {
                id: pointAltitudeField

                validator: DoubleValidator {
                    bottom: -100
                    top: 100000
                    decimals: 2
                }

            }
            Text {
                text: qsTr("Wait")
            }
            TextField {
                id: pointWaitField

                validator: IntValidator {
                    bottom: -1
                    top: 360
                }
            }
        }

        RowLayout {
            Button {
                text: qsTr("Ok")
                onClicked: {

                    UAV.getMission().itemAt(itemIndex).position =
                                QtPositioning.coordinate(Number.fromLocaleString(Qt.locale(), pointLatitudeField.text),
                                                         Number.fromLocaleString(Qt.locale(), pointLongitudeField.text),
                                                         Number.fromLocaleString(Qt.locale(), pointAltitudeField.text))
                    UAV.getMission().itemAt(itemIndex).delayOnWaypoint = Number.fromLocaleString(Qt.locale(), pointWaitField.text)
                    closeMe()
                }
            }
            Button {
                text: qsTr("Exit")
                onClicked: closeMe()
            }
        }
    }
}
