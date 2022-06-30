import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtLocation 5.12
import QtPositioning 5.12
import QtQuick.Controls.Material 2.12
import Finco 1.0

Item {

    signal configureAt(var index)

    function getItemName(type)
    {
        switch (type)
        {
        case MissionItem.SIMPLE_POINT:
            return qsTr("Point")
        case MissionItem.TAKEOFF:
            return qsTr("Takeoff")
        case MissionItem.RTL:
            return qsTr("RTL")
        case MissionItem.LAND:
            return qsTr("Land")
        case MissionItem.JUMP:
            return qsTr("Junmp")
        case MissionItem.DELAY:
            return qsTr("Wait delay")
        case MissionItem.DISTANCE:
            return qsTr("Wait distance")
        case MissionItem.SPEED:
            return qsTr("Speed")
        case MissionItem.SET_SERVO:
            return qsTr("Servo")
        case MissionItem.ROI:
            return qsTr("ROI")
        case MissionItem.CAMERA:
            return qsTr("Camera")
        case MissionItem.GIMBAL:
            return qsTr("Gimbal")
        case MissionItem.GIMBAL:
            return qsTr("Gimbal")
        case MissionItem.TRIGGER:
            return qsTr("Trigger")
        case MissionItem.PARACHUTE:
            return qsTr("Parachute")
        }
        return qsTr("Undefined")
    }

    function getItemFrameName(frame)
    {
        switch (frame) {
        case MissionItem.ABSOLUTE:
            return qsTr("Absolute")
        case MissionItem.RELATIVE:
            return qsTr("Relative")
        case MissionItem.RELIEF:
            return qsTr("Relief")
        }
        return qsTr("Undefined")
    }

    function getItemAdditional(type, index)
    {
        switch (type)
        {
        case MissionItem.SIMPLE_POINT: {
            var delay = UAV.getMission().itemAt(index).delayOnWaypoint
            return "[" + UAV.getMission().itemAt(index).position.latitude.toFixed(6) + "; " +
                UAV.getMission().itemAt(index).position.longitude.toFixed(6) + "; " +
                UAV.getMission().itemAt(index).position.altitude.toFixed(1) + "] " + qsTr("wait") +
                " " + ((delay < 0) ? qsTr("no") : delay) + " " + qsTr("frame") + ": " +
                    getItemFrameName(UAV.getMission().itemAt(index).frame)
        }
        case MissionItem.TAKEOFF:
            return qsTr("Takeoff")
        case MissionItem.RTL:
            break;
        case MissionItem.LAND:
            return qsTr("Land")
        case MissionItem.JUMP:
            return qsTr("Junmp")
        case MissionItem.DELAY:
            return qsTr("Wait delay")
        case MissionItem.DISTANCE:
            return qsTr("Wait distance")
        case MissionItem.SPEED:
            return qsTr("Speed")
        case MissionItem.SET_SERVO:
            return qsTr("Servo")
        case MissionItem.ROI:
            return qsTr("ROI")
        case MissionItem.CAMERA:
            return qsTr("Camera")
        case MissionItem.GIMBAL:
            return qsTr("Gimbal")
        case MissionItem.GIMBAL:
            return qsTr("Gimbal")
        case MissionItem.TRIGGER:
            return qsTr("Trigger")
        case MissionItem.PARACHUTE:
            break;
        }
        return ""
    }

    ColumnLayout {
        anchors.fill: parent
        ListView {
            id: missionList
            Layout.fillHeight: true
            Layout.fillWidth: true

            Component {
                id: compDelegate
                Item {
                    width: missionList.width
                    height: missionIndex.height
                    Rectangle {
                        anchors.fill: parent
                        color: missionList.currentIndex === index ? "lightsteelblue" : "white"
                    }

                    Text {
                        id: missionIndex
                        text: index + ": " + getItemName(type) + " " + getItemAdditional(type, index)
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            missionList.currentIndex = index
                        }
                        onDoubleClicked: {
                            configureAt(index)
                        }
                        onPressAndHold: {
                            configureAt(index)
                        }
                    }
                }
            }

            onCurrentIndexChanged: {
                console.log("on change current " + currentIndex)
            }

            delegate: compDelegate

            model: UAV.getMission()
            focus: true
        }
        RowLayout {
            Button {
                text: qsTr("Add operation")
                onClicked: {

                }
            }
            Button {
                text: qsTr("Edit")
                onClicked: configureAt(missionList.currentIndex)
            }
            Button {
                text: qsTr("Delete")
                onClicked: UAV.getMission().removeOne(missionList.currentIndex)
            }
        }
    }

}
