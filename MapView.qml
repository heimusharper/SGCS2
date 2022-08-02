import QtQuick 2.0
import QtQuick.Controls 2.12
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
    function updateTargetVectorPath()
    {
        targetVectopPath.replaceCoordinate(0, uavPosition)
        targetVectopPath.replaceCoordinate(1, targetPosition)
    }


    property variant realMapView
    property bool simpleMode: false
    onSimpleModeChanged: {
        centerToUAV()
    }

    property bool trackUAV: false
    property variant uavPosition: UAV.getPositioning().position
    property variant targetPosition: UAV.getPositioning().targetPosition
    onUavPositionChanged: {
        centerToUAV()
        updateTargetVectorPath()
    }
    onTargetPositionChanged: {
        updateTargetVectorPath()
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

    //path: [
    //    { latitude: -27, longitude: 153.0 },
    //    { latitude: -27, longitude: 154.1 }
    //]


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
        MapPolyline {
            id: line
            path: UAV.getMission().mapPath
            line.width: 2
            line.color: 'red'
        }
        MapItemView {
            model: UAV.getMission()
            delegate: MapQuickItem {
                anchorPoint.x: roundMapItem.width/2
                anchorPoint.y: roundMapItem.height/2

                sourceItem: RoundButton {
                    id: roundMapItem
                    width: map.width / 20
                    height: width
                    radius: width / 2
                    Material.background: Material.Teal
                    visible: operation === 0
                    text: index
                    onClicked: {
                        UAV.getMission().removeOne(index)
                    }
                }

                coordinate: pos
            }
        }
        MapQuickItem {
            coordinate: UAV.homePosition
            anchorPoint.x: homeMapItem.width/2
            anchorPoint.y: homeMapItem.height/2

            sourceItem: RoundButton {
                id: homeMapItem
                width: map.width / 20
                height: width
                radius: width / 2
                Material.background: Material.Yellow
                text: "H"
                onClicked: {
                }
            }
        }


        MapPolyline {
            id: targetVectopPath

            line.width: 2
            line.color: Material.color(Material.Purple)

            path: [ { latitude: -27, longitude: 153.0 },
                        { latitude: -27, longitude: 154.1 } ]
        }


        // UAV component
        MapQuickItem  {
            property var attitudes: UAV.getPositioning().attitude

            id: mapUAVItemComponentItem
            anchorPoint.x: mapUAVItemComponent.width / 2
            anchorPoint.y: mapUAVItemComponent.height / 2
            sourceItem: mapUAVItemComponent
            coordinate: UAV.getPositioning().position
            // rotation: UAV.getPositioning().attitude.z
            onAttitudesChanged: {
                mapUAVItemComponentItem.rotation = attitudes.z
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
