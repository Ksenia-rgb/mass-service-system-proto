import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

import Mss
import "../components"

Page
{
  required property bool pushEnabledBuffer
  required property bool popEnabledBuffer
  signal pushBuffer()
  signal popBuffer()

  header: Label
  {
    id: header
    text: "Buffer configuration"
    font.pixelSize: 16
    font.bold: true
    leftPadding: 10
    topPadding: 5
    bottomPadding: 5
  }

  GridLayout
  {
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top
    rows: 3
    columns: 4
    rowSpacing: 10
    columnSpacing: 10

    BufferConfigControllerType
    {
      id: config
    }

    MssLabeledIntField
    {
      id: inputCapMin

      Layout.row: 0
      minValue: 1
      maxValue: config.capMax
      defaultValue: config.capMin
      label: "Enter buffer capacity: min"
      onInput: (val) => config.capMin = val
    }

    MssLabeledIntField
    {
      id: inputCapMax

      Layout.row: 1
      minValue: config.capMin
      maxValue: 100000
      defaultValue: config.capMax
      label: "Enter buffer capacity"
      onInput: (val) => config.capMax = val
    }

    MssLabeledIntField
    {
      id: inputCap

      Layout.row: 2
      minValue: config.capMin
      maxValue: config.capMax
      defaultValue: config.cap
      label: "Enter buffer capacity"
      onInput: (val) => config.cap = val
    }

    TextArea
    {
      id: configView

      Layout.row: 0
      Layout.column: 2
      Layout.rowSpan: 4
      Layout.columnSpan: 2

      Layout.preferredWidth: parent.width * 0.5
      Layout.fillHeight: true
      Layout.rightMargin: 10
      Layout.topMargin: 10
      Layout.bottomMargin: 10

      readOnly: true
      selectByMouse: true
      wrapMode: TextEdit.Wrap
      textFormat: TextEdit.PlainText

      background: Rectangle
      {
        color: "transparent"
        border.color: "#888"
        border.width: 1
      }

      text: "Capacity min: " + config.capMin + "\n\n"
        + "Capacity max: " + config.capMax + "\n\n"
        + "Capacity: " + config.cap
    }
  }

  footer: RowLayout
  {
    Button
    {
      text: "<-"
      font.pixelSize: 20
      padding: 4
      Layout.preferredWidth: 40

      enabled: popEnabledBuffer
      onPressed: popBuffer()
    }
    Item
    {
      Layout.fillWidth: true
    }
    Button
    {
      text: "->"
      font.pixelSize: 20
      padding: 4
      Layout.preferredWidth: 40

      enabled: pushEnabledBuffer
      onPressed: pushBuffer()
    }
  }
}
