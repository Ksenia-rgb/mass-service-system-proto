pragma Singleton
import QtQuick

QtObject
{
  readonly property int pageMarging: 15
  readonly property int headerTopPadding: 10

  readonly property int minMinCnt: 1
  readonly property double minMinTime: 1.000
  readonly property double minRate: 1.000
  readonly property int minMinBufferCap: 1

  readonly property int maxMaxCnt: 100000
  readonly property double maxMaxTime: 100000.000
  readonly property double maxRate: 100000.000
  readonly property int maxMaxBufferCap: 100000
}
