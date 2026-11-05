import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

import Mss

Page
{
  required property PDConfigControllerType config
  required property string headerStr
  required property string cntStr
  required property string timeStr
  required property string rateStr
  required property string distLawStr

  required property bool pushEnabled
  required property bool popEnabled
  signal push()
  signal pop()

  header: Text
  {
    id: header

    text: headerStr
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
    rows: 9
    columns: 4
    rowSpacing: 10
    columnSpacing: 10

    MssLabeledIntField
    {
      id: inputCntMin

      Layout.row: 0
      minValue: 1
      maxValue: config.cntMax
      defaultValue: config.cntMin
      label: cntStr + ": min"
      onInput: (val) => config.cntMin = val
    }

    MssLabeledIntField
    {
      id: inputCntMax

      Layout.row: 1
      minValue: config.cntMin
      maxValue: 100000
      defaultValue: config.cntMax
      label: cntStr + ": max"
      onInput: (val) => config.cntMax = val
    }

    MssLabeledIntField
    {
      id: inputCnt

      Layout.row: 2
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
      minValue: 1.000
      maxValue: config.timeMax
      defaultValue: config.timeMin
      label: timeStr + ": min"
      onInput: (val) => config.timeMin = val
    }

    MssLabeledDoubleField
    {
      id: inputTimeMax

      Layout.row: 4
      minValue: config.timeMin
      maxValue: 100000.000
      defaultValue: config.timeMax
      label: timeStr + ": max"
      onInput: (val) => config.timeMax = val
    }

    MssLabeledDoubleField
    {
      id: inputRate

      Layout.row: 5
      minValue: 1.000
      maxValue: 100000.000
      defaultValue: config.rate
      label: rateStr
      onInput: (val) => config.rate = val
    }

    ColumnLayout
    {
      Layout.row: 6
      Layout.column: 0
      Layout.columnSpan: 2
      Layout.leftMargin: 10
      Layout.bottomMargin: 10
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

    TextArea
    {
      id: configView

      Layout.row: 0
      Layout.column: 2
      Layout.rowSpan: 9
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

      text: "Count min: " + config.cntMin + "\n\n"
        + "Count max: " + config.cntMax + "\n\n"
        + "Count: " + config.cnt + "\n\n"
        + "Time min: " + config.timeMin + "\n\n"
        + "Time max: " + config.timeMax + "\n\n"
        + "Rate: " + config.rate + "\n\n"
        + "Distribution law: " + (config.distLaw ? "Exponential" : "Uniform")
    }
  }

  footer: RowLayout
  {
    Button
    {
      text: "<-"
      font.pixelSize: 20
      padding: 4
      Layout.preferredWidth: 50

      enabled: popEnabled
      onPressed: pop()
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
      Layout.preferredWidth: 50

      enabled: pushEnabled
      onPressed: push()
    }
  }
}
