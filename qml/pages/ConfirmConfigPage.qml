import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

import mss
import styles
import components

Page
{
  property QtObject producerConfig: ProducerConfigController
  property QtObject deviceConfig: DeviceConfigController
  property QtObject bufferConfig: BufferConfigController

  signal no()
  signal yes()

  padding: MssTheme.pageMargin

  GridLayout
  {
    anchors.fill: parent

    rows: 2
    columns: 3
    rowSpacing: 10
    columnSpacing: 10

    MssConfigText
    {
      id: producerConfigConfirm

      Layout.row: 0
      Layout.column: 0
      Layout.preferredWidth: 1
      Layout.fillWidth: true
      Layout.fillHeight: true

      text: "<b>Producer config:</b><br><br><br>"
        + "Count min: " + producerConfig.cntMin + "<br><br>"
        + "Count max: " + producerConfig.cntMax + "<br><br>"
        + "Count: " + producerConfig.cnt + "<br><br>"
        + "Time min: " + producerConfig.timeMin + "<br><br>"
        + "Time max: " + producerConfig.timeMax + "<br><br>"
        + "Rate: " + producerConfig.rate + "<br><br>"
        + "Distribution law: " + (producerConfig.distLaw ? "Exponential" : "Uniform")
    }

    MssConfigText
    {
      id: deviceConfigConfirm

      Layout.row: 0
      Layout.column: 1
      Layout.preferredWidth: 1
      Layout.fillWidth: true
      Layout.fillHeight: true

      text: "<b>Device config:</b><br><br><br>"
        + "Count min: " + deviceConfig.cntMin + "<br><br>"
        + "Count max: " + deviceConfig.cntMax + "<br><br>"
        + "Count: " + deviceConfig.cnt + "<br><br>"
        + "Time min: " + deviceConfig.timeMin + "<br><br>"
        + "Time max: " + deviceConfig.timeMax + "<br><br>"
        + "Rate: " + deviceConfig.rate + "<br><br>"
        + "Distribution law: " + (deviceConfig.distLaw ? "Exponential" : "Uniform")
    }

    MssConfigText
    {
      id: bufferConfigConfirm

      Layout.row: 0
      Layout.column: 2
      Layout.preferredWidth: 1
      Layout.fillWidth: true
      Layout.fillHeight: true

      text: "<b>Buffer config:</b><br><br><br>"
        + "Capacity min: " + bufferConfig.capMin + "<br><br>"
        + "Capacity max: " + bufferConfig.capMax + "<br><br>"
        + "Capacity: " + bufferConfig.cap
    }

    RowLayout
    {
      Layout.row: 1
      Layout.column: 0
      Layout.columnSpan: 3

      Layout.fillWidth: true
      Layout.fillHeight: true

      Button
      {
        id: noButton

        text: "No. Back"

        background: Rectangle
        {
          color: "transparent"
          border.color: "#888"
          border.width: 1
        }

        onClicked: no()
      }

      TextArea
      {
        Layout.fillWidth: true

        text: "Are you want to go to modeling system with this configuration?"
        font.bold: true
        horizontalAlignment: "AlignHCenter"
      }

      Button
      {
        id: yesButton

        text: "Yes. Go"

        background: Rectangle
        {
          color: "transparent"
          border.color: "#888"
          border.width: 1
        }

        onClicked: yes()
      }
    }
  }

}
