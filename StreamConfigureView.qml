import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12
import Finco 1.0

Item {
    id: configureRoot

    property var videoStreamAddress

    Rectangle {
        anchors.fill: parent
        color: "white"
    }

    Column {
        Grid {
            columns: 2

            Text {
                id: mapProviderText
                text: qsTr("Stream address")
            }

            TextField{
                id: videoURIInput
                text: Configuration.streamLast
            }
        }
        CheckBox {
            id: autoconnectCheckBox
            text: qsTr("Auto connect on start")
            checked: Configuration.streamAutoConnect
        }
        Button {
            text: qsTr("Apply")
            onClicked: {
                videoStreamAddress = videoURIInput.text

                Configuration.streamAutoConnect = autoconnectCheckBox.checked
                Configuration.streamLast = videoURIInput.text
            }
        }
    }

}
