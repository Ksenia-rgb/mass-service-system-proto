import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

ColumnLayout
{
  required property string label
  required property double minValue
  required property double maxValue
  required property double defaultValue
  property double frozenDefaultValue

  signal input(double val)

  Layout.column: 0
  Layout.columnSpan: 2
  Layout.leftMargin: 10
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

    validator: DoubleValidator
    {
      bottom: minValue
      top: maxValue
      decimals: 3
      notation: DoubleValidator.StandardNotation
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
        input(parseFloat(text))
      }
    }
  }
}
