import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Window 2.14
import QtLocation 5.6
import QtPositioning 5.6
import Finco 1.0
import QtQuick.Controls.Material 2.12

Item {

    id: mapItem

    function centerToUAV () {
        if (simpleMode || trackUAV)
            map.center = uavPosition
    }

    property variant realMapView
    property bool simpleMode: false
    onSimpleModeChanged: {
        centerToUAV()
    }

    property bool trackUAV: false
    property variant uavPosition: UAV.getPositioning().position
    onUavPositionChanged: {
        centerToUAV()
    }
    onTrackUAVChanged: {
        if (trackUAV)
            centerToUAV()
    }
    function zoomIn()
    {
        map.zoomLevel = map.zoomLevel+1
    }
    function zoomOut()
    {
        map.zoomLevel = map.zoomLevel-1
    }

    signal mapFocused;

    property bool addPointOnMapClick: false


    Image {
        id: mapUAVItemComponent
        source: "qrc:/svg/uav.svg"
        width: mapItem.width / 15
        height: width
        antialiasing: true
        smooth: true
    }



    Map {
        anchors.fill: parent
        id: map

        gesture.acceptedGestures: MapGestureArea.PanGesture | MapGestureArea.FlickGesture | MapGestureArea.PinchGesture | MapGestureArea.RotationGesture | MapGestureArea.TiltGesture
        gesture.flickDeceleration: 3000
        gesture.enabled: true

        gesture.onPanStarted: {
            trackUAV = false
            mapFocused()
        }


        // UAV component
        MapQuickItem  {
            id: mapUAVItemComponentItem
            anchorPoint.x: mapUAVItemComponent.width / 2
            anchorPoint.y: mapUAVItemComponent.height / 2
            sourceItem: mapUAVItemComponent
            coordinate: UAV.getPositioning().position
            rotation: UAV.getPositioning().attitude.z
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (addPointOnMapClick && !simpleMode) {
                    var pos = map.toCoordinate(Qt.point(
                                         mouse.x,
                                         mouse.y))
                    pos.altitude = UAV.getMission().defaultAltitude
                    UAV.getMission().appendSimplePoint(pos)
                }
            }
        }

        MapItemView {
            model: UAV.getMission()
            delegate: MapQuickItem {
                /*sourceItem: Rectangle {
                    width: 20
                    height: 20
                    color: "red"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            UAV.getMission().removeOne(index)
                        }
                    }
                }*/
                sourceItem: RoundButton {
                    width: map.width / 20
                    height: width
                    radius: width / 2
                    Material.background: Material.Teal
                    onClicked: {
                        UAV.getMission().removeOne(index)
                    }
                }

                coordinate: QtPositioning.coordinate(lat, lon, alt)
            }
        }
    }


    // select map plugin type and source
    function setMapType (provider, type){
        Configuration.mapProviderName = provider
        Configuration.mapTypeName = type

        var tmpMap = Qt.createQmlObject ('import QtLocation 5.12; Plugin { name:"' + provider +'"}', mapItem)
        map.plugin = tmpMap

        // mapPlugin.name = provider
        for (var i = 0; i < map.supportedMapTypes.length; i++) {
            if (map.supportedMapTypes[i].name === type) {
                map.activeMapType = map.supportedMapTypes[i]
            }
        }
    }
    Component.onCompleted: {
        setMapType(Configuration.mapProviderName, Configuration.mapTypeName)
    }
}
