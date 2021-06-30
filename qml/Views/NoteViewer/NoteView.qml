import QtQuick 2.10
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0
import ResourceProvider 1.0

import StyleSettings 1.0

Item {
    id: root
    property var flatteredIndex

    state: ((flatteredIndex === Metronome.activeNoteIndex) & (!Metronome.isMetronomePlaying)) ?
              "selected" : "base"

    opacity: _delegateArea.pressed ? 0.5 : 1

    signal noteViewClicked(index: int)
    MouseArea{
        id: _delegateArea
        anchors.fill: root
        z: -15
        propagateComposedEvents: true

        onClicked: {
            root.noteViewClicked(index)
        }
    }

    ColumnLayout{
//        spacing: 5

        anchors.fill: root

        NoteImage{
            id: _noteImage
            noteType: note.name
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Layout.fillHeight: false
        }

        Text{
            text: note.line1
            color: Style.textColorMain
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            Layout.fillHeight: false
        }

        Text{
            text: note.line2
            color: Style.textColorMain
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            Layout.fillHeight: false
        }
    }

    //-----------------------------------------------------------------------
    states: [
        State{
            name: "base"
            PropertyChanges { target: _noteImage.blinkAnim; running: false}
            PropertyChanges { target: _noteImage.overlay; color: Style.imagesColorOverlay}
        },
        State{
            name: "selected"
            PropertyChanges { target: _noteImage.blinkAnim; running: true}
        },
        State{
            name: "playing"
            PropertyChanges { target: _noteImage.overlay; color: Style.imagesColorOverlayHighlighted}
            PropertyChanges { target: _noteImage.blinkAnim; running: false}
        }
    ]

    Connections{
        target: Metronome
        function onActiveNoteIndexChanged()
        {
            if(flatteredIndex === Metronome.activeNoteIndex)
            {
                state = "playing"
            }
            else
            {
                state = "base"
            }
        }

        function onIsMetronomePlayingChanged()
        {
            if((!Metronome.isMetronomePlaying) & (flatteredIndex === Metronome.activeNoteIndex))
            {
               state = "selected"
            }
        }
    }
}
