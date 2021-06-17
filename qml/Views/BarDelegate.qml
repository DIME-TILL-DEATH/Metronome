import QtQuick 2.10
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.0
import ResourceProvider 1.0

import MusicalTypesModule 1.0
import StyleSettings 1.0

Item {
    id: root
    property bool activeNote: (isActiveNote & isActiveBar)

    opacity:  _delegateArea.pressed ? 0.5 : 1

    MouseArea{
        id: _delegateArea
        anchors.fill: root
    }

    ColumnLayout{
        x:5
        y: 30

        spacing: 5

        Rectangle {
            id: _imageNote

            height: root.width
            width: root.width

            property alias image: _internalImage
            color: "transparent"

            Image{
                id: _internalImage
                anchors.fill: _imageNote

                source: {
                    switch(Number(type)){
                        case MusicalTypes.Quarter : return Resources.musicalSymbols.quarterNoteIcon
                        case MusicalTypes.Eight: return Resources.musicalSymbols.eightNoteIcon
                        default: return Resources.musicalSymbols.quarterNoteIcon
                    }
                }
                cache: true
            }

            ColorOverlay{
                id: _overlay
                anchors.fill: _internalImage
                source: _imageNote.image
                color:  (root.activeNote & Metronome.isMetronomePlaying) ? Style.imagesColorOverlayPlaying
                                                                         : Style.imagesColorOverlay
                antialiasing: true


                SequentialAnimation on color{
                    id: _blinkAnim
                    loops: Animation.Infinite
                    running: (root.activeNote & !Metronome.isMetronomePlaying) ? true
                                                                               : false
                    ColorAnimation{
                        from: Style.imagesColorOverlay
                        to: Style.imagesColorOverlayHighlighted
                        duration: 750
                    }
                    ColorAnimation{
                        from: Style.imagesColorOverlayHighlighted
                        to: Style.imagesColorOverlay
                        duration: 750
                    }
                }
            }
        }

        Text{
            text: line1
            color: Style.textColorMain
            horizontalAlignment: Text.AlignHCenter
        }

        Text{
            text: line2
            color: Style.textColorMain
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
