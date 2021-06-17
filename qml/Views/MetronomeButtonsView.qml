import QtQuick 2.10
import QtQuick.Controls 2.15

import Base 1.0
import StyleSettings 1.0

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

        BaseSpinBox{
            from: 10
            to: 300
            value: Metronome.tempo()

            onValueChanged: {
                Metronome.tempoChanged(value)
            }
        }

        BaseControlButton {
            id: _btnPlayStop
            isWide: true

            contentItem: Text{
                id: _btnPlayStopText

                //  todo: Заменить на картинку!!! >
                font.pointSize: 25

                text: Metronome.isMetronomePlaying ? "STOP" : "PLAY"

                color: _btnPlayStop.down ? Style.textColorPressed
                                         : Style.textColorMain

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            onClicked: {
                Metronome.playStopButtonClick()

            }
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
