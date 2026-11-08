import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

import styles

Page
{
  signal start()

  padding: MssTheme.pageMarging

  ColumnLayout
  {
    anchors.centerIn: parent
    spacing: 20

    Label
    {
      text: "Mass Service System"
      font.pixelSize: 26
      font.bold: true

      Layout.alignment: Qt.AlignHCenter
    }

    Label
    {
      text: "Application for demonstrating\nthe operation of amass service system"
      font.pixelSize: 14
      color: "#666"

      horizontalAlignment: Text.AlignHCenter
      Layout.alignment: Qt.AlignHCenter
    }

    Button
    {
      text: "Start"
      font.pixelSize: 16
      font.bold: true

      Layout.preferredWidth: 140
      Layout.preferredHeight: 40
      Layout.alignment: Qt.AlignHCenter

      background: Rectangle
      {
        color: "transparent"
        border.color: "#888"
        border.width: 1
      }

      onClicked: start()
    }
  }
}
