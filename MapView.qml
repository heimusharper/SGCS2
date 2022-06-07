import QtQuick 2.0
import QtQuick.Window 2.14
import QtLocation 5.6
import QtPositioning 5.6

Item {

    id: mapItem
    property variant realMapView

    anchors.fill: parent

    Plugin {
        id: mapPlugin
    }

    Map {
        anchors.fill: parent
        id: map
        plugin: mapPlugin
        color: "red"
    }

    function setMapType (provider, type){
        mapPlugin.name = provider
        for (var i = 0; i < map.supportedMapTypes.length; i++) {
            if (map.supportedMapTypes[i].name === type) {
                map.activeMapType = map.supportedMapTypes[i]
            }
        }
    }


}
