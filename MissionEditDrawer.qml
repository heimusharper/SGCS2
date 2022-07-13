import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtLocation 5.12
import QtPositioning 5.12
import QtQuick.Controls.Material 2.12
import Finco 1.0

Item {

    signal configureAt(var index, var item_type, var param1, var param2,
                       var param3, var param4, var param5, var param6, var param7,
                       var frame)
    signal addOperationOn(var index)

    function getItemName(type)
    {
        switch (type)
        {
        case Mission.SIMPLE_POINT:
            return qsTr("Point")
        case Mission.TAKEOFF:
            return qsTr("Takeoff")
        case Mission.RTL:
            return qsTr("RTL")
        case Mission.LAND:
            return qsTr("Land")
        case Mission.JUMP:
            return qsTr("Junmp")
        case Mission.DELAY:
            return qsTr("Wait delay")
        case Mission.DISTANCE:
            return qsTr("Wait distance")
        case Mission.SPEED:
            return qsTr("Speed")
        case Mission.SET_SERVO:
            return qsTr("Servo")
        case Mission.ROI:
            return qsTr("ROI")
        case Mission.CAMERA:
            return qsTr("Camera")
        case Mission.GIMBAL:
            return qsTr("Gimbal")
        case Mission.GIMBAL:
            return qsTr("Gimbal")
        case Mission.TRIGGER:
            return qsTr("Trigger")
        case Mission.PARACHUTE:
            return qsTr("Parachute")
        }
        return qsTr("Undefined")
    }

    function getItemFrameName(frame)
    {
        switch (frame) {
        case Mission.ABSOLUTE:
            return qsTr("Absolute")
        case Mission.RELATIVE:
            return qsTr("Relative")
        case Mission.RELIEF:
            return qsTr("Relief")
        }
        return qsTr("Undefined")
    }

    ColumnLayout {
        anchors.fill: parent        
        ListView {
            id: missionList
            Layout.fillHeight: true
            Layout.fillWidth: true

            Component {
                id: compDelegate
                Rectangle {
                    width: missionList.width
                    height: rmItem.height

                    Rectangle {
                        anchors.fill: parent
                        color: missionList.currentIndex === index ? "lightsteelblue" : "white"
                    }

                    ColumnLayout {
                        id: textItems
                        Text {
                            id: missionIndex
                            text: index + ": " + getItemName(type)
                        }
                        Text {
                            text: {
                                switch (type)
                                {
                                case Mission.SIMPLE_POINT: {
                                    var delay = param1
                                    return "[" + pos.latitude.toFixed(6) + "; " + pos.longitude.toFixed(6) + "; " +
                                            pos.altitude.toFixed(1) + "]; " + qsTr("wait:") +
                                            " " + ((delay < 0) ? qsTr("no") : delay) + "; " +
                                            qsTr("frame") + ": " +
                                            getItemFrameName(frame)
                                }
                                case Mission.TAKEOFF:
                                    return qsTr("Takeoff")
                                case Mission.RTL:
                                    return qsTr("RTL")
                                case Mission.LAND:
                                    return qsTr("Land")
                                case Mission.JUMP:
                                    return qsTr("Junmp")
                                case Mission.DELAY:
                                    return qsTr("Wait delay")
                                case Mission.DISTANCE:
                                    return qsTr("Wait distance")
                                case Mission.SPEED:
                                    return qsTr("Speed")
                                case Mission.SET_SERVO:
                                    return qsTr("Servo")
                                case Mission.ROI:
                                    return qsTr("ROI")
                                case Mission.CAMERA:
                                    return qsTr("Camera")
                                case Mission.GIMBAL:
                                    return qsTr("Gimbal")
                                case Mission.GIMBAL:
                                    return qsTr("Gimbal")
                                case Mission.TRIGGER:
                                    return qsTr("Trigger")
                                case Mission.PARACHUTE:
                                    break;
                                }
                                return ""
                            }
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            missionList.currentIndex = index
                        }
                        onDoubleClicked: {
                            configureAt(index, type, param1, param2, param3, param4, param5, param6, param7, frame)
                        }
                        onPressAndHold: {
                            configureAt(index, type, param1, param2, param3, param4, param5, param6, param7, frame)
                        }
                    }

                    Rectangle {
                        id: rmItem
                        height: textItems.childrenRect.height
                        anchors.right: parent.right
                        width: height
                        color: Material.color(Material.Red)
                        visible: missionList.currentIndex === index
                        Text {
                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            text: qsTr("RM")
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                UAV.getMission().removeOne(index)
                            }
                        }
                    }
                    Rectangle {
                        id: edItem
                        height: textItems.childrenRect.height
                        anchors.right: rmItem.left
                        width: height
                        color: Material.color(Material.LightBlue)
                        visible: missionList.currentIndex === index
                        Text {
                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            text: qsTr("ED")
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                configureAt(index, type, param1, param2, param3, param4, param5, param6, param7, frame)
                            }
                        }
                    }
                    Rectangle {
                        id: addItem
                        height: textItems.childrenRect.height
                        anchors.right: edItem.left
                        width: height
                        color: Material.color(Material.LightGreen)
                        visible: missionList.currentIndex === index
                        Text {
                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            text: qsTr("AD")
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                addOperationOn(index)
                            }
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
    }

}
