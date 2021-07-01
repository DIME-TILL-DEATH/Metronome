import QtQuick 2.10
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import StyleSettings 1.0

Item {
    id: _root

    property alias barView: _barView
    property int noteWidth: 50
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

    width: bar.notesCount() * noteWidth

    ListView{
        id: _barView

        orientation: ListView.Horizontal
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds

        width: _root.width
        height: _root.height

        model: _model

        delegate: NoteView{
            id: _note
            width: noteWidth
            height: _barView.height

            Component.onCompleted: {
                noteViewClicked.connect(_root.noteViewClicked)
            }
        }

        header: Item{
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

                width: noteWidth/25; height: noteWidth*1.75
                color: Style.imagesColorOverlay
            }
        }

        footer: Rectangle{
            id: _barLineStop

            width: noteWidth/25; height: noteWidth*1.75
            color: Style.imagesColorOverlay
        }
    }

    ListModel{ id: _model }

}
