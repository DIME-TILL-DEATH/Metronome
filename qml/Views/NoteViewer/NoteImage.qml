import QtQuick 2.10
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0

import ResourceProvider 1.0
import StyleSettings 1.0


Rectangle {
    id: _imageNote

    height: root.width
    width: root.width
    color: "transparent"

    property alias image: _internalImage
    property alias overlay: _overlay
    property alias blinkAnim: _blinkAnim

    property var noteType


    Image{
        id: _internalImage
        anchors.fill: _imageNote

        property alias overlay : _overlay

        // пока так, но решить вопрос с отрисовками триолей и связей
        source: {
            switch(noteType){
                case "Whole" : return Resources.musicalSymbols.wholeNoteIcon
                case "Half" : return Resources.musicalSymbols.halfNoteIcon
                case "Quarter" : return Resources.musicalSymbols.quarterNoteIcon
                case "Eight": return Resources.musicalSymbols.eightNoteIcon
                case "Sixteenth" : return Resources.musicalSymbols.sixteenthNoteIcon
                case "ThirtySecond" : return Resources.musicalSymbols.thirtysecondNoteIcon
                default: return Resources.musicalSymbols.quarterNoteIcon
            }
        }
        cache: true
    }

    ColorOverlay{
        id: _overlay
        anchors.fill: _internalImage
        source: _imageNote.image
        antialiasing: true

        SequentialAnimation on color{
            id: _blinkAnim
            loops: Animation.Infinite
            running: false
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
