import QtQuick
import QtQuick.Controls.Basic

RadioButton
{
  id: root

  required property string name
  required property bool isChecked

  signal input(bool val)

  text: name
  checked: isChecked
  padding: 2

  indicator: Rectangle
  {
    implicitWidth: 16
    implicitHeight: 16
    x: leftPadding
    y: height / 2 - height / 2
    radius: width / 2
    border.color: checked ? "#000000" : "#888888"

    Rectangle
    {
      width: 8
      height: 8
      x: (parent.width - width) / 2
      y: (parent.height - height) / 2
      radius: width / 2
      color: "#000000"
      visible: checked
    }
  }

  onToggled:
  {
    if (checked)
    {
      input(checked)
    }
  }
}
