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
    rows: 2
    columns: 3
    rowSpacing: 10
    columnSpacing: 10

    CustomPlotItemType
    {
      id: plotProducerCntRejectProb

      Layout.fillWidth: true
      Layout.fillHeight: true

      title: "Producer count: reject probability"
      xLabel: "Time"
      yLabel: "Value"
      backgroundColor: "#ffffff"
      axisColor: "#333333"
      gridColor: "#e0e0e0"
    }

    CustomPlotItemType
    {
      id: plotProducerCntTimeInSystem

      Layout.fillWidth: true
      Layout.fillHeight: true

      title: "Producer count: bid time in system"
      xLabel: "Time"
      yLabel: "Value"
      backgroundColor: "#ffffff"
      axisColor: "#333333"
      gridColor: "#e0e0e0"
    }

    CustomPlotItemType
    {
      id: plotProducerCntWorkload

      Layout.fillWidth: true
      Layout.fillHeight: true

      title: "Producer count: device workload"
      xLabel: "Time"
      yLabel: "Value"
      backgroundColor: "#ffffff"
      axisColor: "#333333"
      gridColor: "#e0e0e0"
    }
  }

  Component.onCompleted:
  {
    plotProducerCntRejectProb.clear()
    plotProducerCntRejectProb.addSeries("Reject prob", "#2196F3")
    plotProducerCntRejectProb.setDataFromModel(0, systemAutoController.producerCntModel, 0, 1)
    plotProducerCntRejectProb.rescaleAxes()
    plotProducerCntRejectProb.replot()

    plotProducerCntTimeInSystem.clear()
    plotProducerCntTimeInSystem.addSeries("Bid time in system", "#2196F3")
    plotProducerCntTimeInSystem.setDataFromModel(0, systemAutoController.producerCntModel, 0, 2)
    plotProducerCntTimeInSystem.rescaleAxes()
    plotProducerCntTimeInSystem.replot()

    plotProducerCntWorkload.clear()
    plotProducerCntWorkload.addSeries("Device workload", "#2196F3")
    plotProducerCntWorkload.setDataFromModel(0, systemAutoController.producerCntModel, 0, 3)
    plotProducerCntWorkload.rescaleAxes()
    plotProducerCntWorkload.replot()
  }
}
