import QtQuick 2.10
import QtQuick.Controls 2.15
import Base 1.0

Item {
    id: _rootRectangle

    width: parent.width
    height: parent.height*0.2

    Grid {
        id: _grid
        anchors.fill: parent

        padding: 5

        rows: 3
        columns: 2

        horizontalItemAlignment: Grid.AlignHCenter
        verticalItemAlignment: Grid.AlignVCenter

        spacing: 5

        BaseControlButton {
            id: _btnLoops
            displayText: "Loop"
        }

        BaseControlButton {
            id: _btnTimer
            displayText: "00s"
        }

        BaseControlButton {
            id: _btnTempo
            isWide: true
            displayText: "120"
        }

        BaseControlButton {
            id: _btnPlayStop
            isWide: true
            displayText: "PLAY"
        }

        BaseControlButton {

            displayText: "+|-"
        }

        BaseControlButton {
            id: _btnMixer
            displayText: "Mixer"
        }
    }
}
