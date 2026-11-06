import QtQuick
import QtQuick.Controls.Basic

TextArea
{
  readOnly: true
  selectByMouse: true
  wrapMode: TextEdit.Wrap
  textFormat: TextEdit.RichText

  background: Rectangle
  {
    color: "transparent"
    border.color: "#888"
    border.width: 1
  }
}
