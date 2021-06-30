import QtQuick 2.0
import QtQuick.Layouts 1.3

import Views 1.0
import "../Functions.js" as Functions

GridLayout{
    id: _root

    columns: 3
    rows: 3

    rowSpacing: 5
    columnSpacing: 5

    Repeater{
        id: _repeater
//        model:

        delegate: NoteButton{
            id: _noteButton
            width: 60
            height: 60
            note: modelData
        }
    }

    Component.onCompleted: {
        _repeater.model = PatternEditor.getAllNoteNames()

        for(var i=0 ; i < _repeater.count; i++)
        {
            _repeater.itemAt(i).noteButtonClicked.connect(noteButtonClicked)
        }
    }

    signal noteButtonInGridClicked(noteType: string)
    function noteButtonClicked(noteType)
    {
        _root.noteButtonInGridClicked(noteType)
    }
}
