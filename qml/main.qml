import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "pages"

Window
{
  width: 600
  height: 500
  visible: true
  title: qsTr("Mass Service System")

  StackView
  {
    id: stack

    anchors.fill: parent
    focus: true
    initialItem: producerConfigPage

    Component
    {
      id: producerConfigPage
      ProducerConfigPage
      {
        pushEnabledProducer: true
        popEnabledProducer: false
        onPushProducer: stack.push(deviceConfigPage)
        onPopProducer: stack.pop()
      }
    }

    Component
    {
      id: deviceConfigPage
      DeviceConfigPage
      {
        pushEnabledDevice: true
        popEnabledDevice: true
        onPushDevice: stack.push(bufferConfigPage)
        onPopDevice: stack.pop()
      }
    }

    Component
    {
      id: bufferConfigPage
      BufferConfigPage
      {
        pushEnabledBuffer: true
        popEnabledBuffer: true
        onPushBuffer: stack.push(configConfirmPage)
        onPopBuffer: stack.pop()
      }
    }

    Component
    {
      id: configConfirmPage
      ConfirmConfigPage
      {
        onYes: stack.push(configConfirmPage)
        onNo: stack.pop()
      }
    }
  }
}
