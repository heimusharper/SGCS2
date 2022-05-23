import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtLocation 5.12
import QtPositioning 5.12

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    header: MainToolBar {

    }


    Drawer {

    }

    StackView {
        id: stackView
        x: -141
        y: 96
        width: 200
        height: 200
    }
}
