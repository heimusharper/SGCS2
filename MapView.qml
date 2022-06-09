import QtQuick 2.0
import QtQuick.Window 2.14
import QtLocation 5.6
import QtPositioning 5.6

Item {

    id: mapItem
    property variant realMapView

    anchors.fill: parent

    //Plugin {
    //    id: mapPlugin
    //    name: "osm"
    //}

    Map {
        anchors.fill: parent
        id: map
        //plugin: mapPlugin

        gesture.acceptedGestures: MapGestureArea.PanGesture | MapGestureArea.FlickGesture | MapGestureArea.PinchGesture | MapGestureArea.RotationGesture | MapGestureArea.TiltGesture
        gesture.flickDeceleration: 3000
        gesture.enabled: true
    }

    function setMapType (provider, type){
        var tmpMap = Qt.createQmlObject ('import QtLocation 5.12; Plugin { name:"' + provider +'"}', mapItem)
        map.plugin = tmpMap

        // mapPlugin.name = provider
        for (var i = 0; i < map.supportedMapTypes.length; i++) {
            if (map.supportedMapTypes[i].name === type) {
                map.activeMapType = map.supportedMapTypes[i]
            }
        }
    }


}
