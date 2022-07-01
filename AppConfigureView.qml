import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12
import Finco 1.0

Item {
    Rectangle {
        anchors.fill: parent
        color: "white"
    }

    Grid {
        columns: 2

        Text {
            text: qsTr("Langs")
        }

        ComboBox {
            id: langList

            onModelChanged: {
                for(var i = 0; i < model.count; ++i)
                    if (model.get(i) === Configuration.language)
                        langList.currentIndex = i
            }
            model: Configuration.getLanguages()
        }
        Button {
            text: qsTr("Apply")
            onClicked: {
                Configuration.language = langList.currentText
            }
        }
    }
}
