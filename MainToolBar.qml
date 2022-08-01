import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.10
import QtQuick.Controls.Material 2.10

import Finco 1.0



ToolBar {
    id: toolBarRoot
    // signals
    signal activateFlightMode()
    signal activateMissionMode()
    signal activateBurger()


    Popup {
        id: statusPopup
        x: parent.width / 2 - width / 2.
        y: parent.height
        padding: 10
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        onOpened: {
            {
                switch(UAV.getFailsafe().stateGyros) {
                case Failsafe.SENSOR_ERROR:
                    textGyros.text = qsTr("Error")
                    textGyros.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textGyros.text = qsTr("Not present")
                    textGyros.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textGyros.text = qsTr("Ready")
                    textGyros.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateAccels) {
                case Failsafe.SENSOR_ERROR:
                    textAccels.text = qsTr("Error")
                    textAccels.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textAccels.text = qsTr("Not present")
                    textAccels.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textAccels.text = qsTr("Ready")
                    textAccels.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateMagnetometer) {
                case Failsafe.SENSOR_ERROR:
                    textMags.text = qsTr("Error")
                    textMags.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textMags.text = qsTr("Not present")
                    textMags.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textMags.text = qsTr("Ready")
                    textMags.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateAbsPressure) {
                case Failsafe.SENSOR_ERROR:
                    textABSPres.text = qsTr("Error")
                    textABSPres.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textABSPres.text = qsTr("Not present")
                    textABSPres.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textABSPres.text = qsTr("Ready")
                    textABSPres.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateDiffPressure) {
                case Failsafe.SENSOR_ERROR:
                    textDIFPres.text = qsTr("Error")
                    textDIFPres.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textDIFPres.text = qsTr("Not present")
                    textDIFPres.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textDIFPres.text = qsTr("Ready")
                    textDIFPres.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateGPS) {
                case Failsafe.SENSOR_ERROR:
                    textGPS.text = qsTr("Error")
                    textGPS.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textGPS.text = qsTr("Not present")
                    textGPS.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textGPS.text = qsTr("Ready")
                    textGPS.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateOpticalFlow) {
                case Failsafe.SENSOR_ERROR:
                    textOptFlow.text = qsTr("Error")
                    textOptFlow.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textOptFlow.text = qsTr("Not present")
                    textOptFlow.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textOptFlow.text = qsTr("Ready")
                    textOptFlow.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateVisionPosition) {
                case Failsafe.SENSOR_ERROR:
                    textVisPos.text = qsTr("Error")
                    textVisPos.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textVisPos.text = qsTr("Not present")
                    textVisPos.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textVisPos.text = qsTr("Ready")
                    textVisPos.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateLaserPosition) {
                case Failsafe.SENSOR_ERROR:
                    textLaserPos.text = qsTr("Error")
                    textLaserPos.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textLaserPos.text = qsTr("Not present")
                    textLaserPos.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textLaserPos.text = qsTr("Ready")
                    textLaserPos.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateAngularRateControl) {
                case Failsafe.SENSOR_ERROR:
                    textAngRateCtrl.text = qsTr("Error")
                    textAngRateCtrl.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textAngRateCtrl.text = qsTr("Not present")
                    textAngRateCtrl.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textAngRateCtrl.text = qsTr("Ready")
                    textAngRateCtrl.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateAttitudeStabilization) {
                case Failsafe.SENSOR_ERROR:
                    textAttStab.text = qsTr("Error")
                    textAttStab.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textAttStab.text = qsTr("Not present")
                    textAttStab.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textAttStab.text = qsTr("Ready")
                    textAttStab.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateYawControl) {
                case Failsafe.SENSOR_ERROR:
                    textYawControl.text = qsTr("Error")
                    textYawControl.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textYawControl.text = qsTr("Not present")
                    textYawControl.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textYawControl.text = qsTr("Ready")
                    textYawControl.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateZControl) {
                case Failsafe.SENSOR_ERROR:
                    textAltControl.text = qsTr("Error")
                    textAltControl.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textAltControl.text = qsTr("Not present")
                    textAltControl.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textAltControl.text = qsTr("Ready")
                    textAltControl.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateXYControl) {
                case Failsafe.SENSOR_ERROR:
                    textXYControl.text = qsTr("Error")
                    textXYControl.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textXYControl.text = qsTr("Not present")
                    textXYControl.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textXYControl.text = qsTr("Ready")
                    textXYControl.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateMotorOut) {
                case Failsafe.SENSOR_ERROR:
                    textMotorOut.text = qsTr("Error")
                    textMotorOut.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textMotorOut.text = qsTr("Not present")
                    textMotorOut.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textMotorOut.text = qsTr("Ready")
                    textMotorOut.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateRC) {
                case Failsafe.SENSOR_ERROR:
                    textRC.text = qsTr("Error")
                    textRC.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textRC.text = qsTr("Not present")
                    textRC.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textRC.text = qsTr("Ready")
                    textRC.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateGeoFence) {
                case Failsafe.SENSOR_ERROR:
                    textGeoFence.text = qsTr("Error")
                    textGeoFence.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textGeoFence.text = qsTr("Not present")
                    textGeoFence.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textGeoFence.text = qsTr("Ready")
                    textGeoFence.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateAHRS) {
                case Failsafe.SENSOR_ERROR:
                    textAHRS.text = qsTr("Error")
                    textAHRS.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textAHRS.text = qsTr("Not present")
                    textAHRS.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textAHRS.text = qsTr("Ready")
                    textAHRS.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateTerrain) {
                case Failsafe.SENSOR_ERROR:
                    textTerrain.text = qsTr("Error")
                    textTerrain.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textTerrain.text = qsTr("Not present")
                    textTerrain.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textTerrain.text = qsTr("Ready")
                    textTerrain.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateReverseMotor) {
                case Failsafe.SENSOR_ERROR:
                    textReverseMotor.text = qsTr("Error")
                    textReverseMotor.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textReverseMotor.text = qsTr("Not present")
                    textReverseMotor.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textReverseMotor.text = qsTr("Ready")
                    textReverseMotor.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateLogging) {
                case Failsafe.SENSOR_ERROR:
                    textLogging.text = qsTr("Error")
                    textLogging.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textLogging.text = qsTr("Not present")
                    textLogging.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textLogging.text = qsTr("Ready")
                    textLogging.color = Material.color(Material.Green)
                    break
                }
                console.log("logging " + UAV.getFailsafe().stateLogging)
            }
            {
                switch(UAV.getFailsafe().stateBattery) {
                case Failsafe.SENSOR_ERROR:
                    textBattery.text = qsTr("Error")
                    textBattery.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textBattery.text = qsTr("Not present")
                    textBattery.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textBattery.text = qsTr("Ready")
                    textBattery.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateProximity) {
                case Failsafe.SENSOR_ERROR:
                    textProximity.text = qsTr("Error")
                    textProximity.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textProximity.text = qsTr("Not present")
                    textProximity.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textProximity.text = qsTr("Ready")
                    textProximity.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateSatCom) {
                case Failsafe.SENSOR_ERROR:
                    textSatCom.text = qsTr("Error")
                    textSatCom.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textSatCom.text = qsTr("Not present")
                    textSatCom.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textSatCom.text = qsTr("Ready")
                    textSatCom.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().stateObstacleAviodance) {
                case Failsafe.SENSOR_ERROR:
                    textObstAviodance.text = qsTr("Error")
                    textObstAviodance.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textObstAviodance.text = qsTr("Not present")
                    textObstAviodance.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textObstAviodance.text = qsTr("Ready")
                    textObstAviodance.color = Material.color(Material.Green)
                    break
                }
            }
            {
                switch(UAV.getFailsafe().statePropulsion) {
                case Failsafe.SENSOR_ERROR:
                    textPropulsion.text = qsTr("Error")
                    textPropulsion.color = Material.color(Material.Red)
                    break
                case Failsafe.SENSOR_NOT_PRESENT:
                    textPropulsion.text = qsTr("Not present")
                    textPropulsion.color = Material.color(Material.Grey)
                    break
                case Failsafe.SENSOR_READY:
                    textPropulsion.text = qsTr("Ready")
                    textPropulsion.color = Material.color(Material.Green)
                    break
                }
            }
        }

        ScrollView {
            anchors.fill: parent
            clip : true
            ScrollBar.vertical.interactive: true
            GridLayout {
                anchors.fill: parent
                columns: 2
                Text {
                    text: qsTr("Gyroscope")
                }
                Text {
                    id: textGyros
                }
                Text {
                    text: qsTr("Accelerometer")
                }
                Text {
                    id: textAccels
                }
                Text {
                    text: qsTr("Magnetometer")
                }
                Text {
                    id: textMags
                }
                Text {
                    text: qsTr("Abs. Pressure")
                }
                Text {
                    id: textABSPres
                }
                Text {
                    text: qsTr("Diff. Pressure")
                }
                Text {
                    id: textDIFPres
                }
                Text {
                    text: qsTr("GPS")
                }
                Text {
                    id: textGPS
                }
                Text {
                    text: qsTr("Optical flow")
                }
                Text {
                    id: textOptFlow
                }
                Text {
                    text: qsTr("Vision position")
                }
                Text {
                    id: textVisPos
                }
                Text {
                    text: qsTr("Laser position")
                }
                Text {
                    id: textLaserPos
                }
                Text {
                    text: qsTr("Angular rate control")
                }
                Text {
                    id: textAngRateCtrl
                }
                Text {
                    text: qsTr("Attitude stabilization")
                }
                Text {
                    id: textAttStab
                }
                Text {
                    text: qsTr("Yaw control")
                }
                Text {
                    id: textYawControl
                }
                Text {
                    text: qsTr("Altitude control")
                }
                Text {
                    id: textAltControl
                }
                Text {
                    text: qsTr("Position control")
                }
                Text {
                    id: textXYControl
                }
                Text {
                    text: qsTr("Motor out")
                }
                Text {
                    id: textMotorOut
                }
                Text {
                    text: qsTr("RC")
                }
                Text {
                    id: textRC
                }
                Text {
                    text: qsTr("GeoFence")
                }
                Text {
                    id: textGeoFence
                }
                Text {
                    text: qsTr("AHRS")
                }
                Text {
                    id: textAHRS
                }
                Text {
                    text: qsTr("Terrain")
                }
                Text {
                    id: textTerrain
                }
                Text {
                    text: qsTr("Reverse motor")
                }
                Text {
                    id: textReverseMotor
                }
                Text {
                    text: qsTr("Logging")
                }
                Text {
                    id: textLogging
                }
                Text {
                    text: qsTr("Battery")
                }
                Text {
                    id: textBattery
                }
                Text {
                    text: qsTr("Proximity")
                }
                Text {
                    id: textProximity
                }
                Text {
                    text: qsTr("Satellite communication")
                }
                Text {
                    id: textSatCom
                }
                Text {
                    text: qsTr("Obstacle aviodance")
                }
                Text {
                    id: textObstAviodance
                }
                Text {
                    text: qsTr("Propulsion")
                }
                Text {
                    id: textPropulsion
                }
            }
        }
    }

    Popup {
        id: outerPopup
        x: parent.width - width
        y: parent.height
        padding: 10
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        ColumnLayout {
            anchors.fill: parent

            RadioButton {
                text: "UDP"
                checked: Configuration.connectionMethod === "udp"
                onClicked: {
                    connectionStack.currentIndex = 0
                }
            }
            RadioButton {
                text: "Serial"
                checked: Configuration.connectionMethod === "serial"
                onClicked: {
                    connectionStack.currentIndex = 1
                }
            }
            Component.onCompleted: {
                if (Configuration.connectionMethod === "udp")
                    connectionStack.currentIndex = 0
                else if (Configuration.connectionMethod === "serial")
                    connectionStack.currentIndex = 1
                else
                    connectionStack.currentIndex = 2
            }

            StackLayout {
                id: connectionStack
                Item {
                    implicitWidth: gridOfUDP.width
                    implicitHeight: gridOfUDP.height
                    id: udpView
                    GridLayout {
                        id: gridOfUDP
                        // horizontalItemAlignment: Qt.AlignHCenter
                        // verticalItemAlignment: Qt.AlignVCenter
                        columns: 2
                        // spacing: 5

                        Text {
                            text: "UDP"
                        }
                        Button {
                            text: "Connect"
                            onClicked: {
                                outerPopup.close();
                                Configuration.connectionMethod = "udp"
                                Configuration.connectionUDPHost = udpHostField.text
                                Configuration.connectionUDPPort = udpPortField.value
                                UAV.connection().connectToUDP(udpHostField.text, udpPortField.value);
                            }
                        }
                        Text {
                            text: "Host"
                        }
                        TextField {
                            id: udpHostField
                            text: Configuration.connectionUDPHost
                        }

                        Text {
                            text: "Port"
                        }

                        SpinBox {
                            id: udpPortField
                            value: Configuration.connectionUDPPort
                            from: 1024
                            to: 64000
                        }
                    }
                }

                Item {
                    implicitWidth: gridOfSerial.width
                    implicitHeight: gridOfSerial.height
                    id: serialView
                    GridLayout {
                        id: gridOfSerial
                        // horizontalItemAlignment: Qt.AlignHCenter
                        // verticalItemAlignment: Qt.AlignVCenter
                        columns: 2
                        // spacing: 5

                        Text {
                            text: "Serial"
                        }
                        Button {
                            text: "Connect"
                            onClicked: {
                                outerPopup.close();
                                Configuration.connectionMethod = "serial"
                                Configuration.connectionSerialPort = serialPortField.text
                                UAV.connection().connectToUART(serialPortField.text);
                            }
                        }
                        Text {
                            text: "Port"
                        }
                        TextField {
                            id: serialPortField
                            text: Configuration.connectionSerialPort
                        }
                    }
                }
            }
        }
    }


    function checkErrors() {
        if (stateGyros === Failsafe.SENSOR_ERROR ||
                stateAccels === Failsafe.SENSOR_ERROR ||
                stateMagnetometer === Failsafe.SENSOR_ERROR ||
                stateAbsPressure === Failsafe.SENSOR_ERROR ||
                stateDiffPressure === Failsafe.SENSOR_ERROR ||
                stateGPS === Failsafe.SENSOR_ERROR ||
                stateOpticalFlow === Failsafe.SENSOR_ERROR ||
                stateVisionPosition === Failsafe.SENSOR_ERROR ||
                stateLaserPosition === Failsafe.SENSOR_ERROR ||
                stateAngularRateControl === Failsafe.SENSOR_ERROR ||
                stateAttitudeStabilization === Failsafe.SENSOR_ERROR ||
                stateYawControl === Failsafe.SENSOR_ERROR ||
                stateZControl === Failsafe.SENSOR_ERROR ||
                stateXYControl === Failsafe.SENSOR_ERROR ||
                stateMotorOut === Failsafe.SENSOR_ERROR||
                stateRC === Failsafe.SENSOR_ERROR||
                stateGeoFence === Failsafe.SENSOR_ERROR||
                stateAHRS === Failsafe.SENSOR_ERROR||
                stateTerrain === Failsafe.SENSOR_ERROR||
                stateReverseMotor === Failsafe.SENSOR_ERROR||
                stateLogging === Failsafe.SENSOR_ERROR||
                stateBattery === Failsafe.SENSOR_ERROR||
                stateProximity === Failsafe.SENSOR_ERROR||
                stateSatCom === Failsafe.SENSOR_ERROR||
                stateObstacleAviodance === Failsafe.SENSOR_ERROR||
                statePropulsion === Failsafe.SENSOR_ERROR) {
            backgroudItem.color = Material.color(Material.Red)
            failureIndicator.text = "!"
        } else {
            backgroudItem.color = Material.color(Material.Cyan)
            failureIndicator.text = "+"
        }
    }
    property var stateGyros: UAV.getFailsafe().stateGyros
    onStateGyrosChanged: checkErrors()
    property var stateAccels: UAV.getFailsafe().stateAccels
    onStateAccelsChanged: checkErrors()
    property var stateMagnetometer: UAV.getFailsafe().stateMagnetometer
    onStateMagnetometerChanged: checkErrors()
    property var stateAbsPressure: UAV.getFailsafe().stateAbsPressure
    onStateAbsPressureChanged: checkErrors()
    property var stateDiffPressure: UAV.getFailsafe().stateDiffPressure
    onStateDiffPressureChanged: checkErrors()
    property var stateGPS: UAV.getFailsafe().stateGPS
    onStateGPSChanged: checkErrors()
    property var stateOpticalFlow: UAV.getFailsafe().stateOpticalFlow
    onStateOpticalFlowChanged: checkErrors()
    property var stateVisionPosition: UAV.getFailsafe().stateVisionPosition
    onStateVisionPositionChanged: checkErrors()
    property var stateLaserPosition: UAV.getFailsafe().stateLaserPosition
    onStateLaserPositionChanged: checkErrors()
    property var stateAngularRateControl: UAV.getFailsafe().stateAngularRateControl
    onStateAngularRateControlChanged: checkErrors()
    property var stateAttitudeStabilization: UAV.getFailsafe().stateAttitudeStabilization
    onStateAttitudeStabilizationChanged: checkErrors()
    property var stateYawControl: UAV.getFailsafe().stateYawControl
    onStateYawControlChanged: checkErrors()
    property var stateZControl: UAV.getFailsafe().stateZControl
    onStateZControlChanged: checkErrors()
    property var stateXYControl: UAV.getFailsafe().stateXYControl
    onStateXYControlChanged: checkErrors()
    property var stateMotorOut: UAV.getFailsafe().stateMotorOut
    onStateMotorOutChanged: checkErrors()
    property var stateRC: UAV.getFailsafe().stateRC
    onStateRCChanged: checkErrors()
    property var stateGeoFence: UAV.getFailsafe().stateGeoFence
    onStateGeoFenceChanged: checkErrors()
    property var stateAHRS: UAV.getFailsafe().stateAHRS
    onStateAHRSChanged: checkErrors()
    property var stateTerrain: UAV.getFailsafe().stateTerrain
    onStateTerrainChanged: checkErrors()
    property var stateReverseMotor: UAV.getFailsafe().stateReverseMotor
    onStateReverseMotorChanged: checkErrors()
    property var stateLogging: UAV.getFailsafe().stateLogging
    onStateLoggingChanged: checkErrors()
    property var stateBattery: UAV.getFailsafe().stateBattery
    onStateBatteryChanged: checkErrors()
    property var stateProximity: UAV.getFailsafe().stateProximity
    onStateProximityChanged: checkErrors()
    property var stateSatCom: UAV.getFailsafe().stateSatCom
    onStateSatComChanged: checkErrors()
    property var stateObstacleAviodance: UAV.getFailsafe().stateObstacleAviodance
    onStateObstacleAviodanceChanged: checkErrors()
    property var statePropulsion: UAV.getFailsafe().statePropulsion
    onStatePropulsionChanged: checkErrors()



    background: Rectangle {
        id: backgroudItem
        color: Material.color(Material.Red)
    }

    function getGPSText (n) {
        switch(n) {
        case Sensors.ERROR:
            return "ER"
        case Sensors.FIX2D:
            return "2D"
        case Sensors.FIX3D:
            return "3D"
        case Sensors.DGPS:
            return "DGPS"
        case Sensors.RTKFIX:
            return "RTK FIX"
        case Sensors.RTKFLOAT:
            return "RTK FLOAT"
        case Sensors.STATIC:
            return "STATIC"
        case Sensors.PPP:
            return "PPP"
        case Sensors.NA:
        default:
            return "NA"
        }
    }
    function getGPSColor (n) {
        switch(n) {
        case Sensors.ERROR:
            return Material.color(Material.Red)
        case Sensors.FIX2D:
            return Material.color(Material.Amber)
        case Sensors.FIX3D:
        case Sensors.DGPS:
        case Sensors.RTKFIX:
        case Sensors.RTKFLOAT:
            return Material.color(Material.Green)
        case Sensors.STATIC:
        case Sensors.PPP:
            return Material.color(Material.Blue)
        case Sensors.NA:
        default:
            return Material.color(Material.Grey)
        }
    }

    ColumnLayout {
        spacing: 0
        anchors.fill: parent
         RowLayout {
             id: buttonsLayout

             ToolButton {
                 id: toolButton
                 text: stackView.depth > 1 ? "\u25C0" : "\u2630"
                 font.pixelSize: height / 2
                 onClicked: {
                     activateBurger()
                 }
             }
             ToolButton {
                 id: gps
                 text:  getGPSText(UAV.getSensors().gpsStatus)
                 font.pixelSize: height / 2
                 icon.name: "satelites"
                 icon.color: getGPSColor(UAV.getSensors().gpsStatus)
             }
             Item {
                 Layout.fillWidth: true
             }
             ToolButton {
                 id: failureIndicator
                 text: "?"
                 // visible: UAV.connection().connected
                 font.pixelSize: height / 2
                 onClicked: {
                     statusPopup.open()
                    // toolBarRoot.activateFlightMode()
                 }
             }
             ToolButton {
                 id: flightMode
                 text: "FM"
                 // visible: UAV.connection().connected
                 font.pixelSize: height / 2
                 onClicked: {
                    toolBarRoot.activateFlightMode()
                 }
             }
             ToolButton {
                 id: missionMode
                 text: "MM"
                 // visible: UAV.connection().connected
                 font.pixelSize: height / 2
                 onClicked: {
                     toolBarRoot.activateMissionMode()
                 }
             }
             ToolButton {
                 id: connectionButton
                 visible: !UAV.connection().connected
                 text: "Connect"
                 height: buttonsLayout.height
                 font.pixelSize: height / 2
                 onClicked: {
                     outerPopup.open() // connection popup
                 }
                 Rectangle {
                     anchors.fill: parent
                     anchors.margins: 0
                     color: Material.color(Material.LightRed)
                 }
             }
         }
         Rectangle {
             Layout.fillWidth: true
             height: 4
             color: Material.color(Material.Cyan)

             Rectangle {
                 id: statusLine
                 height: parent.height
                 width: parent.width * UAV.progress
                 color: Material.color(Material.LightGreen)

             }
         }
    }
}
