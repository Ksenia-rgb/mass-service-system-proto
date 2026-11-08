import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

import mss
import styles

Page
{
  required property PDConfigControllerType config
  required property string headerStr
  required property string cntStr
  required property string timeStr
  required property string rateStr
  required property string distLawStr

  required property bool pushEnabledPD
  required property bool popEnabledPD
  signal pushPD()
  signal popPD()

  padding: MssTheme.pageMarging

  header: MssHeader
  {
    text: headerStr
  }

  GridLayout
  {
    anchors.fill: parent
    rows: 9
    columns: 2
    rowSpacing: 10
    columnSpacing: 10

    MssLabeledIntField
    {
      id: inputCntMin

      Layout.row: 0
      Layout.column: 0
      minValue: MssTheme.minMinCnt
      maxValue: config.cntMax
      defaultValue: config.cntMin
      label: cntStr + ": min"
      onInput: (val) => config.cntMin = val
    }

    MssLabeledIntField
    {
      id: inputCntMax

      Layout.row: 1
      Layout.column: 0
      minValue: config.cntMin
      maxValue: MssTheme.maxMaxCnt
      defaultValue: config.cntMax
      label: cntStr + ": max"
      onInput: (val) => config.cntMax = val
    }

    MssLabeledIntField
    {
      id: inputCnt

      Layout.row: 2
      Layout.column: 0
      minValue: config.cntMin
      maxValue: config.cntMax
      defaultValue: config.cnt
      label: cntStr
      onInput: (val) => config.cnt = val
    }

    MssLabeledDoubleField
    {
      id: inputTimeMin

      Layout.row: 3
      Layout.column: 0
      minValue: MssTheme.minMinTime
      maxValue: config.timeMax
      defaultValue: config.timeMin
      label: timeStr + ": min"
      onInput: (val) => config.timeMin = val
    }

    MssLabeledDoubleField
    {
      id: inputTimeMax

      Layout.row: 4
      Layout.column: 0
      minValue: config.timeMin
      maxValue: MssTheme.maxMaxTime
      defaultValue: config.timeMax
      label: timeStr + ": max"
      onInput: (val) => config.timeMax = val
    }

    MssLabeledDoubleField
    {
      id: inputRate

      Layout.row: 5
      Layout.column: 0
      minValue: MssTheme.minRate
      maxValue: MssTheme.maxRate
      defaultValue: config.rate
      label: rateStr
      onInput: (val) => config.rate = val
    }

    ColumnLayout
    {
      Layout.row: 6
      Layout.column: 0
      spacing: 0

      Label
      {
        text: distLawStr
      }
      ButtonGroup
      {
        id: distGroup
        exclusive: true
      }
      MssRadioButton
      {
        id: expRadio

        name: "Exponential"
        isChecked: config.distLaw
        ButtonGroup.group: distGroup
        onInput: (val) => config.distLaw = val
      }
      MssRadioButton
      {
        id: uniformRadio

        name: "Uniform"
        isChecked: !config.distLaw
        ButtonGroup.group: distGroup
        onInput: (val) => config.distLaw = !val
      }
    }

    MssConfigText
    {
      id: configView

      Layout.row: 0
      Layout.column: 1
      Layout.rowSpan: 7
      Layout.preferredWidth: parent.width * 0.5
      Layout.fillHeight: true

      text: "Count min: " + config.cntMin + "<br><br>"
        + "Count max: " + config.cntMax + "<br><br>"
        + "<b>Count: " + config.cnt + "</b><br><br>"
        + "Time min: " + config.timeMin + "<br><br>"
        + "Time max: " + config.timeMax + "<br><br>"
        + "Rate: " + config.rate + "<br><br>"
        + "<b>Distribution law: " + (config.distLaw ? "Exponential" : "Uniform") + "</b>"
    }

    Item
    {
      Layout.row: 7
      Layout.column: 0
      Layout.columnSpan: 2
      Layout.fillHeight: true
    }

    MssPassFooter
    {
      Layout.row: 8
      Layout.column: 0
      Layout.columnSpan: 2
      pushEnabled: pushEnabledPD
      popEnabled: popEnabledPD
      onPush: pushPD()
      onPop: popPD()
    }
  }
}
