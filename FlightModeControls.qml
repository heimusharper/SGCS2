import QtQuick 2.0
import QtQuick.Controls 2.15

Item {

    id: root
    property bool showAdditionalActions: false

    Item {
        id: additionalActions
        visible: showAdditionalActions
        anchors.right: parent.right
        anchors.bottom: showAdditionalActionsButton.top
        // anchors.bottomMargin: 10
        anchors.rightMargin: 10
        width: showAdditionalActionsButton.width
        height: (showAdditionalActionsButton.height + 10) * additionalActionsColumn.visibleChildren.length

        Column {
            id: additionalActionsColumn
            spacing: 10
            anchors.fill: parent
            RoundButton {
                id: armButton
                width: root.width / 15
                height: width
                radius: width / 2
                icon.source: "qrc:/svg/takeoff.svg"
                onClicked: {
                    UAV.doARM()
                }
            }
            RoundButton {
                id: rtlButton
                width: root.width / 15
                height: width
                radius: width / 2
                icon.source: "qrc:/svg/rtl.svg"
                onClicked: {
                    UAV.doRTL()
                }
            }
            RoundButton {
                id: landButton
                width: root.width / 15
                height: width
                radius: width / 2
                icon.source: "qrc:/svg/land.svg"
                onClicked: {
                    UAV.doLand()
                }
            }
        }
    }

    RoundButton {
        id: showAdditionalActionsButton
        width: root.width / 15
        height: width
        radius: width / 2
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.rightMargin: 10
        font.pixelSize: height * 0.8
        text: "\u03A3"
        onClicked: {
            showAdditionalActions = !showAdditionalActions
        }
    }

}
