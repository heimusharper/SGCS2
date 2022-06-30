import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {

    id: root
    property int buttonsSize: 30

    signal zoomIn()
    signal zoomOut()
    signal trackUAV()
    width: mcl.childrenRect.width
    height: mcl.childrenRect.height

    ColumnLayout {
        id: mcl
        RoundButton {
            id: trackButton
            width: buttonsSize
            height: buttonsSize
            radius: 10
            text: "O"
            onClicked: {
                trackUAV()
            }
        }
        RoundButton {
            id: zoomInButton
            width: buttonsSize
            height: buttonsSize
            radius: 10
            text: "+"
            onClicked: {
                zoomIn()
            }
        }
        RoundButton {
            id: zoomOutButton
            width: buttonsSize
            height: buttonsSize
            radius: 10
            text: "-"
            onClicked: {
                zoomOut()
            }
        }
    }
}
