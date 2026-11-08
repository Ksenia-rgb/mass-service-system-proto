import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

import mss
import components

MssPDConfigPage
{
  required property bool pushEnabledProducer
  required property bool popEnabledProducer
  signal pushProducer()
  signal popProducer()

  config: ProducerConfigController
  headerStr: "Producer configuration"
  cntStr: "Enter producers count"
  timeStr: "Enter generation bid time"
  rateStr: "Enter rate of generation (bids per hour)"
  distLawStr: "Select distribution law for generation bid time"

  pushEnabledPD: pushEnabledProducer
  popEnabledPD: popEnabledProducer
  onPushPD: pushProducer()
  onPopPD: popProducer()
}
