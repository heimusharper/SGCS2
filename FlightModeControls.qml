import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {

    id: root
    property bool showAdditionalActions: false
    property int buttonsSize: 30

    width: mcl.childrenRect.width
    height: mcl.childrenRect.height

    RowLayout {
        id: mcl
        ColumnLayout {

            RoundButton {
                id: armButton
                //width: buttonsSize
                height: buttonsSize
                radius: 10
                visible: showAdditionalActions
                text: qsTr("Start")
                onClicked: {
                    UAV.doARM()
                }
            }
            RoundButton {
                id: rtlButton
                //width: buttonsSize
                height: buttonsSize
                radius: 10
                visible: showAdditionalActions
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
                visible: showAdditionalActions
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
