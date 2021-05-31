import QtQuick 2.0
import QtGraphicalEffects 1.0
import ResourceProvider 1.0

import MusicalNoteModule 1.0

Item {
    id: root
 //   color: "black"

    opacity:  _delegateArea.pressed ? 0.5
                                    : 0.8

    MouseArea{
        id: _delegateArea
        anchors.fill: root
    }


    Rectangle {
        id: _imageNote

        height: parent.width
        width: parent.width

        property alias image: _internalImage
        color: "transparent"

        Image{
            id: _internalImage
            anchors.fill: _imageNote

            // If работает, switch нет и даёт предупреждение, мне непонятно почему
            source: {
//                switch(type){
//                    case MusicalNote.Quarter : return Resources.musicalSymbols.quarterNoteIcon
//                    case MusicalNote.Eight: return Resources.musicalSymbols.eightNoteIcon
//                    default: return Resources.musicalSymbols.quarterNoteIcon
//                }

                if(type == MusicalNote.Eight) return Resources.musicalSymbols.quarterNoteIcon
                else return Resources.musicalSymbols.eightNoteIcon
            }
            sourceSize.height: height
            sourceSize.width: width
            cache: true
        }

        ColorOverlay{
            anchors.fill: _internalImage
            source: _imageNote.image
            color:  "royalblue"
            antialiasing: true
        }
    }

    Column{
        spacing: 2

        Text{

            text: type
            color: "lightBlue"
        }
        Text{
            text: line1
            color: "lightBlue"
        }
        Text{
            text: line2
            color: "lightBlue"
        }
    }
}
