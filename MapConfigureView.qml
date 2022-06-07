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
                console.log("Current index " + currentIndex)
                var myArray = new Array
                var tmpMap = Qt.createQmlObject ('import QtLocation 5.12; Map { plugin: Plugin { name:"' + textAt(currentIndex) +'"} }', configureRoot)
                console.log("Find maps for " + textAt(currentIndex))
                for (var i = 0; i < tmpMap.supportedMapTypes.length; i++) {
                    myArray.push(tmpMap.supportedMapTypes[i].name)
                    console.log("Founded " + tmpMap.supportedMapTypes[i].name)
                }
                mapProvider = textAt(currentIndex)
                mapTypesComboBox.model = myArray
            }
        }
        Text {
            id: mapTypeText
            text: qsTr("Type")
        }
        ComboBox {
            id: mapTypesComboBox
            onCurrentIndexChanged: {
                mapType = textAt(currentIndex)
            }
        }
    }
}
