import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1
import "properties.js" as Styles

import com.ComDeviceWorker.rf 1.0

Rectangle {
    id:  root
    color: "transparent"
    objectName: "root"

    implicitWidth: rootCol.implicitWidth

    property bool isConnectControlsEnabled: true

    property int fontSize: Styles.labelFontSize

    property var comPortsModel
    property var baudRatesModel: ["9600", "115200", "230400", "460800", "921600"]

    signal scanPortsRequested()
    signal deviceIdentificationRequested()
    signal startStreamRequested()

    function switchState(enabled){
        isConnectControlsEnabled = enabled
        streamButton.enabled = enabled
    }

    function connectedButtonState(connected){
//        streamButton.enabled = true
        if(connected)
        {
            streamButton.enabled = true
            streamButton.text = qsTr("Stop stream")
        }
        else
            streamButton.text = qsTr("StartStream")
    }

    function scanPorts()
    {
        comDevWorker.FindActiveComPorts();
        comPortsModel = comDevWorker.ComPorts;
        streamButton.enabled = comBox.count > 0
    }

//    Component.onCompleted: scanPorts()

    ComDeviceWorker{
        id: comDevWorker
    }

    Column{
        id: rootCol
        anchors.fill: parent
        spacing: 6

        GridLayout{
            anchors.right: parent.right
            anchors.left: parent.left
            columnSpacing: 10
            columns: 2

            Button{
                text: qsTr("Scan ports")
                Layout.columnSpan: 2
                Layout.fillWidth: true
//                onClicked: scanPortsRequested()
                onClicked: scanPorts()
                enabled: root.isConnectControlsEnabled
            }

            Text{
                text: qsTr("Com port") + ":"
                font.pointSize: fontSize
            }

            ComboBox{
                id: comBox
                Layout.fillWidth: true
                model: root.comPortsModel
                enabled: root.isConnectControlsEnabled
            }

            Text {
                text: qsTr("Baud rate") + ":"
                font.pointSize: fontSize
            }

            ComboBox{
                id: baudRateBox
                Layout.fillWidth: true
                model: baudRatesModel
                enabled: root.isConnectControlsEnabled
            }

            Text {
                text: qsTr("Period") + ", ms:"
                font.pointSize: fontSize
            }

            TextField{
                id: periodBox
                Layout.fillWidth: true
                enabled: root.isConnectControlsEnabled
            }

            Text {
                text: qsTr("Dump file") + ":"
                font.pointSize: fontSize
            }

            TextField{
                id: dumpFileBox
                Layout.fillWidth: true
                enabled: root.isConnectControlsEnabled
            }

            Button{
                text: qsTr("Device identification")
                Layout.columnSpan: 2
                Layout.fillWidth: true
                onClicked: deviceIdentificationRequested()
                enabled: root.isConnectControlsEnabled
            }

            Button{
                id: streamButton
                text: qsTr("Start stream")
                Layout.columnSpan: 2
                Layout.fillWidth: true
                onClicked: startStreamRequested()
            }
        }
    }
}
