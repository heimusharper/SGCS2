import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12
import Finco 1.0

Item {
    id: configureRoot

    property var mapProvider
    property var mapType

    Component.onCompleted: {
        console.log("Search maping plugins...")
        var plugin = Qt.createQmlObject ('import QtLocation 5.12; Plugin {}', configureRoot)
        var myArray = new Array
        console.log("Founded " + plugin.availableServiceProviders.length + " plugins")
        for (var i = 0; i<plugin.availableServiceProviders.length; i++) {
            var tempPlugin = Qt.createQmlObject ('import QtLocation 5.12; Plugin {name: "' + plugin.availableServiceProviders[i]+ '"}', configureRoot)
            if (tempPlugin.supportsMapping())
                myArray.push(tempPlugin.name)
            console.log("Driver " + tempPlugin.name)
        }
        myArray.sort()
        providerComboBox.model = myArray
        for (var j = 0; j < myArray.length; j++) {
            if (myArray[j] === Configuration.mapProviderName) {
                providerComboBox.currentIndex = j
                break
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "white"
    }

    Grid {
        columns: 2

        Text {
            id: mapProviderText
            text: qsTr("Map provider")
        }

        ComboBox {
            id: providerComboBox
            onCurrentIndexChanged: {
                var myArray = new Array
                var tmpMap = Qt.createQmlObject ('import QtLocation 5.12; Map { plugin: Plugin { name:"' + textAt(currentIndex) +'"} }', configureRoot)
                console.log("Find maps for " + textAt(currentIndex))
                for (var i = 0; i < tmpMap.supportedMapTypes.length; i++) {
                    myArray.push(tmpMap.supportedMapTypes[i].name)
                }
                myArray.sort()
                mapTypesComboBox.model = myArray
                for (var j = 0; j < myArray.length; j++) {
                    if (myArray[j] === Configuration.mapTypeName) {
                        mapTypesComboBox.currentIndex = j
                        console.log("on found type" + j)
                        break
                    }
                    console.log("map "+ myArray[i] + "<>"+Configuration.mapTypeName+ " "+ myArray)
                }
            }
        }
        Text {
            id: mapTypeText
            text: qsTr("Type")
        }
        ComboBox {
            id: mapTypesComboBox
            onCurrentIndexChanged: {
                // mapType = textAt(currentIndex)
            }
        }
        Button {
            text: qsTr("Apply")
            onClicked: {
                mapProvider = providerComboBox.currentText
                mapType = mapTypesComboBox.currentText
            }
        }
    }
}
