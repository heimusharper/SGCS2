import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Window 2.14
import QtLocation 5.6
import QtPositioning 5.6
import Finco 1.0

Item {

    id: mapItem
    anchors.fill: parent

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

    property bool showAdditionalActions: false


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
            showAdditionalActions = false
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
    }

    // controls
    RoundButton {
        visible: !simpleMode
        id: trackUAVButton
        width: mapItem.width / 15
        height: width
        radius: width / 2
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.rightMargin: 10
        icon.source: "qrc:/svg/track_uav.svg"
        onClicked: {
            trackUAV = !trackUAV
            if (trackUAV)
                centerToUAV()
        }
    }


    Item {
        id: additionalActions
        visible: showAdditionalActions
        anchors.right: parent.right
        anchors.bottom: showAdditionalActionsButton.top
        // anchors.bottomMargin: 10
        anchors.rightMargin: 10
        width: showAdditionalActionsButton.width
        height: (showAdditionalActionsButton.height + 10) * additionalActionsColumn.visibleChildren.length

        Column {
            id: additionalActionsColumn
            spacing: 10
            anchors.fill: parent
            RoundButton {
                id: armButton
                width: mapItem.width / 15
                height: width
                radius: width / 2
                icon.source: "qrc:/svg/takeoff.svg"
            }
            RoundButton {
                id: rtlButton
                width: mapItem.width / 15
                height: width
                radius: width / 2
                icon.source: "qrc:/svg/rtl.svg"
            }
            RoundButton {
                id: landButton
                width: mapItem.width / 15
                height: width
                radius: width / 2
                icon.source: "qrc:/svg/land.svg"
            }
        }
    }
    RoundButton {
        id: showAdditionalActionsButton
        visible: !simpleMode
        width: mapItem.width / 15
        height: width
        radius: width / 2
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.rightMargin: 10
        text: "\u03A3"
        onClicked: {
            showAdditionalActions = !showAdditionalActions
        }
    }

    // select map plugin type and source
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
