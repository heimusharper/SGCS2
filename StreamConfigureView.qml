import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12

Item {
    id: configureRoot

    property var videoStreamAddress

    Column {
        Grid {
            columns: 2

            Text {
                id: mapProviderText
                text: qsTr("Stream address")
            }

            TextField{
                id: videoURIInput
                text: "rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mp4"
            }
        }
        CheckBox {
            text: qsTr("Auto connect on start")
        }
        Button {
            text: qsTr("Apply")
            onClicked: {
                videoStreamAddress = videoURIInput.text
            }
        }
    }

}
