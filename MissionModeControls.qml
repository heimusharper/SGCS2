import QtQuick 2.0
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.15

Item {

    id: root
    property bool showAdditionalActions: false
    property bool addPointModeEnabled: true

    signal pointModeSet()

    Component.onCompleted: {
        pointModeSet()
    }
    onAddPointModeEnabledChanged: {
        pointModeSet    ()
    }
    onVisibleChanged: {
        if (!visible) {
            addPointModeEnabled = false;
        } else {
            addPointModeEnabled = true;
        }
    }

    // down side

    Item {
        id: infoLine
        height: root.height / 20
        width: ex.childrenRect.width
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            anchors.fill: parent
            color: Material.color(Material.Grey)
        }

        Row {
            id: ex

            anchors.fill: parent

            Text {
                text: "info"
                font.pixelSize: infoLine.height
            }

        }
    }

    Item {
        id: additionalActions2
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 10
        anchors.topMargin: 10
        width: showAdditionalActionsButton.width
        height: (showAdditionalActionsButton.height + 10) * additionalActionsColumn.visibleChildren.length

        Column {
            spacing: 10
            anchors.fill: parent
            RoundButton {
                id: addPointButton
                width: root.width / 15
                height: width
                radius: width / 2
                text: "\uFF0B"
                checked: addPointModeEnabled
                font.pixelSize: height * 0.8
                onClicked: {
                    addPointModeEnabled = !addPointModeEnabled
                }
            }
            RoundButton {
                id: addOperationButton
                width: root.width / 15
                height: width
                radius: width / 2
                text: "\u2219"
                font.pixelSize: height * 0.8
                onClicked: {
                }
            }
            RoundButton {
                id: undoButton
                width: root.width / 15
                height: width
                radius: width / 2
                text: "\u238C"
                font.pixelSize: height * 0.8
                onClicked: {
                }
            }
        }
    }


    // left side

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
                id: uploadButton
                width: root.width / 15
                height: width
                radius: width / 2
                text: "\u2B71"
                font.pixelSize: height * 0.8
                onClicked: {
                }
            }
            RoundButton {
                id: downloadButton
                width: root.width / 15
                height: width
                radius: width / 2
                text: "\u2B79"
                font.pixelSize: height * 0.8
                onClicked: {
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
