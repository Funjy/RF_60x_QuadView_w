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

    property bool isComParametersEnabled: true
    property bool isStreamParametersEnabled: true
    property bool isConnectButtonEnabled: true

    property int fontSize: Styles.labelFontSize

    property var comPortsModel
    property var baudRatesModel: ["9600", "115200", "230400", "460800", "921600"]

    signal beforeScanPortsRequested()
    signal scanPortsRequested()
    signal deviceIdentificationRequested()
    signal streamButtonClicked()
    signal imLoaded()

    function setConnectButtonEnabled(en)
    {
        identificationButton.enabled = en
    }

    function setConnectButtonState(connected)
    {
        if(connected)
        {
            identificationButton.text = qsTr("Disconnect")
            isComParametersEnabled = false
        }
        else
        {
            identificationButton.text = qsTr("Device identification")
            isComParametersEnabled = true
        }
    }

    function setStreamButtonEnabled(en)
    {
        streamButton.enabled = en
    }

    function switchState(enabled){
        isStreamParametersEnabled = enabled
        isConnectButtonEnabled = enabled
        streamButton.enabled = enabled
    }

    function setStreamButtonState(connected){
//        streamButton.enabled = true
        if(connected)
        {
            streamButton.enabled = true
            streamButton.text = qsTr("Stop stream")
            isStreamParametersEnabled = false
        }
        else
        {
            streamButton.text = qsTr("Start Stream")
            isStreamParametersEnabled = true
        }
    }

    function scanPorts()
    {
        beforeScanPortsRequested();
        comDevWorker.findActiveComPorts();
        comPortsModel = comDevWorker.ComPorts;
        scanPortsRequested();
    }

    function getConnectParameters()
    {
        return new Array(comBox.currentText.toString(), baudRateBox.currentText.toString(), periodBox.text.toString(), dumpFileBox.text.toString());
    }

    function setConnectParameters(params)
    {
        var bri = baudRateBox.find(params[1])
        if(bri !== -1)
            baudRateBox.currentIndex(bri)
        periodBox.text = params[2]
        dumpFileBox.text = params[3]
    }

//    Component.onCompleted: scanPorts()

    Component.onCompleted: {
        isConnectButtonEnabled = false;
        streamButton.enabled = false;
    }    

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
                enabled: root.isComParametersEnabled
            }

            Text{
                text: qsTr("Com port") + ":"
                font.pointSize: fontSize
            }

            ComboBox{
                id: comBox
                Layout.fillWidth: true
                model: root.comPortsModel
                enabled: root.isComParametersEnabled
                onCurrentTextChanged: {
                    identificationButton.enabled = !(currentText === "" || currentText === "Not found");
                }
            }

            Text {
                text: qsTr("Baud rate") + ":"
                font.pointSize: fontSize
            }

            ComboBox{
                id: baudRateBox
                Layout.fillWidth: true
                model: baudRatesModel
                enabled: root.isComParametersEnabled
                Component.onCompleted: {
                    imLoaded()
                }
            }

            Text {
                text: qsTr("Period") + ", ms:"
                font.pointSize: fontSize
            }

            TextField{
                id: periodBox
                Layout.fillWidth: true
                enabled: root.isStreamParametersEnabled
            }

            Text {
                text: qsTr("Dump file") + ":"
                font.pointSize: fontSize
            }

            TextField{
                id: dumpFileBox
                Layout.fillWidth: true
                enabled: root.isStreamParametersEnabled
            }

            Button{
                id: identificationButton
                text: qsTr("Device identification")
                Layout.columnSpan: 2
                Layout.fillWidth: true
                onClicked: deviceIdentificationRequested()
                enabled: root.isConnectButtonEnabled
            }

            Button{
                id: streamButton
                text: qsTr("Start stream")
                Layout.columnSpan: 2
                Layout.fillWidth: true
                onClicked: streamButtonClicked()
            }
        }
    }
}
