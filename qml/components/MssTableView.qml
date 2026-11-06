import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

ColumnLayout
{
  required property QtObject modelObject
  required property string modelLabel

  Label
  {
    padding: 0
    text: modelLabel
  }

  HorizontalHeaderView
  {
    syncView: tableView
    Layout.fillWidth: true
    clip: true
  }

  TableView
  {
    id: tableView

    Layout.fillWidth: true
    Layout.fillHeight: true
    clip: true

    model: modelObject

    delegate: Rectangle
    {
      required property int row
      required property int column
      required property string display

      implicitHeight: textItem.implicitHeight + 10
      implicitWidth: 100

      color: (row % 2 === 0) ? "#fafafa" : "transparent"
      border.color: "#eee"
      border.width: 1

      Text
      {
        id: textItem

        anchors.fill: parent
        anchors.margins: 4
        text: parent.display
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
      }
    }
  }
}
