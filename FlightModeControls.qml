import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Finco 1.0

Item {

    id: root
    property bool showAdditionalActions: false
    property int buttonsSize: 30
    property int uavMode: UAV.controlMode

    onUavModeChanged: {
        // ARM
        switch (uavMode)
        {
        case UAV.WAIT:
            armButton.text = qsTr("ARM")
            armButton.visible = true
            break;
        case UAV.ARMED:
            armButton.text = qsTr("START")
            armButton.visible = true
            break;
        default:
            armButton.visible = false
            break;
        }
        // RTL/LAND
        switch (uavMode)
        {
        case UAV.WAIT:
        case UAV.ARMED:
        case UAV.TAKEOFF:
            rtlButton.visible = false
            landButton.visible = false
            break;
        default:
            rtlButton.visible = true
            landButton.visible = true
            break;
        }
    }

    width: mcl.childrenRect.width
    height: mcl.childrenRect.height

    RowLayout {
        id: mcl
        ColumnLayout {
            id: buttonsColumn
            visible: showAdditionalActions

            RoundButton {
                id: armButton
                //width: buttonsSize
                height: buttonsSize
                radius: 10
                text: qsTr("Start")
                onClicked: {
                    switch (uavMode)
                    {
                    case UAV.WAIT:
                        UAV.doARM()
                        break;
                    case UAV.ARMED:
                        UAV.doTakeoff()
                        break;
                    default:
                        break;
                    }
                }
            }
            RoundButton {
                id: rtlButton
                //width: buttonsSize
                height: buttonsSize
                radius: 10
                text: qsTr("RTL")
                onClicked: {
                    UAV.doRTL()
                }
            }
            RoundButton {
                id: landButton
                //width: buttonsSize
                height: buttonsSize
                radius: 10
                text: qsTr("Land")
                onClicked: {
                    UAV.doLand()
                }
            }
        }
        RoundButton {
            id: showButton
            width: buttonsSize
            height: buttonsSize
            radius: 10
            checkable: true
            Layout.alignment: Qt.AlignBottom
            text: "..."
            onCheckedChanged: {
                showAdditionalActions = !showAdditionalActions
            }

        }
    }
}
