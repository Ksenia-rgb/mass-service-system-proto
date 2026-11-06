import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

ColumnLayout
{
  required property string label
  required property int minValue
  required property int maxValue
  required property int defaultValue
  property int frozenDefaultValue

  signal input(int val)

  Component.onCompleted:
  {
    frozenDefaultValue = defaultValue
  }

  Layout.column: 0
  Layout.columnSpan: 2
  spacing: 4

  Label
  {
    text: label
    Layout.fillWidth: true
    wrapMode: Text.WordWrap
  }

  TextField
  {
    id: textField

    Layout.fillWidth: true
    Layout.preferredHeight: 30

    text: String(defaultValue)
    placeholderText: String(frozenDefaultValue)

    validator: IntValidator
    {
      bottom: minValue
      top: maxValue
      locale: "C"
    }

    background: Rectangle
    {
      border.width: 1
      border.color:
      {
        return (textField.acceptableInput && textField.text.length !== 0) ? "#888" : "red"
      }
    }

    onEditingFinished:
    {
      if (acceptableInput)
      {
        input(parseInt(text))
      }
    }
  }
}
