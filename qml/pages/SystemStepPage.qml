import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

import mss
import styles
import components

Page
{
  property QtObject systemStepController: SystemStepController
  property bool isStarted: false
  property bool isFinished: false

  signal goAuto();

  padding: MssTheme.pageMarging

  Component.onCompleted:
  {
    systemStepController.start();
    isStarted = true;
  }

  header: MssHeader
  {
    text: "System step modeling"
  }

  GridLayout
  {
    anchors.fill: parent

    rows: 4
    columns: 2
    rowSpacing: 10
    columnSpacing: 10

    Label
    {
      Layout.row: 0
      Layout.column: 0
      Layout.columnSpan: 2
      padding: 0

      text: "SYSTEM TIME: " + systemStepController.systemTime
    }

    MssTableView
    {
      id: calendarTable
      Layout.row: 1
      Layout.column: 0

      modelLabel: "CALENDAR"
      modelObject: systemStepController.calendarModel
    }

    MssTableView
    {
      id: bufferTable
      Layout.row: 1
      Layout.column: 1

      modelLabel: "BUFFER"
      modelObject: systemStepController.bufferModel
    }

    RowLayout
    {
      Layout.row: 2
      Layout.column: 0
      Layout.columnSpan: 2

      Button
      {
        id: startButton

        text: "Start"
        enabled: !isStarted

        background: Rectangle
        {
          color: "transparent"
          border.color: "#888"
          border.width: 1
        }

        onClicked:
        {
          systemStepController.start();
          isStarted = true;
          isFinished = false;
        }
      }

      Item
      {
        Layout.fillWidth: true
      }

      Button
      {
        id: stepButton

        text: "Step"
        enabled: isStarted

        background: Rectangle
        {
          color: "transparent"
          border.color: "#888"
          border.width: 1
        }

        onClicked: systemStepController.step()
      }

      Item
      {
        Layout.fillWidth: true
      }

      Button
      {
        id: finishButton

        text: "Finish"
        enabled: isStarted && !isFinished

        background: Rectangle
        {
          color: "transparent"
          border.color: "#888"
          border.width: 1
        }

        onClicked:
        {
          systemStepController.finish();
          isStarted = false;
          isFinished = true;
        }
      }
    }

    Button
    {
      id: autoButton

      Layout.row: 3
      Layout.column: 0
      Layout.columnSpan: 2
      Layout.fillWidth: true

      text: "Go to auto results"
      font.bold: true

      background: Rectangle
      {
        color: "transparent"
        border.color: "#888"
        border.width: 1
      }

      onClicked: goAuto()
    }
  }
}
