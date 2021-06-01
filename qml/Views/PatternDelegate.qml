import QtQuick 2.0
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.0
import ResourceProvider 1.0

import MusicalNoteModule 1.0

Item {
    id: root

    opacity:  _delegateArea.pressed ? 0.5                                   : 0.8

    MouseArea{
        id: _delegateArea
        anchors.fill: root
    }

    ColumnLayout{
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
                        case MusicalNote.Quarter : return Resources.musicalSymbols.quarterNoteIcon
                        case MusicalNote.Eight: return Resources.musicalSymbols.eightNoteIcon
                        default: return Resources.musicalSymbols.quarterNoteIcon
                    }
                }
//                sourceSize.height: height
//                sourceSize.width: width
                cache: true
            }

            ColorOverlay{
                anchors.fill: _internalImage
                source: _imageNote.image
                color:  "royalblue"
                antialiasing: true
            }
        }

        Text{
            text: line1
            color: "lightBlue"
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text{
            text: line2
            color: "lightBlue"
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
