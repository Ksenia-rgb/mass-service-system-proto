import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

import mss
import styles
import components

Page
{
  property QtObject config: BufferConfigController
  required property bool pushEnabledBuffer
  required property bool popEnabledBuffer
  signal pushBuffer()
  signal popBuffer()

  padding: MssTheme.pageMargin

  header: MssHeader
  {
    text: "Buffer configuration"
  }

  GridLayout
  {
    anchors.fill: parent
    rows: 5
    columns: 2
    rowSpacing: 10
    columnSpacing: 10

    MssLabeledIntField
    {
      id: inputCapMin

      Layout.row: 0
      Layout.column: 0
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
      Layout.column: 0
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
      Layout.column: 0
      minValue: config.capMin
      maxValue: config.capMax
      defaultValue: config.cap
      label: "Enter buffer capacity"
      onInput: (val) => config.cap = val
    }

    MssConfigText
    {
      id: configView

      Layout.row: 0
      Layout.column: 1
      Layout.rowSpan: 3
      Layout.preferredWidth: parent.width * 0.5
      Layout.fillHeight: true

      text: "Capacity min: " + config.capMin + "<br><br>"
        + "Capacity max: " + config.capMax + "<br><br>"
        + "<b>Capacity: " + config.cap + "</b>"
    }

    Item
    {
      Layout.row: 3
      Layout.column: 0
      Layout.columnSpan: 2
      Layout.fillHeight: true
    }

    MssPassFooter
    {
      Layout.row: 4
      Layout.column: 0
      Layout.columnSpan: 2
      pushEnabled: pushEnabledBuffer
      popEnabled: popEnabledBuffer
      onPush: pushBuffer()
      onPop: popBuffer()
    }
  }
}
