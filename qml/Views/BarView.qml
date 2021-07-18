import QtQuick 2.10
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import Base 1.0
import StyleSettings 1.0
import QtGraphicalEffects 1.0

Item {
    id: _root

    property alias barView: _barView
    property int noteWidth: 50
    property int barLinesWidth: noteWidth/25
    property var barLabel : barNumber

    signal noteDelegateClicked(noteIndex: int)

    function noteViewClicked(noteIndex)
    {
        _root.noteDelegateClicked(noteIndex)
    }

    Component.onCompleted: {
        for(var noteIndex=0; noteIndex < bar.notesCount(); noteIndex++)
        {
            _model.append({"note": bar.noteQMLAt(noteIndex)})
        }
    }

    width: bar.notesCount() * noteWidth + barLinesWidth

    ListView{
        id: _barView

        orientation: ListView.Horizontal
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds

        width: _root.width
        height: _root.height

        anchors{
            horizontalCenter: _root.horizontalCenter
        }

        interactive: false

        model: _model

        currentIndex: Metronome.activeNoteIndex

        highlight: HighlightRectangle{
            visible: (index === Metronome.activeBarIndex)
        }



        delegate: NoteView{
            id: _note

            width: noteWidth
            height: _barView.height

            y: height/10

            Component.onCompleted: {
                noteViewClicked.connect(_root.noteViewClicked)
            }
        }

        header: Item{
            y: parent.height/10

            Text{
                anchors{ left: _barLineStart.right
                         leftMargin: _barLineStart.width
                }

                color: Style.textColorMain
                font.pointSize: 10
                text: barLabel
            }
            Rectangle{
                id: _barLineStart

                width: barLinesWidth; height: noteWidth*1.75
                color: Style.imagesColorOverlay
            }
        }

        footer: Rectangle{
            id: _barLineStop

            y: parent.height/10

            width: barLinesWidth; height: noteWidth*1.75
            color: Style.imagesColorOverlay
        }
    }

    ListModel{ id: _model }

}
