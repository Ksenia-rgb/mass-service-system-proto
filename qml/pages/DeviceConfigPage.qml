import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

import mss
import components

MssPDConfigPage
{
  required property bool pushEnabledDevice
  required property bool popEnabledDevice
  signal pushDevice()
  signal popDevice()

  config: DeviceConfigController
  headerStr: "Device configuration"
  cntStr: "Enter devices count"
  timeStr: "Enter service bid time"
  rateStr: "Enter rate of service (bids per hour)"
  distLawStr: "Select distribution law for service bid time"

  pushEnabledPD: pushEnabledDevice
  popEnabledPD: popEnabledDevice
  onPushPD: pushDevice()
  onPopPD: popDevice()
}
