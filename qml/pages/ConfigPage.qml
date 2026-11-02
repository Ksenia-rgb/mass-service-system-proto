import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import ConfigController

Page
{
  ColumnLayout
  {
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top
    spacing: 10

    TextField
    {
      id: inputProducerCnt
      Layout.preferredHeight: 40
      Layout.fillWidth: true
      Layout.margins: 10

      placeholderText: "Enter producers count"

      onEditingFinished: ConfigController.enterProducerCnt(inputProducerCnt.text)
    }

    TextField
    {
      id: inputDeviceCnt
      Layout.preferredHeight: 40
      Layout.fillWidth: true
      Layout.margins: 10

      placeholderText: "Enter devices count"

      onEditingFinished: ConfigController.enterDeviceCnt(inputDeviceCnt.text)
    }

    TextField
    {
      id: inputBufferCap
      Layout.preferredHeight: 40
      Layout.fillWidth: true
      Layout.margins: 10

      placeholderText: "Enter buffer capacity"

      onEditingFinished: ConfigController.enterBUfferCap(inputBufferCap.text)
    }

    Text
    {
      id: config

      Layout.preferredHeight: 40
      Layout.fillWidth: true
      Layout.margins: 10

      text: "Config:\n"
    }

    Button
    {
      id: printConfig

      Layout.preferredHeight: 40
      Layout.fillWidth: true
      Layout.margins: 10

      text: "Print Config"
      width: 25
      height: 25
      onClicked: config.text = ConfigController.printConfig()
    }
  }
}
