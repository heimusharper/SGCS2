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


    Item {
        id: itemPointEdit
        anchors.fill: parent
        function init(pos, wait)
        {
            pointLatitudeField.text = pos.latitude
            pointLongitudeField.text = pos.longitude
            pointAltitudeField.text = pos.altitude
            pointWaitField.text = wait
        }

        GridLayout {
            anchors.fill: parent
            columns: 2
            Text {
                text: qsTr("Latitude")
            }
            TextField {
                id: pointLatitudeField
            }
            Text {
                text: qsTr("Longitude")
            }
            TextField {
                id: pointLongitudeField
            }
            Text {
                text: qsTr("Altitude")
            }
            TextField {
                id: pointAltitudeField
            }
            Text {
                text: qsTr("Wait")
            }
            TextField {
                id: pointWaitField
            }
        }
        function save()
        {
            UAV.getMission().itemAt(itemIndex).position =
                        QtPositioning.coordinate(parseFloat(pointLatitudeField.text.replace(",", ".")),
                                                 parseFloat(pointLongitudeField.text.replace(",", ".")),
                                                 parseFloat(pointAltitudeField.text.replace(",", ".")))
            UAV.getMission().itemAt(itemIndex).delayOnWaypoint = parseInt(pointWaitField)
        }
    }
    Item {
        id: itemTakeoffEdit
    }
    Item {
        id: itemRTLEdit
    }
    Item {
        id: itemLandEdit
    }
    Item {
        id: itemJumpEdit
    }
    Item {
        id: itemDelayEdit
    }
    Item {
        id: itemDistanceEdit
    }
    Item {
        id: itemSpeedEdit
    }
    Item {
        id: itemServoEdit
    }
    Item {
        id: itemROIEdit
    }
    Item {
        id: itemCameraEdit
    }
    Item {
        id: itemGimbalEdit
    }
    Item {
        id: itemTriggerEdit
    }
    Item {
        id: itemParachuteEdit
    }

    onItemIndexChanged: {
        editDrawer.pop()
        switch (UAV.getMission().itemAt(itemIndex).type)
        {
        case MissionItem.SIMPLE_POINT:
            editDrawer.push(itemPointEdit)
            itemPointEdit.init(UAV.getMission().itemAt(itemIndex).position,
                               UAV.getMission().itemAt(itemIndex).delayOnWaypoint)
            break;
        case MissionItem.TAKEOFF:
            editDrawer.push(itemTakeoffEdit)
            break;
        case MissionItem.RTL:
            editDrawer.push(itemRTLEdit)
            break;
        case MissionItem.LAND:
            editDrawer.push(itemLandEdit)
            break;
        case MissionItem.JUMP:
            editDrawer.push(itemJumpEdit)
            break;
        case MissionItem.DELAY:
            editDrawer.push(itemDelayEdit)
            break;
        case MissionItem.DISTANCE:
            editDrawer.push(itemDistanceEdit)
            break;
        case MissionItem.SPEED:
            editDrawer.push(itemSpeedEdit)
            break;
        case MissionItem.SET_SERVO:
            editDrawer.push(itemServoEdit)
            break;
        case MissionItem.ROI:
            editDrawer.push(itemROIEdit)
            break;
        case MissionItem.CAMERA:
            editDrawer.push(itemCameraEdit)
            break;
        case MissionItem.GIMBAL:
            editDrawer.push(itemGimbalEdit)
            break;
        case MissionItem.TRIGGER:
            editDrawer.push(itemTriggerEdit)
            break;
        case MissionItem.PARACHUTE:
            editDrawer.push(itemParachuteEdit)
            break;
        }
    }

    ColumnLayout {
        anchors.fill: parent

        StackView {
            id: editDrawer
            Layout.fillHeight: true
            Layout.fillWidth: true
            initialItem: itemPointEdit
        }

        RowLayout {
            Button {
                text: qsTr("Ok")
                onClicked: {
                    switch (UAV.getMission().itemAt(itemIndex).type)
                    {
                    case MissionItem.SIMPLE_POINT:
                        itemPointEdit.save()
                        break;
                    /*case MissionItem.TAKEOFF:
                        itemTakeoffEdit.save()
                        break;
                    case MissionItem.RTL:
                        itemRTLEdit.save()
                        break;
                    case MissionItem.LAND:
                        itemLandEdit.save()
                        break;
                    case MissionItem.JUMP:
                        itemJumpEdit.save()
                        break;
                    case MissionItem.DELAY:
                        itemDelayEdit.save()
                        break;
                    case MissionItem.DISTANCE:
                        itemDistanceEdit.save()
                        break;
                    case MissionItem.SPEED:
                        itemSpeedEdit.save()
                        break;
                    case MissionItem.SET_SERVO:
                        itemServoEdit.save()
                        break;
                    case MissionItem.ROI:
                        itemROIEdit.save()
                        break;
                    case MissionItem.CAMERA:
                        itemCameraEdit.save()
                        break;
                    case MissionItem.GIMBAL:
                        itemGimbalEdit.save()
                        break;
                    case MissionItem.TRIGGER:
                        itemTriggerEdit.save()
                        break;
                    case MissionItem.PARACHUTE:
                        itemParachuteEdit.save()
                        break;*/
                    }
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
