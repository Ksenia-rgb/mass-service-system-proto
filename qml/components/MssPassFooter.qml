import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

RowLayout
{
  required property bool pushEnabled
  required property bool popEnabled
  signal push()
  signal pop()

  Button
  {
    text: "<-"
    font.pixelSize: 20
    padding: 4
    Layout.preferredWidth: 50

    enabled: popEnabled
    onClicked: pop()
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
    onClicked: push()
  }
}
