import QtQuick 2.0
import QtQuick.Window 2.14
import QtLocation 5.6
import QtPositioning 5.6

Item {

    id: mapItem
    property variant realMapView

    anchors.fill: parent

    function setMapType (provider, type){
        if (realMapView)
        {
            realMapView.destroy()
        }
        realMapView = Qt.createQmlObject('import QtLocation 5.12; Map { plugin: Plugin { name:"' + provider + '"} }', mapItem);
        console.log("on load " + provider + " " + type)


        for (var i = 0; i < realMapView.supportedMapTypes.length; i++) {
            if (realMapView.supportedMapTypes[i].name == type) {
                realMapView.activeMapType = realMapView.supportedMapTypes[i]
            }
        }
    }


}
