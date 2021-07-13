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
        padding: 5; spacing: 5

        rows: 3; columns: 2

        horizontalItemAlignment: Grid.AlignHCenter
        verticalItemAlignment: Grid.AlignVCenter


        BaseControlButton {
            displayText: "Loop"
        }

        BaseControlButton {
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

//            Canvas {
//                     id: canvas
//                     x: control.width - width - control.rightPadding
//                     y: control.topPadding + (control.availableHeight - height) / 2
//                     width: 12
//                     height: 8
//                     contextType: "2d"

//                     Connections {
//                         target: control
//                         function onPressedChanged() { canvas.requestPaint(); }
//                     }

//                     onPaint: {
//                         context.reset();
//                         context.moveTo(0, 0);
//                         context.lineTo(width, 0);
//                         context.lineTo(width / 2, height);
//                         context.closePath();
//                         context.fillStyle = control.pressed ? "#17a81a" : "#21be2b";
//                         context.fill();
//                     }
//                 }

            onClicked: {
                Metronome.playStopButtonClick()

            }
        }

        BaseControlButton {
            displayText: "+|-"
        }

        BaseControlButton {
            displayText: "Mixer"
        }
    }
}
