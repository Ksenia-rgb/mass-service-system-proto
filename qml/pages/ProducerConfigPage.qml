import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

import ProducerConfigController

Page
{
  GridLayout
  {
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top
    rows: 9
    columns: 4
    rowSpacing: 10
    columnSpacing: 10

    ProducerConfigController
    {
      id: config
    }

    TextField
    {
      id: inputCntMin

      Layout.row: 1
      Layout.column: 0
      Layout.columnSpan: 2

      Layout.preferredHeight: 40
      Layout.fillWidth: true
      Layout.leftMargin: 10

      text: config.cntMin
      placeholderText: "Enter producers min count"

      validator: IntValidator
      {
        bottom: 1
        top: 100000
        locale: "C"
      }

      background: Rectangle
      {
        border.width: 1
        border.color:
        {
          if (inputCntMin.text.length === 0)
          {
            return "#888"
          }
          return inputCntMin.acceptableInput ? "#888" : "red"
        }
      }

      onEditingFinished:
      {
        if (inputCntMin.acceptableInput)
        {
          config.cntMin = parseInt(inputCntMin.text)
        }
      }
    }

    TextField
    {
      id: inputCntMax

      Layout.row: 0
      Layout.column: 0
      Layout.columnSpan: 2

      Layout.preferredHeight: 40
      Layout.fillWidth: true
      Layout.leftMargin: 10
      Layout.topMargin: 10

      text: config.cntMax
      placeholderText: "Enter producers max count"

      validator: IntValidator
      {
        bottom: 1
        top: 100000
        locale: "C"
      }

      background: Rectangle
      {
        border.width: 1
        border.color:
        {
          if (inputCntMax.text.length === 0)
          {
            return "#888"
          }
          return inputCntMax.acceptableInput ? "#888" : "red"
        }
      }

      onEditingFinished:
      {
        if (inputCntMax.acceptableInput)
        {
          config.cntMax = parseInt(inputCntMax.text)
        }
      }
    }

    TextField
    {
      id: inputCnt

      Layout.row: 2
      Layout.column: 0
      Layout.columnSpan: 2

      Layout.preferredHeight: 40
      Layout.fillWidth: true
      Layout.leftMargin: 10

      text: config.cnt
      placeholderText: "Enter producers count"

      validator: IntValidator
      {
        bottom: 1
        top: 100000
        locale: "C"
      }

      background: Rectangle
      {
        border.width: 1
        border.color:
        {
          if (inputCnt.text.length === 0)
          {
            return "#888"
          }
          return inputCnt.acceptableInput ? "#888" : "red"
        }
      }

      onEditingFinished:
      {
        if (inputCnt.acceptableInput)
        {
          config.cnt = parseInt(inputCnt.text)
        }
      }
    }

    TextField
    {
      id: inputTimeMin

      Layout.row: 4
      Layout.column: 0
      Layout.columnSpan: 2

      Layout.preferredHeight: 40
      Layout.fillWidth: true
      Layout.leftMargin: 10

      text: config.timeMin
      placeholderText: "Enter generation bid min time"

      validator: DoubleValidator
      {
        bottom: 0.0
        top: 1000.0
        decimals: 3
        notation: DoubleValidator.StandardNotation
        locale: "C"
      }

      background: Rectangle
      {
        border.width: 1
        border.color:
        {
          if (inputTimeMin.text.length === 0)
          {
            return "#888"
          }
          return inputTimeMin.acceptableInput ? "#888" : "red"
        }
      }

      onEditingFinished:
      {
        if (inputTimeMin.acceptableInput)
        {
          config.timeMin = parseFloat(inputTimeMin.text)
        }
      }
    }

    TextField
    {
      id: inputTimeMax

      Layout.row: 3
      Layout.column: 0
      Layout.columnSpan: 2

      Layout.preferredHeight: 40
      Layout.fillWidth: true
      Layout.leftMargin: 10

      text: config.timeMax
      placeholderText: "Enter generation bid max time"

      validator: DoubleValidator
      {
        bottom: 0.0
        top: 1000.0
        decimals: 3
        notation: DoubleValidator.StandardNotation
        locale: "C"
      }

      background: Rectangle
      {
        border.width: 1
        border.color:
        {
          if (inputTimeMax.text.length === 0)
          {
            return "#888"
          }
          return inputTimeMax.acceptableInput ? "#888" : "red"
        }
      }

      onEditingFinished:
      {
        if (inputTimeMax.acceptableInput)
        {
          config.timeMax = parseFloat(inputTimeMax.text)
        }
      }
    }

    TextField
    {
      id: inputRate

      Layout.row: 5
      Layout.column: 0
      Layout.columnSpan: 2

      Layout.preferredHeight: 40
      Layout.fillWidth: true
      Layout.leftMargin: 10

      text: config.rate
      placeholderText: "Enter rate of producers in bids per hour"

      validator: DoubleValidator
      {
        bottom: 0.0
        top: 1000.0
        decimals: 3
        notation: DoubleValidator.StandardNotation
        locale: "C"
      }

      background: Rectangle
      {
        border.width: 1
        border.color:
        {
          if (inputRate.text.length === 0)
          {
            return "#888"
          }
          return inputRate.acceptableInput ? "#888" : "red"
        }
      }

      onEditingFinished:
      {
        if (inputRate.acceptableInput)
        {
          config.rate = parseFloat(inputRate.text)
        }
      }
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
        text: "Select distribution law for generation bid time"
      }
      ButtonGroup
      {
        id: distGroup
        exclusive: true
      }
      RadioButton
      {
        id: expRadio

        text: "Exponential"
        checked: config.distLaw
        padding: 2
        ButtonGroup.group: distGroup

        indicator: Rectangle
        {
          implicitWidth: 16
          implicitHeight: 16
          x: expRadio.leftPadding
          y: expRadio.height / 2 - height / 2
          radius: width / 2
          border.color: expRadio.checked ? "#000000" : "#888888"

          Rectangle
          {
            width: 8
            height: 8
            x: (parent.width - width) / 2
            y: (parent.height - height) / 2
            radius: width / 2
            color: "#000000"
            visible: expRadio.checked
          }
        }

        onToggled:
        {
          if (checked)
          {
            config.distLaw = true
          }
        }
      }
      RadioButton
      {
        id: uniformRadio

        text: "Uniform"
        checked: !config.distLaw
        padding: 2
        ButtonGroup.group: distGroup

        indicator: Rectangle
        {
          implicitWidth: 16
          implicitHeight: 16
          x: uniformRadio.leftPadding
          y: uniformRadio.height / 2 - height / 2
          radius: width / 2
          border.color: uniformRadio.checked ? "#000000" : "#888888"

          Rectangle
          {
            width: 8
            height: 8
            x: (parent.width - width) / 2
            y: (parent.height - height) / 2
            radius: width / 2
            color: "#000000"
            visible: uniformRadio.checked
          }
        }

        onToggled:
        {
          if (checked)
          {
            config.distLaw = false
          }
        }
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

      text: "Config:\n\n"
        + "Count max: " + config.cntMax + "\n\n"
        + "Count min: " + config.cntMin + "\n\n"
        + "Count: " + config.cnt + "\n\n"
        + "Time max: " + config.timeMax + "\n\n"
        + "Time min: " + config.timeMin + "\n\n"
        + "Rate: " + config.rate + "\n\n"
        + "Distribution law: " + (config.distLaw ? "Exponential" : "Uniform")
    }
  }
}
