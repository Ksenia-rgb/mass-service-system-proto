import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import mss
import pages

Window
{
  property QtObject systemController: SystemController

  width: 600
  height: 550
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
        onYes:
        {
          systemController.prepareSystemStepController();
          stack.push(systemStepPage);
        }
        onNo: stack.pop()
      }
    }

    Component
    {
      id: systemStepPage
      SystemStepPage
      {
        onGoAuto:
        {
          systemController.prepareSystemAutoController();
          stack.push(systemAutoPage);
        }
      }
    }

    Component
    {
      id: systemAutoPage
      SystemAutoPage{}
    }
  }
}
