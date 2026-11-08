import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

import mss
import styles
import components
import charts

Page
{
  property QtObject systemAutoController: SystemAutoController

  id: root

  padding: MssTheme.pageMarging

  header: MssHeader
  {
    text: "System auto results"
  }

  GridLayout
  {
    anchors.fill: parent
    rows: 3
    columns: 3
    rowSpacing: 10
    columnSpacing: 10

    CustomPlotItemType
    {
      id: plotProducerCntRejectProb

      Layout.row: 0
      Layout.column: 0
      Layout.fillWidth: true
      Layout.fillHeight: true

      title: "Producer count: reject probability"
      xLabel: "Count"
      yLabel: "Value"
      backgroundColor: "transparent"
      axisColor: "#333333"
      gridColor: "#888"
    }

    CustomPlotItemType
    {
      id: plotProducerCntTimeInSystem

      Layout.row: 0
      Layout.column: 1
      Layout.fillWidth: true
      Layout.fillHeight: true

      title: "Producer count: bid time in system"
      xLabel: "Count"
      yLabel: "Value"
      backgroundColor: "transparent"
      axisColor: "#333333"
      gridColor: "#888"
    }

    CustomPlotItemType
    {
      id: plotProducerCntWorkload

      Layout.row: 0
      Layout.column: 2
      Layout.fillWidth: true
      Layout.fillHeight: true

      title: "Producer count: device workload"
      xLabel: "Count"
      yLabel: "Value"
      backgroundColor: "transparent"
      axisColor: "#333333"
      gridColor: "#888"
    }

    CustomPlotItemType
    {
      id: plotDeviceCntRejectProb

      Layout.row: 1
      Layout.column: 0
      Layout.fillWidth: true
      Layout.fillHeight: true

      title: "Device count: reject probability"
      xLabel: "Count"
      yLabel: "Value"
      backgroundColor: "transparent"
      axisColor: "#333333"
      gridColor: "#888"
    }

    CustomPlotItemType
    {
      id: plotDeviceCntTimeInSystem

      Layout.row: 1
      Layout.column: 1
      Layout.fillWidth: true
      Layout.fillHeight: true

      title: "Device count: bid time in system"
      xLabel: "Count"
      yLabel: "Value"
      backgroundColor: "transparent"
      axisColor: "#333333"
      gridColor: "#888"
    }

    CustomPlotItemType
    {
      id: plotDeviceCntWorkload

      Layout.row: 1
      Layout.column: 2
      Layout.fillWidth: true
      Layout.fillHeight: true

      title: "Device count: device workload"
      xLabel: "Count"
      yLabel: "Value"
      backgroundColor: "transparent"
      axisColor: "#333333"
      gridColor: "#888"
    }

    CustomPlotItemType
    {
      id: plotBufferCapRejectProb

      Layout.row: 2
      Layout.column: 0
      Layout.fillWidth: true
      Layout.fillHeight: true

      title: "Buffer capacity: reject probability"
      xLabel: "Capacity"
      yLabel: "Value"
      backgroundColor: "transparent"
      axisColor: "#333333"
      gridColor: "#888"
    }

    CustomPlotItemType
    {
      id: plotBufferCapTimeInSystem

      Layout.row: 2
      Layout.column: 1
      Layout.fillWidth: true
      Layout.fillHeight: true

      title: "Buffer capacity: bid time in system"
      xLabel: "Capacity"
      yLabel: "Value"
      backgroundColor: "transparent"
      axisColor: "#333333"
      gridColor: "#888"
    }

    CustomPlotItemType
    {
      id: plotBufferCapWorkload

      Layout.row: 2
      Layout.column: 2
      Layout.fillWidth: true
      Layout.fillHeight: true

      title: "Buffer capacity: device workload"
      xLabel: "Capacity"
      yLabel: "Value"
      backgroundColor: "transparent"
      axisColor: "#333333"
      gridColor: "#888"
    }
  }

  Component.onCompleted:
  {
    plotProducerCntRejectProb.addSeries("Reject prob", "#1A1EB2")
    plotProducerCntTimeInSystem.addSeries("Bid time in system", "#1A1EB2")
    plotProducerCntWorkload.addSeries("Device workload", "#1A1EB2")

    plotDeviceCntRejectProb.addSeries("Reject prob", "#1A1EB2")
    plotDeviceCntTimeInSystem.addSeries("Bid time in system", "#1A1EB2")
    plotDeviceCntWorkload.addSeries("Device workload", "#1A1EB2")

    plotBufferCapRejectProb.addSeries("Reject prob", "#1A1EB2")
    plotBufferCapTimeInSystem.addSeries("Bid time in system", "#1A1EB2")
    plotBufferCapWorkload.addSeries("Device workload", "#1A1EB2")
  }

  Connections
  {
    target: systemAutoController.producerCntModel
    function onModelReset()
    {
      plotProducerCntRejectProb.setDataFromModel(0, systemAutoController.producerCntModel, 0, 1)
      plotProducerCntRejectProb.rescaleAxes()
      plotProducerCntRejectProb.replot()

      plotProducerCntTimeInSystem.setDataFromModel(0, systemAutoController.producerCntModel, 0, 2)
      plotProducerCntTimeInSystem.rescaleAxes()
      plotProducerCntTimeInSystem.replot()

      plotProducerCntWorkload.setDataFromModel(0, systemAutoController.producerCntModel, 0, 3)
      plotProducerCntWorkload.rescaleAxes()
      plotProducerCntWorkload.replot()
    }
  }

  Connections
  {
    target: systemAutoController.deviceCntModel
    function onModelReset()
    {
      plotDeviceCntRejectProb.setDataFromModel(0, systemAutoController.deviceCntModel, 0, 1)
      plotDeviceCntRejectProb.rescaleAxes()
      plotDeviceCntRejectProb.replot()

      plotDeviceCntTimeInSystem.setDataFromModel(0, systemAutoController.deviceCntModel, 0, 2)
      plotDeviceCntTimeInSystem.rescaleAxes()
      plotDeviceCntTimeInSystem.replot()

      plotDeviceCntWorkload.setDataFromModel(0, systemAutoController.deviceCntModel, 0, 3)
      plotDeviceCntWorkload.rescaleAxes()
      plotDeviceCntWorkload.replot()
    }
  }

  Connections
  {
    target: systemAutoController.bufferCapModel
    function onModelReset()
    {
      plotBufferCapRejectProb.setDataFromModel(0, systemAutoController.bufferCapModel, 0, 1)
      plotBufferCapRejectProb.rescaleAxes()
      plotBufferCapRejectProb.replot()

      plotBufferCapTimeInSystem.setDataFromModel(0, systemAutoController.bufferCapModel, 0, 2)
      plotBufferCapTimeInSystem.rescaleAxes()
      plotBufferCapTimeInSystem.replot()

      plotBufferCapWorkload.setDataFromModel(0, systemAutoController.bufferCapModel, 0, 3)
      plotBufferCapWorkload.rescaleAxes()
      plotBufferCapWorkload.replot()
    }
  }
}
