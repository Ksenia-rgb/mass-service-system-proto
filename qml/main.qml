import QtQuick
import QtQuick.Controls

import "pages"

Window
{
  width: 600
  height: 500
  visible: true
  title: qsTr("Mass Service System")

  StackView {
    id: stackView
    anchors.fill: parent
    initialItem: "pages/ConfigPage.qml"
  }
}
